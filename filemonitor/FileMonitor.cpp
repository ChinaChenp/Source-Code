#include "FileMonitor.h"

namespace detail {

std::string deal_path(const char * path) {
    std::string new_path;
    if (path != NULL) {
        new_path = path;
        if (path[strlen(path) - 1] != '/') {
            new_path += "/";
        }
    }
    return new_path;
}

int scan_dir (const std::string & dir_name,
        std::set<std::string> * dirlist, std::set<std::string> *filelist = NULL) {
    DIR * d = opendir (dir_name.c_str());
    if (!d) {
        return -1;
    }

    std::string new_dir = deal_path(dir_name.c_str());

    if (NULL != dirlist) {
        dirlist->insert(dir_name);
    }

    while (1) {
        struct dirent * entry = readdir (d);
        if (! entry) {
            break;
        }

        std::string d_name = entry->d_name;
        if (!(entry->d_type & DT_DIR)) {
            if (NULL != filelist) {
                filelist->insert(new_dir + d_name);
            }
        } else {
            if (d_name != ".." && d_name != ".") {
                std::string path = new_dir + d_name + "/";

                if (d_name.size() >= PATH_MAX) {
                    return -2;
                }

                int ret = scan_dir (path.c_str(), dirlist, filelist);
                if (ret != 0) {
                    return ret;
                }
            }
        }
    }

    if (closedir(d)) {
        return -3;
    }

    return 0;
}


int event_check (int fd) {
    fd_set rfds;
    struct timeval timeout;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    return select (fd + 1, &rfds, NULL, NULL, &timeout);
}

int read_events (std::queue<struct inotify_event *> & qu, int fd) {
    const int buffer_size = 16 * 1024;
    char buffer[buffer_size];

    size_t r = ::read (fd, buffer, buffer_size);
    if (r <= 0) {
        return r;
    }

    int count = 0;
    for ( char *p = buffer; p < buffer + r; ) {
        struct inotify_event *event = (struct inotify_event *) p;

        size_t event_size = sizeof(struct inotify_event) + event->len;
        void * ev = ::malloc(event_size);
        ::memcpy((void *)ev, (void *)event, event_size);
        qu.push((struct inotify_event *)ev);
        p += event_size;
        count++;
    }

    LOG("%d events queued", count);
    return count;
}

int handle_event (const struct inotify_event * event,
        const std::map<int, basetool::Event> & events,
        basetool::FileEvent & fs) {
    /* If the event was associated with a filename, we will store it here */
    const char *cur_event_file_or_dir = NULL;
    /* This is the watch descriptor the event occurred on */
    int cur_event_wd = event->wd;
    int cur_event_cookie = event->cookie;

    // fd
    fs.fd= event->wd;

    // file name
    const char *cur_event_filename = NULL;
    if (event->len) {
        fs.filename = event->name;
        cur_event_filename = event->name;
    }

    // path
    std::map<int, basetool::Event>::const_iterator f = events.find(fs.fd);
    if (f != events.end()) {
        fs.path = f->second.path;
    } else {
        LOG("fd %d not find path", fs.fd);
    }

    // type
    if ( event->mask & (IN_ISDIR | IN_DELETE_SELF)) {
        fs.type = 2;
        cur_event_file_or_dir = "Dir";
    } else {
        fs.type = 1;
        cur_event_file_or_dir = "File";
    }

    // mask
    fs.mask = event->mask;

    unsigned long flags = event->mask &
        ~(IN_ALL_EVENTS | IN_UNMOUNT | IN_Q_OVERFLOW | IN_IGNORED );

    /* Perform event dependent handler routines */
    /* The mask is the magic that tells us what file operation occurred */
    switch (event->mask &
            (IN_ALL_EVENTS | IN_UNMOUNT | IN_Q_OVERFLOW | IN_IGNORED))
    {
        /* File was accessed */
        case IN_ACCESS:
            fs.mask_comment = "IN_ACCESS";
            LOG("ACCESS: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* File was modified */
        case IN_MODIFY:
            fs.mask_comment = "IN_MODIFY";
            LOG ("MODIFY: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* File changed attributes */
        case IN_ATTRIB:
            fs.mask_comment = "IN_ATTRIB";
            LOG ("ATTRIB: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* File open for writing was closed */
        case IN_CLOSE_WRITE:
            fs.mask_comment = "IN_CLOSE_WRITE";
            LOG ("CLOSE_WRITE: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* File open read-only was closed */
        case IN_CLOSE_NOWRITE:
            fs.mask_comment = "IN_CLOSE_NOWRITE";
            LOG ("CLOSE_NOWRITE: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* File was opened */
        case IN_OPEN:
            fs.mask_comment = "IN_OPEN";
            LOG ("OPEN: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* File was moved from X */
        case IN_MOVED_FROM:
            fs.mask_comment = "IN_MOVED_FROM";
            LOG ("MOVED_FROM: %s \"%s\" on WD #%i. Cookie=%d",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd,
                    cur_event_cookie);
            break;

            /* File was moved to X */
        case IN_MOVED_TO:
            fs.mask_comment = "IN_MOVED_TO";
            LOG ("MOVED_TO: %s \"%s\" on WD #%i. Cookie=%d",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd,
                    cur_event_cookie);
            break;

            /* Subdir or file was deleted */
        case IN_DELETE:
            fs.mask_comment = "IN_DELETE";
            LOG ("DELETE: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* Subdir or file was created */
        case IN_CREATE:
            fs.mask_comment = "IN_CREATE";
            LOG ("CREATE: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* Watched entry was deleted */
        case IN_DELETE_SELF:
            fs.mask_comment = "IN_DELETE_SELF";
            LOG ("DELETE_SELF: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* Watched entry was moved */
        case IN_MOVE_SELF:
            fs.mask_comment = "IN_MOVE_SELF";
            LOG ("MOVE_SELF: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* Backing FS was unmounted */
        case IN_UNMOUNT:
            fs.mask_comment = "IN_UNMOUNT";
            LOG ("UNMOUNT: %s \"%s\" on WD #%i",
                    cur_event_file_or_dir, cur_event_filename, cur_event_wd);
            break;

            /* Too many FS events were received without reading them
             *                some event notifications were potentially lost.  */
        case IN_Q_OVERFLOW:
            fs.mask_comment = "IN_Q_OVERFLOW";
            LOG ("Warning: AN OVERFLOW EVENT OCCURRED: ");
            break;

            /* Watch was removed explicitly by inotify_rm_watch or automatically
             *                because file was deleted, or file system was unmounted.  */
        case IN_IGNORED:
            fs.mask_comment = "IN_IGNORED";
            //watched_items--;
            LOG ("IGNORED: WD #%d", cur_event_wd);
            //LOG("Watching = %d items\n",watched_items);
            break;

            /* Some unknown message received */
        default:
            fs.mask_comment = "UNKNOWN";
            LOG ("UNKNOWN EVENT \"%X\" OCCURRED for file \"%s\" on WD #%i",
                    event->mask, cur_event_filename, cur_event_wd);
            break;

    }

    /* If any flags were set other than IN_ISDIR, report the flags */
    if (flags & (~IN_ISDIR)) {
        flags = event->mask;
        LOG ("Flags=%lX\n", flags);
    }

    return 0;
}

bool is_change_event(unsigned long mask) {

    unsigned long mk = mask & (IN_ALL_EVENTS |
            IN_UNMOUNT | IN_Q_OVERFLOW | IN_IGNORED);
    if (mk == IN_MOVED_FROM ||
        mk == IN_MOVED_TO ||
        mk == IN_DELETE ||
        mk == IN_CREATE ||
        mk == IN_DELETE_SELF ||
        mk == IN_MOVE_SELF) {
        return true;
    }

    return false;
}


void handle_events (std::queue<struct inotify_event *> & qu,
        const std::map<int, basetool::Event> & events,
        basetool::VeEvents & dir_events,
        basetool::VeEvents & file_events) {
    struct inotify_event * ev = NULL;
    while (!qu.empty()) {
        ev = qu.front();
        if (ev != NULL) {
            basetool::FileEvent fs;
            int ret = handle_event (ev, events, fs);
            if (ret == 0) {
                if (fs.type == 1) {
                    file_events[fs.fd].push_back(fs);
                } else {
                    dir_events[fs.fd].push_back(fs);
                }
            }

            free (ev);
            ev = NULL;
        }
        qu.pop();
    }
}
}

namespace basetool {
void default_callback(const std::vector<FileEvent> & events) {}

int FileMonitor::add_dir(const std::string & path, unsigned long mask, CallBack cb) {
    if (path.empty()) {
        LOG("path is NULL");
        return -1;
    }

    // real path
    char path_buf[256] = {0};
    const char *p = realpath(path.c_str(), path_buf);
    if (NULL == p) {
        LOG("do real path %s", path.c_str());
        return -2;
    }

    std::string new_path = detail::deal_path(path_buf);
    LOG("do real path %s", new_path.c_str());

    //scan path
    std::set<std::string> list_dir;
    int ret = detail::scan_dir(new_path.c_str(), &list_dir);
    if (ret != 0) {
        LOG("scan dir error ret = %d", ret);
        return -3;
    }

    // watch every file
    int watch_fd = 0;
    std::set<std::string>::iterator dir = list_dir.begin();
    for (; dir != list_dir.end(); ++dir) {
        watch_fd = ::inotify_add_watch(m_fd, dir->c_str(), mask);
        if (watch_fd < 0) {
            LOG("add watch file %s error", dir->c_str());
            return -4;
        }

        basetool::Event ev(cb, *dir, mask);
        m_events_info.insert(std::make_pair(watch_fd, ev));
    }

    return 0;
}

int FileMonitor::rm_dir(const std::string & path) {

    return 0;
}

void FileMonitor::start() {
    m_running = true;

    while (m_running && !m_events_info.empty()) {
        if ( detail::event_check(m_fd) > 0 ) {
            int r = detail::read_events(m_events_queue, m_fd);
            LOG ("event return num = %d", r);
            if (r <= 0) { // timeout or error
                LOG ("event check ret = %d", r);
                continue;
            } else {
                VeEvents dir_events, file_events;
                detail::handle_events(m_events_queue, m_events_info, dir_events, file_events);

                // only call back file event
                VeEvents::iterator it = file_events.begin();
                for (; it != file_events.end(); ++it) {
                    std::map<int, basetool::Event>::iterator cb = m_events_info.find(it->first);
                    if (cb == m_events_info.end()) {
                        continue;
                    }

                    // do call back
                    cb->second.cb(it->second);
                }

                update_event(dir_events);
            }
        }
    }
    return;
}

int FileMonitor::update_event(const basetool::VeEvents & events) {
    basetool::VeEvents::const_iterator it = events.begin();
    for (; it != events.end(); ++it) {
        // get info by fd
        std::map<int, basetool::Event>::iterator fd_info_iter = m_events_info.find(it->first);
        if (fd_info_iter == m_events_info.end()) {
            LOG("fd %d not find path", it->first);
            continue;
        }
        const basetool::Event & fd_info = fd_info_iter->second;

        const std::vector<FileEvent> & fe = it->second;
        std::vector<FileEvent>::const_iterator ev = fe.begin();
        for (; ev != fe.end(); ++ev) {
            unsigned long mk = ev->mask & (IN_ALL_EVENTS |
                    IN_UNMOUNT | IN_Q_OVERFLOW | IN_IGNORED);
            if (ev->type == 2 && (mk == IN_MOVED_TO || mk == IN_CREATE)) {
                std::string path = fd_info.path + ev->filename + "/";
                //scan path
                std::set<std::string> list_dir;
                int ret = detail::scan_dir(path, &list_dir);
                if (ret != 0) {
                    LOG("scan dir error ret = %d", ret);
                    return -1;
                }
                LOG("scan dir %s ", path.c_str());

                // watch every file
                int watch_fd = 0;
                std::set<std::string>::iterator dir = list_dir.begin();
                for (; dir != list_dir.end(); ++dir) {
                    watch_fd = ::inotify_add_watch(m_fd, dir->c_str(), fd_info.mask);
                    if (watch_fd < 0) {
                        LOG("add watch file %s error", dir->c_str());
                        return -2;
                    }

                    basetool::Event ev(fd_info.cb, *dir, fd_info.mask);
                    m_events_info.insert(std::make_pair(watch_fd, ev));
                }
                break;
            }
        }
    }
    return 0;
}
} // namespace basetool

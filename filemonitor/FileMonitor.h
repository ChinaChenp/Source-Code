#ifndef FILE_MONITOR_
#define FILE_MONITOR_

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

#include <dirent.h>
#include <limits.h> // PATH_MAX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/inotify.h>
#include <sys/stat.h>

namespace basetool {
#define LOG(fmt,args...) \
    do {\
        printf("%s/%s:%d "fmt"\n",__FILE__,__FUNCTION__,__LINE__,##args);\
    } while(0)\


typedef struct fileevent {
    int fd;
    unsigned long type;   // 1-file or 2-dir
    unsigned long mask;
    std::string mask_comment;
    std::string filename;
    std::string path;
    fileevent() : fd(0), type(-1), mask(0) {}
}FileEvent;

void default_callback(const std::vector<FileEvent> & events);
typedef void (*CallBack)(const std::vector<FileEvent> &);
typedef std::map<int, std::vector<FileEvent> > VeEvents;

typedef struct event {
    CallBack cb;
    std::string path;
    unsigned long mask;
    event(CallBack c, const std::string & p, unsigned long mk):
        cb(c), path(p), mask(mk) {}
}Event;

class FileMonitor {
public:
    FileMonitor():
        m_running(false),m_fd(::inotify_init()) {}

    ~FileMonitor() {
        std::map<int, basetool::Event>::iterator it = m_events_info.begin();
        for (; it != m_events_info.end(); ++it) {
            ::inotify_rm_watch(m_fd, it->first);
        }

        if (!m_fd) {
            ::close(m_fd);
        }

        while (!m_events_queue.empty()) {
            struct inotify_event * e = m_events_queue.front();
            if (e != NULL) {
                ::free(e);
                e = NULL;
            }
            m_events_queue.pop();
        }
    }

    //
    // IN_ACCESS        文件被访问
    // IN_ATTRIB        文件属性发生变化
    // IN_CLOSE_WRITE   以write方式打开文件并关闭
    // IN_CLOSE_NOWRITE 以非write方式打开文件并关闭
    // IN_CREATE        文件或目录被创建
    // IN_DELETE        文件或目录被删除（被监测的文件夹A中B文件被删除）
    // IN_DELETE_SELF   被监测的文件或目录被删除（被监测的文件夹A被删除）
    // IN_MODIFY        文件被修改
    // IN_MOVE_SELF     被监测的文件或目录移动
    // IN_MOVED_FROM    文件移出被监测的目录
    // IN_MOVED_TO      文件移入被监测的目录
    // IN_OPEN          文件被打开
    //
    int add_dir(const std::string & path,
            unsigned long mask = IN_ALL_EVENTS, CallBack cb = default_callback);
    int rm_dir(const std::string & path);

    void start();

private:
    int update_event(const basetool::VeEvents & events);

    bool m_running;
    int m_fd;
    std::queue<struct inotify_event *> m_events_queue;
    std::map<int, basetool::Event> m_events_info;
};

}
#endif //FILE_MONITOR_

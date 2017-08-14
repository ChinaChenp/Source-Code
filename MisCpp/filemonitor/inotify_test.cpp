#include "FileMonitor.h"
#include <iostream>

void callback1(const std::vector<basetool::FileEvent> & event){
    for (int i = 0; i < event.size(); ++i) {
        std::cout << "callback1, size " << i
            << ",wath fd = " << event[i].fd
            << ",path = " << event[i].path
            << ",type = " << event[i].type
            << ",name = " << event[i].filename
            << ",mask = " << event[i].mask
            << ",mask comment = " << event[i].mask_comment << std::endl;
    }
}

void callback2(const std::vector<basetool::FileEvent> & event){
    for (int i = 0; i < event.size(); ++i) {
        std::cout << "callback2, size " << i
            << ",wath fd = " << event[i].fd
            << ",path = " << event[i].path
            << ",type = " << event[i].type
            << ",name = " << event[i].filename
            << ",mask = " << event[i].mask
            << ",mask comment = " << event[i].mask_comment << std::endl;
    }
}

int main(int argc, char * argv[]) {
    basetool::FileMonitor fm;
    fm.add_dir(argv[1], IN_ALL_EVENTS, callback2);
    fm.add_dir(argv[2], IN_CREATE | IN_MODIFY | IN_DELETE | IN_ATTRIB, callback1);
    fm.start();
    return 0;
}

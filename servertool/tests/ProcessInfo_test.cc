#include "ProcessInfo.h"
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

int main()
{
  printf("pid = %d\n", basetool::ProcessInfo::pid());
  printf("uid = %d\n", basetool::ProcessInfo::uid());
  printf("euid = %d\n", basetool::ProcessInfo::euid());
  printf("start time = %s\n", basetool::ProcessInfo::startTime().toFormattedString().c_str());
  printf("hostname = %s\n", basetool::ProcessInfo::hostname().c_str());
  printf("opened files = %d\n", basetool::ProcessInfo::openedFiles());
  printf("threads = %zd\n", basetool::ProcessInfo::threads().size());
  printf("num threads = %d\n", basetool::ProcessInfo::numThreads());
  printf("status = %s\n", basetool::ProcessInfo::procStatus().c_str());
}

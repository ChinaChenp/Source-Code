#include "Singleton.h"
#include "CurrentThread.h"
#include "ThreadLocal.h"
#include "Thread.h"

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <stdio.h>
#include <unistd.h>

class Test : boost::noncopyable
{
 public:
  Test()
  {
    printf("tid=%d, constructing %p\n", basetool::CurrentThread::tid(), this);
  }

  ~Test()
  {
    printf("tid=%d, destructing %p %s\n", basetool::CurrentThread::tid(), this, name_.c_str());
  }

  const basetool::string& name() const { return name_; }
  void setName(const basetool::string& n) { name_ = n; }

 private:
  basetool::string name_;
};

#define STL basetool::Singleton<basetool::ThreadLocal<Test> >::instance().value()

void print()
{
  printf("tid=%d, %p name=%s\n",
         basetool::CurrentThread::tid(),
         &STL,
         STL.name().c_str());
}

void threadFunc(const char* changeTo)
{
  print();
  STL.setName(changeTo);
  sleep(1);
  print();
}

int main()
{
  STL.setName("main one");
  basetool::Thread t1(boost::bind(threadFunc, "thread1"));
  basetool::Thread t2(boost::bind(threadFunc, "thread2"));
  t1.start();
  t2.start();
  t1.join();
  print();
  t2.join();
  pthread_exit(0);
}

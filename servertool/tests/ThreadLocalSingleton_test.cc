#include "ThreadLocalSingleton.h"
#include "CurrentThread.h"
#include "Thread.h"

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <stdio.h>

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

void threadFunc(const char* changeTo)
{
  printf("tid=%d, %p name=%s\n",
         basetool::CurrentThread::tid(),
         &basetool::ThreadLocalSingleton<Test>::instance(),
         basetool::ThreadLocalSingleton<Test>::instance().name().c_str());
  basetool::ThreadLocalSingleton<Test>::instance().setName(changeTo);
  printf("tid=%d, %p name=%s\n",
         basetool::CurrentThread::tid(),
         &basetool::ThreadLocalSingleton<Test>::instance(),
         basetool::ThreadLocalSingleton<Test>::instance().name().c_str());

  // no need to manually delete it
  // basetool::ThreadLocalSingleton<Test>::destroy();
}

int main()
{
  basetool::ThreadLocalSingleton<Test>::instance().setName("main one");
  basetool::Thread t1(boost::bind(threadFunc, "thread1"));
  basetool::Thread t2(boost::bind(threadFunc, "thread2"));
  t1.start();
  t2.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         basetool::CurrentThread::tid(),
         &basetool::ThreadLocalSingleton<Test>::instance(),
         basetool::ThreadLocalSingleton<Test>::instance().name().c_str());
  t2.join();

  pthread_exit(0);
}

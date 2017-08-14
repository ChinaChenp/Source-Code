#include "Singleton.h"
#include "CurrentThread.h"
#include "Thread.h"

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

class TestNoDestroy : boost::noncopyable
{
 public:
  // Tag member for Singleton<T>
  void no_destroy();

  TestNoDestroy()
  {
    printf("tid=%d, constructing TestNoDestroy %p\n", basetool::CurrentThread::tid(), this);
  }

  ~TestNoDestroy()
  {
    printf("tid=%d, destructing TestNoDestroy %p\n", basetool::CurrentThread::tid(), this);
  }
};

void threadFunc()
{
  printf("tid=%d, %p name=%s\n",
         basetool::CurrentThread::tid(),
         &basetool::Singleton<Test>::instance(),
         basetool::Singleton<Test>::instance().name().c_str());
  basetool::Singleton<Test>::instance().setName("only one, changed");
}

int main()
{
  basetool::Singleton<Test>::instance().setName("only one");
  basetool::Thread t1(threadFunc);
  t1.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         basetool::CurrentThread::tid(),
         &basetool::Singleton<Test>::instance(),
         basetool::Singleton<Test>::instance().name().c_str());
  basetool::Singleton<TestNoDestroy>::instance();
  printf("with valgrind, you should see %zd-byte memory leak.\n", sizeof(TestNoDestroy));
}

#include "Thread.h"
#include "CurrentThread.h"

#include <string>
#include <boost/bind.hpp>
#include <stdio.h>
#include <unistd.h>

void mysleep(int seconds)
{
  timespec t = { seconds, 0 };
  nanosleep(&t, NULL);
}

void threadFunc()
{
  printf("tid=%d\n", basetool::CurrentThread::tid());
}

void threadFunc2(int x)
{
  printf("tid=%d, x=%d\n", basetool::CurrentThread::tid(), x);
}

void threadFunc3()
{
  printf("tid=%d\n", basetool::CurrentThread::tid());
  mysleep(1);
}

class Foo
{
 public:
  explicit Foo(double x)
    : x_(x)
  {
  }

  void memberFunc()
  {
    printf("tid=%d, Foo::x_=%f\n", basetool::CurrentThread::tid(), x_);
  }

  void memberFunc2(const std::string& text)
  {
    printf("tid=%d, Foo::x_=%f, text=%s\n", basetool::CurrentThread::tid(), x_, text.c_str());
  }

 private:
  double x_;
};

int main()
{
  printf("pid=%d, tid=%d\n", ::getpid(), basetool::CurrentThread::tid());

  basetool::Thread t1(threadFunc);
  t1.start();
  t1.join();

  basetool::Thread t2(boost::bind(threadFunc2, 42),
                   "thread for free function with argument");
  t2.start();
  t2.join();

  Foo foo(87.53);
  basetool::Thread t3(boost::bind(&Foo::memberFunc, &foo),
                   "thread for member function without argument");
  t3.start();
  t3.join();

  basetool::Thread t4(boost::bind(&Foo::memberFunc2, boost::ref(foo), std::string("Shuo Chen")));
  t4.start();
  t4.join();

  {
    basetool::Thread t5(threadFunc3);
    t5.start();
    // t5 may destruct eariler than thread creation.
  }
  mysleep(2);
  {
    basetool::Thread t6(threadFunc3);
    t6.start();
    mysleep(2);
    // t6 destruct later than thread creation.
  }
  sleep(2);
  printf("number of created threads %d\n", basetool::Thread::numCreated());
}

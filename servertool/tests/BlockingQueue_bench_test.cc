#include "BlockingQueue.h"
#include "CountDownLatch.h"
#include "Thread.h"
#include "Timestamp.h"

#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <string>
#include <stdio.h>

class Bench
{
 public:
  Bench(int numThreads)
    : latch_(numThreads),
      threads_(numThreads)
  {
    for (int i = 0; i < numThreads; ++i)
    {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.push_back(new basetool::Thread(
            boost::bind(&Bench::threadFunc, this), basetool::string(name)));
    }
    for_each(threads_.begin(), threads_.end(), boost::bind(&basetool::Thread::start, _1));
  }

  void run(int times)
  {
    printf("waiting for count down latch\n");
    latch_.wait();
    printf("all threads started\n");
    for (int i = 0; i < times; ++i)
    {
      basetool::Timestamp now(basetool::Timestamp::now());
      queue_.put(now);
      usleep(1000);
    }
  }

  void joinAll()
  {
    for (size_t i = 0; i < threads_.size(); ++i)
    {
      queue_.put(basetool::Timestamp::invalid());
    }

    for_each(threads_.begin(), threads_.end(), boost::bind(&basetool::Thread::join, _1));
  }

 private:

  void threadFunc()
  {
    printf("tid=%d, %s started\n",
           basetool::CurrentThread::tid(),
           basetool::CurrentThread::name());

    std::map<int, int> delays;
    latch_.countDown();
    bool running = true;
    while (running)
    {
      basetool::Timestamp t(queue_.take());
      basetool::Timestamp now(basetool::Timestamp::now());
      if (t.valid())
      {
        int delay = static_cast<int>(timeDifference(now, t) * 1000000);
        // printf("tid=%d, latency = %d us\n",
        //        basetool::CurrentThread::tid(), delay);
        ++delays[delay];
      }
      running = t.valid();
    }

    printf("tid=%d, %s stopped\n",
           basetool::CurrentThread::tid(),
           basetool::CurrentThread::name());
    for (std::map<int, int>::iterator it = delays.begin();
        it != delays.end(); ++it)
    {
      printf("tid = %d, delay = %d, count = %d\n",
             basetool::CurrentThread::tid(),
             it->first, it->second);
    }
  }

  basetool::BlockingQueue<basetool::Timestamp> queue_;
  basetool::CountDownLatch latch_;
  boost::ptr_vector<basetool::Thread> threads_;
};

int main(int argc, char* argv[])
{
  int threads = argc > 1 ? atoi(argv[1]) : 1;

  Bench t(threads);
  t.run(10000);
  t.joinAll();
}

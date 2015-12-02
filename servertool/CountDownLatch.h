#ifndef BASE_TOOL_COUNTDOWNLATCH_H
#define BASE_TOOL_COUNTDOWNLATCH_H

#include "Condition.h"
#include "Mutex.h"

#include <boost/noncopyable.hpp>

namespace basetool
{

class CountDownLatch : boost::noncopyable
{
 public:

  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:
  mutable MutexLock mutex_;
  Condition condition_;
  int count_;
};

}
#endif  // BASE_TOOL_COUNTDOWNLATCH_H

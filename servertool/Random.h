#ifndef BASE_TOOL_RANDOM_H_
#define BASE_TOOL_RANDOM_H_

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h> //getpid
#include <unistd.h>


namespace basetool
{
// A very simple random number generator.  Not especially good at
// generating truly random bits, but good enough for our needs in this
// package.
class Random 
{
public:
  explicit Random(uint32_t s = 0) 
	{
		uint32_t seed = s == 0 ? randSeed() : s;
		seed_ = seed & 0x7fffffffu;
  }

  uint32_t next() {
    static const uint32_t M = 2147483647L;   // 2^31-1
    static const uint64_t A = 16807;  // bits 14, 8, 7, 5, 2, 1, 0
    // We are computing
    //       seed_ = (seed_ * A) % M,    where M = 2^31-1
    //
    // seed_ must not be zero or M, or else all subsequent computed values
    // will be zero or M respectively.  For all other values, seed_ will end
    // up cycling through every number in [1,M-1]
    uint64_t product = seed_ * A;

    // Compute (product % M) using the fact that ((x << 31) % M) == x.
    seed_ = static_cast<uint32_t>((product >> 31) + (product & M));
    // The first reduction may overflow by 1 bit, so we may need to
    // repeat.  mod == M is not possible; using > allows the faster
    // sign-bit-based test.
    if (seed_ > M) {
      seed_ -= M;
    }
    return seed_;
  }
  // Returns a uniformly distributed value in the range [0..n-1]
  // REQUIRES: n > 0
  uint32_t rangeInt(int n) { return next() % n; }

	// bool true/false
	bool rangeBool() { return ((next() & static_cast<uint32_t>(1)) != 0); } 

	// double [0 -> n)
	double rangeDouble(int n)
	{
		static const double doubleSeed = 2.3283064365386962890625e-10;
		double retval = next() * doubleSeed;
		double docval = retval - static_cast<uint32_t>(retval);
		return next() % n + docval;
	}

private:
	uint32_t randSeed();
  uint32_t seed_;

};

inline uint32_t Random::randSeed()
{
	uint32_t seed = 0;
	struct timeval r;
	gettimeofday (&r, NULL);
	seed += static_cast<uint32_t>(r.tv_sec);
	seed += static_cast<uint32_t>(r.tv_usec);
	seed += static_cast<uint32_t>(getpid());
	seed += static_cast<uint32_t>(getppid());
	return seed;
}

}  // namespace basetool

#endif  // BASE_TOOL_RANDOM_H_

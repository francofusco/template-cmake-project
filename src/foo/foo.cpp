/** @file foo.cpp
  * @brief Implemenation file for the foo::bar(int) function.
  */
#include <foo/foo.hpp>

namespace foo {

int bar(int a) {
  return a+1;
}


unsigned int factorial(
  unsigned int n
)
{
  return n<=1 ? 1 : n*factorial(n-1);
}


int sign(
  int n
)
{
  if(n==0)
    return 0;
  else
    return n>0 ? 1 : -1;
}



Counter::Counter(
  unsigned int max,
  bool autoreset
)
: count_(0)
, max_(max)
, autoreset_(autoreset)
{

}


void Counter::countOnce()
{
  if(count_ < max_)
    count_++;
  else if(autoreset_)
    reset();
}


void Counter::reset()
{
  count_ = 0;
}

}

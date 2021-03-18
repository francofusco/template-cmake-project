/** @file foo.hpp
  * @brief Header file for the foo::bar(int) function.
  */
#pragma once

namespace foo {

/// A function.
/** Long description.
  * @param a an integer parameter.
  * @return some value.
  */
int bar(int a);

/// Returns the factorial of a number.
/** @param n a number \f$n\in\mathbb{N}\f$.
  * @return \f$n!\f$
  */
unsigned int factorial(unsigned int n);

/// Returns the sign of n.
int sign(int n);


/// A simple class for counting.
class Counter {
public:
  /// Creates a counter which cannot exceed a given maximum.
  /** @param max the maximum value the counter can reach.
    * @param autoreset if true, then after reaching the maximum value the
    *   counter will overflow and return to zero. If false, the counter will
    *   stop incrementing at max, and a call to reset() must be performed to
    *   bring it back to zero.
    */
  Counter(unsigned int max, bool autoreset);

  /// Access the current count value.
  inline const unsigned int& currentCount() const { return count_; }

  /// Increment the counter by one unit.
  void countOnce();

  /// Reset the counter to zero.
  void reset();

private:
  unsigned int count_; ///< Stores the current count value.
  unsigned int max_; ///< Maximum value that can be reached by the counter.
  bool autoreset_; ///< If true, the counter can overflow.
};

}

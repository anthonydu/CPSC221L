/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n) {
  /* Your code goes here! */
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fib(n - 1) + fib(n - 2);
}

map<unsigned long, unsigned long> fibs;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n) {
  /* Your code goes here! */
  if (n == 0) return 0;
  if (n == 1) return 1;
  auto found = fibs.find(n);
  if (found == fibs.end()) {
    fibs[n] = memoized_fib(n - 1) + memoized_fib(n - 2);
    return fibs[n];
  } else
    return found->second;

  //   if (n == 0) return 0;
  //   if (n == 1) return 1;
  //   unsigned long fib1, fib2;
  //   auto fib0 = fibs.find(n - 1);
  //   if (fib0 == fibs.end())
  //     fib1 = fib(n - 1);
  //   else
  //     fib1 = fib0->second;
  //   fib0 = fibs.find(n - 2);
  //   if (fib0 == fibs.end())
  //     fib2 = fib(n - 2);
  //   else
  //     fib2 = fib0->second;
  //   return fib1 + fib2;
}

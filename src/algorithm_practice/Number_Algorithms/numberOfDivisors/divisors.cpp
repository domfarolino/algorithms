#include <iostream>
#include <climits>

// Source: Inspired by `betweenTwoSets`

/**
 * Number of divisors
 * The goal of this algorithm is to compute and output
 * the number of divisors for a given number. I always
 * knew the most optimized version of this algorithm had
 * something to do with the square root of the number you
 * were trying to find the divisors of, but without thinking
 * too hard, I couldn't figure out why.
 *
 * The naïve approach to solving this problem is trivial.
 * Given a number n, for all numbers [1, n] (inclusive) we
 * need to check to see if (n % i) == 0. Each time the previous
 * condition is met, `i` is a divisor of (is a factor of) n, and
 * we can increment our count of divisors and print `i` out.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Let's take a closer look at a number's divisors. For example, the
 * divisors of 20 are 1, 2, 4, 5, 10, and 20. Seeing this, you might
 * see that one pattern is that the divisors of a number will never
 * exceed half of that number (with the exception of the number itself).
 * This could give us a minor optimization, but we ultimately have the same
 * complexity as before. It's on the right track though; what we can realize
 * is that the divisors come in pairs. When I divide 20 by 1 I get 20. By 2 I
 * get 10, by 4 I get 5, by 5 I get 4, and so on. They repeat. 20 has 6 divisors
 * and the pairs look like:
 *  (1,  20)
 *  (2,  10)
 *  (4,  5)
 *  (5,  4)
 *  (10, 2)
 *  (20, 1)
 *
 * Notice that the pairs repeat, but when do they start repeating? They start repeating
 * when the second number begins to overtake the first number. For 20, the first occurrence
 * of this appears at 5, but on a more concrete level the first number will TRULY start to get
 * overtaken by the second when the two numbers are equal of course. In that, the two numbers are
 * equal and multiplying them yields `n`. This happens when the numbers are sqrt(n) of course. Therefore
 * to avoid repeating these pairs, we can get all divisors by just looking at the divisors that are <= sqrt(n).
 *
 * For all i <= sqrt(n) such that (n % i) == 0, `i` is a divisor of `n`, so we can count it. `n / i` is also a divisor
 * which we'd get to later by iterating past the point where the first number gets overtaken by the second, but we can
 * count it immediately instead of waiting. The divisor `n / i` is either equal to `i` (in which case `i` is the integer
 * square root of `n`) or it is > to `i`. If it is greater, we want to count it right away, if it is equal, meaning `n` is
 * a perfect square, we want to make sure we only count it once!
 *
 * Complexity analysis:
 * Time complexity: O(sqrt(n))
 * Space complexity: O(1)
 */

// Can assume n will not overflow a 32-bit integer
void listDivisors(int n) {
  int count = 0;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      count++;
      std::cout << i << " is a divisor" << std::endl;

      if (i != (n / i)) {
        count++;
        std::cout << n / i  << " is a divisor" << std::endl;
      }
    }
  }

  std::cout << "The total number of divisors is: " << count << std::endl;
}

int main() {
  int n;
  std::cin >> n;
  listDivisors(n);
  return 0;
}

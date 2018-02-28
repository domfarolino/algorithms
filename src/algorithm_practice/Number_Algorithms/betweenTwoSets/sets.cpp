#include <iostream>
#include <stdexcept>
#include <vector>

// Source: https://www.hackerrank.com/challenges/between-two-sets

/**
 * Between Two Sets
 * The key to this algorithm is realizing that we
 * need to find the least common multiple of all of
 * the numbers in the first set, and then the greatest
 * common divisor of all the numbers in the second set.
 * This is simply because the smallest number such that
 * every number is a set is a factor of is the least common
 * multiple of the set, and if this number is a factor of all
 * numbers in the second set it will certainly be a factor of
 * said set's greatest common factor/divisor. Thus we compute
 * both set values before (a bit of preprocessing), and then we
 * run through all multiples of the LCM <= GCD and keep track
 * how many multiples of the LCM are factors of the GCD.
 *
 * This implementation has a few optimizations left out that I
 * did not think of:
 *
 *  - We could be using the optimized Euclidean GCD algorithm to
 *    compute GCD values in O(log(n)) instead of O(n), where n is
 *    the larger of the two passedin values.
 *  - An early-out check to see if the LCM of set `A` divides (is
 *    a factor of) the GCD of set `B`. This means that all of the
 *    numbers of set `A` must divide (be factors of) all of the numbers
 *    in set `B`. If they are not, they share no common factors and such
 *    "in between" value we're seeking does not exist. It also takes care
 *    of the case where LCM of set `A` < GCD of set `B`, because a larger
 *    number cannot divide a smaller one.
 *  - This implementation currently loops from LCM => GCD, looking at all
 *    multiples of LCM in between checking to see how many divide (are factors
 *    of) GCD. There is a more optimized way to find the number of divisors in some
 *    range, and in this case it would be possible to do so in O(sqrt(c)) time, where
 *    `c` is the GCD of the second set. See the `numberOfDivisors` algorithm in this
 *    repository.
 *
 * Complexity analysis:
 * Time complexity: O(n*b + gcd); n = length of the longest set, b = largest number from any set
 *                              gcd = GCD of second set. We get the n*b because for every value in
 *                              each set, we have to run the GCD algorithm which is O(max(x, y)).
 *                              After this, we have to compute all divisors of GCD that are multiples
 *                              of LCM, which takes O(gcd) time in the worst case. If we were to use the
 *                              optimized Euclidean GCD algorithm we could get this down to O(n*log(b) + c),
 *                              and we could further reduce this to O(n*log(b) + sqrt(gcd)) if we were to use
 *                              a more optimized approach to finding all divisors of GCD that are multiples of
 *                              LCM.
 * TODO(domfarolino): confirm this complexity
 * Space complexity: O(1)
 */

/**
 * Unoptimized Euclidean GCD
 *
 * Time complexity: O(n); n = max(a, b)
 * Space complexity: O(1)
 */
int gcd(unsigned int a, int b) {
  while (a != b) {
    if (a > b) {
      a -= b;
    } else {
      b -= a;
    }
  }

  return a;
}

unsigned int lcmOfSet(const std::vector<int>& set) {
  if (set.size() == 0) throw std::logic_error("The set must have at least one element");

  unsigned int returnLCM = set[0];

  for (int i = 1; i < set.size(); ++i) {
    returnLCM = (returnLCM * set[i]) / (gcd(returnLCM, set[i]));
  }

  return returnLCM;
}

int gcdOfSet(const std::vector<int>& set) {
  if (set.size() == 0) throw std::logic_error("The set must have at least one element");

  int returnGCD = set[0];

  for (int i = 1; i < set.size(); ++i) {
    returnGCD = gcd(returnGCD, set[i]);
  }

  return returnGCD;
}

int main() {
  int n, m;
  unsigned int setLCM, setGCD;
  std::cin >> n >> m;
  std::vector<int> a(n), b(m);

  for (int i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }

  for (int i = 0; i < b.size(); ++i) {
    std::cin >> b[i];
  }

  setLCM = lcmOfSet(a);
  setGCD = gcdOfSet(b);

  /**
   * This loop checks all multiples of the
   * LCM of the first set <= to the GCD of
   * the second set while keeping track of
   * the number of multiples that are factors
   * of the second
   */
  int i = 1, count = 0;
  while (setLCM*i <= setGCD) {
    if (setGCD % (setLCM*i) == 0) {
      count++;
    }

    i++;
  }

  std::cout << count << std::endl;
  return 0;
}

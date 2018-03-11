#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // for min()...replace with define?

// Source: https://www.hackerrank.com/challenges/non-divisible-subset/

/**
 * Non-Divisible Subset
 * My first reaction to this was that there is definitely
 * an easier way to do this than generating all 2^n subsets
 * and running tests on them, so my next thought was we could
 * in O(n^2) tell exactly how many pairs of numbers in the original
 * set had a sum divisible by `k`. If there's one pair with this quality,
 * we can eliminate one of the numbers, thus making the maximal subset of
 * length n-1. If there are two overlapping pairs, we have to be more careful.
 * Consider the array:
 * [1, 5, 11], k = 6
 * In this array, we have 1 + 5 = 6, and 1 + 11 = 12. Both of these are evenly
 * divisible by 6, however both pairs share the same number `1`, therefore eliminating
 * the 1 would be the best way to maximize the size of our non-divisible subset as opposed
 * to eliminating both 5 and 11. The best way to tackle this case and others is to realize what
 * 5, 11, and some other numbers have in common. We know any number whose sum with 1 is a multiple
 * of 6 must be 1 less than a multiple of six itself. This is because intuitively n1 + n2 = mk if and
 * only if n1 % k = x, and n2 % k = 1 - x. The two operands % k must have complementary modulo values.
 * The next key realization that I did not personally get is noting we should maintain a map where the
 * keys are the possible values of any number % k. The values of this map will be the number of times each
 * value in the array % k exists. So given the array [1, 5, 11], k = 6 we'd have a map looking like this: {1: 1, 5: 2}
 * because there is one value such that value % k = 1, and two values such that value % k = 5. Again, we know that the
 * only two values that can be summed to form a multiple of k are values whose modulo of k are complementary. This means
 * n1 % k = x, n2 % k = k - x. In this case, we need to look at exactly how many values share the key x, and k - x. The number
 * of values we'll need to get rid of in the array given some pair of x, k - x will be the smaller of the two uMap[x] and uMap[k - x].
 * In the above example, getting rid of 1 is cheaper than getting rid of both 5 and 11 because the 5 and 11 don't interfere with each other,
 * but the 1 interferes with both. We can leave the two values whose modulo with k is 5 and still meet the same requirements. We need to do this
 * for every x, k - x key pair and keep track of how many values we eliminate. This means we can effectively iterate up through k/2 so we can be
 * assured we don't duplicate pairwise work.
 *
 * Let's take a look at the special cases where value % k = 0, and value % k = k/2 . Of course all values that are by default a
 * multiple of k will need removed except for one of them. That means in the array [2, 4, 6], k = 2 we'll have the map {2: 3}, and
 * we'll need to get rid of two of the three values. We also have to consider the case where k is even. In this case k/2 and k - k/2
 * will be the same value so given our described algorithm we'll be removing all occurrences by default. This is a mistake and we can
 * account for it by catching this early and handling how we wish.
 *
 * Time complexity: O(n + k)
 * Space complexity: O(k)
 */

long largestSubset(const std::vector<long>& v, long k) {
  long numberOfValuesRemoved = 0;
  std::unordered_map<long, long> uMap;

  // Initialize map to have all modulo values 0...k-1 set to 0
  for (long i = 0; i < k; ++i) {
    uMap.insert(std::make_pair(i, 0));
  }

  // Set all values in map for real
  for (long i = 0; i < v.size(); ++i) {
    uMap[v[i] % k]++;
  }

  // Handle special case of all multiples of k first
  if (uMap[0] != 0) {
    numberOfValuesRemoved += (uMap[0] - 1);
  }

  // Handle case where k is even
  if (k%2 == 0 && uMap[k/2]) {
    /**
     * Eventually we'll be adding the minimum of
     * uMap[k/2] and uMap[k - k/2] which will be the
     * same. So since we have to add it to numberOfValuesRemoved
     * anyways, we adjust it to be the correct value now. The correct
     * value is 1 less than the actual value, since we'll be removing
     * all but one of these occurrences.
     */
    uMap[k/2] -= 1;
  }

  // General case
  for (long i = 1; i <= k/2; ++i) {
    numberOfValuesRemoved += std::min(uMap[i], uMap[k - i]);
  }

  return v.size() - numberOfValuesRemoved;
}

int main() {
  long n, k;
  std::vector<long> v;
  std::cin >> n >> k;
  v.resize(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  std::cout << largestSubset(v, k) << std::endl;
  return 0;
}

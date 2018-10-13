#include <iostream>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-104/problems/partition-array-into-disjoint-intervals/

/**
 * Partition Array Into Disjoint Intervals
 *
 * This problem is relatively straightforward, but I'm documenting it here because
 * I think it employs a good reusable concept. Since we want to minimize `L`, where
 * `L` is the index of the last element in the left array partition, we should of course
 * start with `L` = 0, and check to see if this arrangement satisfies our conditions. So
 * what exactly is the condition? Well we need to know that every element in our left array
 * partition is <= every element in the right array partition. This sounds a little overwhelming,
 * however it can naively be done by brute-force getting a max and a min value from each partition
 * of the array, at any given `L`, and comparing them. This would give us a solution whose time complexity
 * is O(n^2), since we may have to go through O(n) different `L` arrangements, each costing us O(n) to check
 * for min and max values for both partitions respectively. This is where a key reusable concept comes into
 * play. We can support fast min/max lookup for subarrays that start or end with a boundary of the original
 * array, and by fast I mean O(1)! We can maintain two separate arrays, for max and min values that are kind
 * of dynamic programmy in nature, that can tell us the min and max values of all non-middle subarrays. For
 * example:
 *
 * Array: [3, 1, 0, 4, 6, 5]
 * max:   [3, 3, 3, 4, 6, 6]
 *
 * This max array tells us the max value in any subarray from [0, i], i ∈ 0...n - 1, and can be built just
 * by traversing the array, and keeping track of the max element seen! Therefore, for any `L` ∈ 0...n - 1, we
 * can, in O(1) time, know the max value it contains. The same can be done for the min values of any right partition,
 * by building backwards, from n - 1...0. Not too bad, it's a classic space vs time complexity tradeoff really. The concept
 * of these kinds of arrays are super convenient, and can be used in a lot of places. Now we just keep iterating `L` until our
 * condition is satisfied, and we can return `L + 1` when finished, since that is the length of the left partition.
 *
 * Note the actual Leetcode problem says each array is guaranteed to have an answer, so we can get away with iterating
 * our `L` from 0...n - 2, since there will always be a right partition, however in the real world, we may not be able
 * to make this assumption, and might have to iterate from 0...n - 1, and return something special if a valid partition
 * does not exist.
 *
 * Complexity analysis
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

int partitionDisjoint(const std::vector<int>& A) {
  std::vector<int> leftMax = A, rightMin = A;
  int currMin = INT_MAX, currMax = INT_MIN;

  for (int i = 0; i < A.size(); ++i) {
    currMax = std::max(currMax, A[i]);
    leftMax[i] = currMax;
    currMin = std::min(currMin, A[A.size() - 1 - i]);
    rightMin[A.size() - 1 - i] = currMin;
  }

  int L = 0;
  currMax = leftMax[L];
  currMin = rightMin[L + 1];
  while (currMax > currMin) {
    L++;
    currMax = leftMax[L];
    currMin = rightMin[L + 1];
  }

  return L + 1;
}

int main() {
  std::vector<int> vec = {5, 0, 3, 8, 6};
  std::cout << partitionDisjoint(vec) << std::endl;
  return 0;
}

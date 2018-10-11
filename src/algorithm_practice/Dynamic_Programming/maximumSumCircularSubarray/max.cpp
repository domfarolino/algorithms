#include <iostream>
#include <algorithm>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-105/problems/maximum-sum-circular-subarray/

/**
 * Maximum Sum Circular Subarray
 * This is a nifty modification of the more-generic maximum sum
 * subarray problem. Since the array we're dealing with in this case
 * is "circular", really the only thing that changes is that we must now
 * consider the subarray [i, n - 1] + [0, j] as the possible maximum sum
 * subarray.
 *
 * We can make the observation that when the maximum subarray spans the edges of the given
 * array, all of the elements in the middle comprise the minimum subarray that does not span
 * the edges. So what we can do is go find the regular max subarray given a method such as Kadane's
 * algorithm, and then also find the minimum subarray the same way, just with backwards logic. The idea
 * is that if the true subarray spans across the edges of the array, and is not the max subarray we found
 * via the usual means, then the array we found via the usual means is only a subset of the real one, and
 * the real max subarray sum can be found by totalArraySum - minimumSubArray. If the max subarray we found
 * via the usual means happens to be the actual max subarray, then the totalArraySum - minimumSubArray will
 * be some smaller value. Thus we can collect both of these values and return the larger of the two. There is
 * a tricky edge case however, when the array is filled entirely with negative numbers, or in other words, when
 * the max subarray sum found via the usual means is negative. In this case, that value is the best we can do,
 * and the _entire_ array is the minumum subarray. Therefore totalArraySum - minimumSubArray will be 0, and is a
 * false answer to our problem.
 *
 * Complexity analysis
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

int maxSumCircularSubarray(const std::vector<int>& vec) {
  // Edge case that would be good to clarify.
  if (!vec.size()) return 0;

  // Get the total sum.
  // Note: we could perform all of the logic in this function in
  // a single for loop, but I find this more clear.
  int totalSum = 0;
  for (int val: vec)
    totalSum += val;

  // Find the normal max subarray sum.
  int currSum = 0, maxSum = INT_MIN;
  for (int val: vec) {
    currSum = std::max(currSum + val, val);
    maxSum = std::max(currSum, maxSum);
  }

  currSum = 0;
  int minSum = INT_MAX;
  for (int val: vec) {
    currSum = std::min(currSum + val, val);
    minSum = std::min(currSum, minSum);
  }

  if (maxSum < 0) return maxSum;
  return std::max(maxSum, totalSum - minSum);
}

int main() {
  std::vector<int> vec = {5, -3, 5};
  std::cout << maxSumCircularSubarray(vec) << std::endl;
  return 0;
}

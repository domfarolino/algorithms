#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <cstdlib>

// Source: CLRS Chatper 4 Section 1
// Source: https://leetcode.com/problems/maximum-subarray/description/
// Source: https://blog.domfarolino.com/Maximum-Subarray-Study/

/**
 * Maximum Subarray
 * This is a really interesting and important problem. For a complete
 * problem description, see the Leetcode link above. For a complete solution
 * read the README in this directory explaining Kadane's algorithm, and see the
 * link to my blog post above.
 */

/**
 * Naive maximum subarray algorithm
 * Theta(n^2) by looking at every contiguous
 * subarray in the entire array A[low, ..., high]
 */
std::tuple<int, int, int> maximumSubarrayNaive(const std::vector<int> &nums) {
  int sum = INT_MIN, currentSum, subArrayStart, subArrayEnd;
  
  for (int i = 0; i < nums.size(); ++i) {
    currentSum = 0;
    for (int j = i; j < nums.size(); ++j) {
      currentSum += nums[j];
      if (currentSum > sum) {
        sum = currentSum;
        subArrayStart = i;
        subArrayEnd = j;
      }
    }
  
  }

  return std::make_tuple(subArrayStart, subArrayEnd, sum);
}

/**
 * Dynamic programming.
 * This algorithm embodies
 * the technique of keeping track
 * of the maxSubarray we have come
 * accross thus far. This gives us a
 * one-pass O(n) solution, and is essentially
 * Kadane's max sum subarray algorithm.
 */
std::tuple<int, int, int> maximumSubarrayLinear(const std::vector<int> &nums) {
  if (!nums.size()) return std::make_tuple(0, 0, 0);
  int currStartIndex, currEndIndex, startIndex, endIndex;
  int maxSum = INT_MIN, currSum = 0;

  for (int i = 0; i < nums.size(); i++) {
    if (currSum + nums[i] < nums[i]) {
      // Here, having currSum be the subarray that may end with nums[i] is
      // actually less beneficial than just starting over with a new subarray @ i.
      currStartIndex = i;
      currSum = nums[i];
    } else {
      // Update the existing subarray we're trying out to now include nums[i]
      currSum += nums[i];
    }

    endIndex = i;
    if (currSum > maxSum) {
      maxSum = currSum;
      startIndex = currStartIndex;
      endIndex = currEndIndex;
    }
  }

  return std::make_tuple(startIndex, endIndex, maxSum);
}

// TODO(domfarolino): Consider adding the divide and conquer solution from CLRS.
int main() {
  srand(0);
  std::vector<int> a;
  std::vector<int> b;

  int s = 2000;
  std::cout << "# Size" << '\t' << "Naive" << '\t' << /*"Divide and Conquer" <<*/ "Linear" << std::endl;
  int push;
  for (int i = 2; i <= s; i+=2) {
    for (int j = 0; j < i; ++j) {
      push = rand() % 20000;
      if (rand() % 3) push *= -1;
      a.push_back(push);
    }
      clock_t clock_a_start = clock();
      maximumSubarrayNaive(a);
      clock_t clock_a_stop = clock();

      /*
      clock_t clock_b_start = clock();
      maximumSubarrayDivideAndConquer(a, 0, a.size()-1);
      clock_t clock_b_stop = clock();
      */

      clock_t clock_c_start = clock();
      maximumSubarrayLinear(a);
      clock_t clock_c_stop = clock();

      std::cout << i << '\t';
      std::cout << (float)(clock_a_stop - clock_a_start)/(CLOCKS_PER_SEC/1000) << '\t';
      //std::cout << (float)(clock_b_stop - clock_b_start)/(CLOCKS_PER_SEC/1000) << '\t';
      std::cout << (float)(clock_c_stop - clock_c_start)/(CLOCKS_PER_SEC/1000) << std::endl;

      a.clear();
  }

  return 0;
}

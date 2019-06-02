#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

// Source: https://leetcode.com/contest/smarking-algorithm-contest-3/problems/minimum-moves-to-equal-array-elements/
// Source: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/

/**
 * Minimum Moves to Equal Array Elements
 * This is a pretty cool algorithm. I knew
 * there had to be a simpler and more efficient
 * algorithm than actually going through all of the
 * steps. I then started laying out some simple examples
 * to see what the finishing number would be in arrays with
 * different numbers. To see exactly how the differences in array
 * elements affects the highest number each element in the array will
 * attain in the final step, I used some of the following examples:

    // [1, 4]
    // [2, 4]
    // [3, 4]
    // [4, 4]

    // [1, 1, 4]
    // [2, 2, 4]
    // [3, 3, 4]
    // [4, 4, 4]

    // [1, 2, 4]
    // [2, 3, 4]
    // [3, 4, 4]
    // [4, 4, 5]
    // [5, 5, 5]

    // [1, 2, 2, 4]
    // [2, 3, 3, 4]
    // [3, 4, 4, 4]
    // [4, 4, 5, 5]
    // [5, 5, 5, 6]
    // [6, 6, 6, 6]

    // [1, 3, 4]
    // [2, 4, 4]
    // [3, 4, 5]
    // [4, 5, 5]
    // [5, 5, 6]
    // [6, 6, 6]

    // [1, 4, 4]
    // [2, 4, 5]
    // [3, 5, 5]
    // [4, 5, 6]
    // [5, 6, 6]
    // [6, 6, 7]
    // [7, 7, 7]

    // [1, 4, 4, 4]
    // [2, 4, 5, 5]
    // [3, 5, 5, 6]
    // [4, 6, 6, 6]
    // [5, 6, 7, 7]
    // [6, 7, 7, 8]
    // [7, 8, 8, 8]
    // [8, 8, 9, 9]
    // [9, 9, 9, 10]
    // [10, 10, 10, 10]
 *
 * See below algorithms for complexity analysis
 *
 */

/**
 * Some of the documentation that relates to the idea behind
 * this non-optimal algorithm can be found below, in the docs
 * for the optimal algorithm.
 *
 * Complexity analysis:
 * Time complexity: O(nlog(n))
 * Space complexity: depends on implementation of sort
 */
int minMovesSort(std::vector<int>& nums) {
  sort(nums.begin(), nums.end());
  int minimum = nums[0], maximum = nums[nums.size() - 1];

  int retMoves = maximum - minimum + 1;

  for (int i = 1; i < nums.size() - 1; ++i) {
    retMoves += nums[i] - minimum;
  }

  return retMoves - 1;
}

/**
 * This solution utilizes the fact that each non-min element
 * has an effect on the number of moves it will take. My original
 * "breakthrough" with this problem exploited the fact that we know
 * for a fact we will take *at least* |max - min + 1| moves, because
 * of the "range" of the array, and each non-min value could contribute
 * more moves, proportional to its distance from |min|. Therefore we can
 * set |moves| equal to this value initially, and iterate through the values
 * adjusting |moves| (incrementing) when necessary. We have to do this for all
 * duplicates of |max| too, instead of the one we just counted. This required
 * keeping track of the-|max|-we-first-counted's location. But this is more work.
 * Instead it is easier to just not count it first, and go through the entire array
 * adjusting |moves| as necessary, and not worrying about double-counting any value.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
int minMovesLeaner(std::vector<int>& nums) {
  int moves = 0, min = INT_MAX, max = INT_MIN;
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i] < min) min = nums[i];
  }

  for (int i = 0; i < nums.size(); ++i) {
    moves += (nums[i] - min);
  }

  return moves;
}

int main() {
  // Good test cases:
  // [1, 4]
  // [1, 1, 4]
  // [1, 2, 4]
  // [1, 2, 2, 4]
  // [1, 3, 4]
  // [0, 1, 3]

  std::vector<int> inputVec = {1, 1, 2, 3, 4, 5, 5, 6, 6}; // -std=c++0x
  std::cout << minMovesSort(inputVec) << std::endl;
  std::cout << minMoves(inputVec) << std::endl;
  std::cout << minMovesLeaner(inputVec) << std::endl;

  return 0;
}

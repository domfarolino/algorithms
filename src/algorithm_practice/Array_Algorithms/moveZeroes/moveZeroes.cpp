#include <iostream>
#include <vector>

using namespace std;

// Source: https://leetcode.com/problems/move-zeroes/

/* Move Zeroes
 * This algorithm is designed to push all non-zero
 * numbers in some vector to the beginning while maintaining
 * their relative order. The zeroes in the vector should occupy
 * the final remaining elements of the array.
 *
 * We can start with a for loop that iterates through each element of
 * the array/vector checking if the current element is non-zero. If the
 * current element (array[i]) is non-zero we want to write it in the first
 * possible place in the array. This means we'll maintain a second counter
 * variable (j) to keep track of the earliest place we can write a number to.
 * Every time we encounter a non-zero element we set array[j] = array[i], and
 * increment j. When our loop is finished, all of the non-zeroes will be pushed
 * to the beginning of the array however we may still have elements after index j
 * that are non-zero, just as they were when we first got the array. This means after
 * our loop we should run through all the elements [j...n-1] and set all the values = 0.
 * Note we can get around this extra loop at the end of the algorithm by setting array[i]
 * to 0 after we set array[j] = array[i]. Be careful! We only want to set array[i] = 0 after
 * this assignment if i != j. The test case with the array [1] will catch this bug!
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

// 2015
// void moveZeroes(vector<int>& nums) {
//   int current = 0;
//   for (unsigned int i = 0; i < nums.size(); ++i) {
//     if (nums[i] != 0) nums[current++] = nums[i];
//   }
//   while(current != nums.size()) nums[current++] = 0;
// }

void moveZeroesWithLoop(vector<int>& nums) {
  int j = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i]) {
      nums[j] = nums[i];
      j++;
    }
  }

  // j && ... so that we can stop if j == 0
  for (j; j && j < nums.size(); ++j) {
    nums[j] = 0;
  }
}

void moveZeroes(vector<int>& nums) {
  int j = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i]) {
      nums[j] = nums[i];
      // This extra check below prevents
      // us from needing a second loop in
      // our algorithm
      if (i - j) nums[i] = 0;
      j++;
    }
  }
}

int main() {
  vector<int> test;
  test.push_back(1);
  test.push_back(0);
  test.push_back(0);
  test.push_back(1);

  moveZeroes(test);

  for (int i = 0; i < test.size(); ++i) {
    cout << test[i] << " ";
  }

  cout << endl;

  return 0;
}

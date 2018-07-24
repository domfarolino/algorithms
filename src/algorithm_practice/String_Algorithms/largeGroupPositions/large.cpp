#include <iostream>
#include <vector>
#include <string>

// Source: https://leetcode.com/contest/weekly-contest-83/problems/positions-of-large-groups/

/**
 * Large Group Positions
 * Inch-worm kinda problem. Relatively simple, just maintain two counter (index) variables,
 * advance the "end" one forward while we're looking at the same character as the start. If
 * the length of the range when we're finished is >= 3, store the state of the counter variables
 * (or something derived from them, for example, e - 1 in the below case), and start over from where
 * the end counter variable left off. Don't run off the end of the array!
 *
 * Complexity analysis:
 * Time complexity: O(n) (single pass inch-worm)
 * Space complexity: O(1)
 */

std::vector<std::vector<int> > largeGroupPositions(const std::string& input) {
  std::vector<std::vector<int> > returnVec;
  int s = 0, e = 0;

  while (1) {
    // Find the length of the current group starting at index |s|
    while (e < input.length() && input[s] == input[e]) e++;

    if (e - s >= 3) {
      std::vector<int> newMember = {s, e - 1};
      returnVec.push_back(newMember);
    }

    s = e;
    if (e >= input.length()) break;
  }

  return returnVec;
}

int main() {
  std::string input = "aaabbaaaaabbbbbaaxxcccc";
  std::vector<std::vector<int> > resultVec = largeGroupPositions(input);

  std::cout << "[";
  for (int i = 0; i < resultVec.size(); ++i) {
    std::cout << "[" << resultVec[i][0] << "," << resultVec[i][1] << "], ";
  }
  std::cout << "]" << std::endl;

  return 0;
}

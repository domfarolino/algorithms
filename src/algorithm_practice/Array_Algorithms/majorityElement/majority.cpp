#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/majority-element/description/
// Source: https://www.geeksforgeeks.org/majority-element/
// Berman's Advanced Algorithm I Class

int majorityElement(std::vector<int>& nums) {
  int returnElement = nums[0];
  int count = 1;

  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i] == returnElement) {
      count++;
    } else {
      if (count == 1) returnElement = nums[i];
      else count--;
    }
  }

  return returnElement;
}

int main() {
  std::vector<int> arr = {4, 2, 2, 2, 3};
  std::cout << majorityElement(arr) << std::endl;
  return 0;
}

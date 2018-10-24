#include <iostream>
#include <unordered_map>
#include <vector>

// Source: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

int binarySearch(const std::vector<int>& arr, int l, int r, int val) {
  int m;
  while (l <= r) {
    m = (l + r) / 2;
    if (arr[m] < val) {
      l = m + 1;
    } else if (arr[m] > val) {
      r = m - 1;
    } else {
      return m;
    }
  }

  return -1;
}

std::vector<int> twoSum(const std::vector<int>& nums, int k) {
  std::vector<int> returnVec;
  std::unordered_map<int, int> uMap;
  int tmp;

  for (int i = 0; i < nums.size(); ++i) {
    tmp = binarySearch(nums, i + 1, nums.size() - 1, k - nums[i]);
    if (tmp != -1) {
      returnVec.push_back(i);
      returnVec.push_back(tmp);
      break;
    }
  }

  return returnVec;
}

int main() {
  std::vector<int> a = {1, 2, 4, 4}, b = {2, 2, 6};
  std::vector<int> result = twoSum(a, 8);

  std::cout << result[0] << ", " << result[1] << std::endl;
  result = twoSum(b, 8);
  std::cout << result[0] << ", " << result[1] << std::endl;
  return 0;
}

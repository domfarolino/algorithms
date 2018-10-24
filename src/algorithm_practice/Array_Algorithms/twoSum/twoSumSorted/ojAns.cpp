// Source: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

class Solution {
public:
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
      returnVec.push_back(i + 1);
      returnVec.push_back(tmp + 1);
      break;
    }
  }

  return returnVec;
}
};

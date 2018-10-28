// Source: https://leetcode.com/problems/3sum/description/

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
      } else
        return m;
    }

    return -1;
  }

  vector<vector<int>> threeSum(vector<int>& nums) {
    std::vector<std::vector<int>> returnVec;
    std::sort(nums.begin(), nums.end());

    int tmp, find;
    for (int i = 0; i < int(nums.size()) - 1; ++i) {
      if (i != 0 && nums[i] == nums[i - 1]) continue;
      for (int j = i + 1; j < nums.size(); ++j) {
        if (j != i + 1 && nums[j] == nums[j - 1]) continue;
        tmp = nums[i] + nums[j];
        find = binarySearch(nums, j + 1, nums.size() - 1, -tmp);
        if (find != -1) {
          std::vector<int> newVec = {nums[i], nums[j], nums[find]};
          returnVec.push_back(newVec);
        }
      }
    }
    return returnVec;
  }
};

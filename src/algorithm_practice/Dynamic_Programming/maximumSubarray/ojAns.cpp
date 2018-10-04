// Source: https://leetcode.com/problems/maximum-subarray/description/

class Solution {
public:
int maxSubArray(const std::vector<int> &nums) {
  if (!nums.size()) return 0;
  int maxSum = INT_MIN, currSum = 0;

  for (int i = 0; i < nums.size(); i++) {
    if (currSum + nums[i] < nums[i])
      currSum = nums[i];
    else
      currSum += nums[i];

    maxSum = max(maxSum, currSum);
  }

  return maxSum;
}
  
};

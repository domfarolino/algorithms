// Source: https://leetcode.com/problems/maximum-sum-circular-subarray/description/

class Solution {
public:
int maxSubarraySumCircular(const std::vector<int>& vec) {
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
};

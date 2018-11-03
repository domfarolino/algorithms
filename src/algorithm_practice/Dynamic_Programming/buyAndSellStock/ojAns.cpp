// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

class Solution {
public:
  int maxProfit(const std::vector<int>& arr) {
  int maxProf = 0, low = 0, high = 0;
  if (arr.size() == 1) return maxProf;

  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i] > arr[high])
      high = i;
    else if (arr[i] < arr[low]) {
      low = i;
      high = i;
    }

  if (arr[high] - arr[low] > maxProf)
    maxProf = arr[high] - arr[low];
  }

  return maxProf;
}
};

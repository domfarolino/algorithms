#include <iostream>
#include <algorithm>
#include <vector>

// Source: https://leetcode.com/problems/min-cost-climbing-stairs/description/

int minCostClimbingStairs(std::vector<int>& cost) {
  // Assert cost.size() >= 2
  
  for (int i = 2; i < cost.size(); ++i) {
    cost[i] = std::min(cost[i - 2], cost[i - 1]) + cost[i];
  }

  return std::min(cost[cost.size() - 2], cost[cost.size() - 1]);
}

int main() {
  std::vector<int> steps = {5, 6};
  std::cout << minCostClimbingStairs(steps) << std::endl;
  steps = {5, 6, 10};
  std::cout << minCostClimbingStairs(steps) << std::endl;
  steps = {5, 6, 5, 0};
  std::cout << minCostClimbingStairs(steps) << std::endl;
  steps = {5, 6, 3, 1};
  std::cout << minCostClimbingStairs(steps) << std::endl;
  return 0;
}

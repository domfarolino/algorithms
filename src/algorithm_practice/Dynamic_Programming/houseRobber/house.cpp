#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/house-robber/description/

int rob(std::vector<int>& loots) {
  if (!loots.size()) return 0;
  // Assert: nums.size() >= 1

  if (loots.size() > 1)
    loots[1] = std::max(loots[1], loots[0]);

  for (int i = 2; i < loots.size(); ++i) {
    loots[i] = std::max(loots[i - 2] + loots[i], loots[i - 1]);
  }

  return loots[loots.size() - 1];
}

int main() {
  std::vector<int> loots = {2};
  std::cout << rob(loots) << std::endl;
  loots = {2, 1};
  std::cout << rob(loots) << std::endl;
  loots = {1, 2};
  std::cout << rob(loots) << std::endl;
  loots = {8, 10, 9, 40};
  std::cout << rob(loots) << std::endl;
  loots = {8, 10, 9, 1};
  std::cout << rob(loots) << std::endl;
  loots = {8, 10, 9, 1, 1};
  std::cout << rob(loots) << std::endl;
  return 0;
}

#include <iostream>
#include <vector>

// Source: Modification of https://leetcode.com/problems/house-robber/description/
// Source: Related: https://leetcode.com/problems/min-cost-climbing-stairs/description/

std::vector<int> rob(std::vector<int>& loots) {
  std::vector<int> first, second;
  if (!loots.size()) return second;
  // Assert: nums.size() >= 1

  first = {loots[0]};

  if (loots.size() > 1) {
    loots[1] = std::max(loots[1], loots[0]);
    second = {loots[1]};
  } else second = first; // Second should always be non-empty since it is what we're returning.

  for (int i = 2; i < loots.size(); ++i) {
    if (loots[i - 2] + loots[i] > loots[i - 1]) {
      first.push_back(loots[i]);
      std::swap(first, second);
      loots[i] += loots[i - 2];
    } else {
      loots[i] = loots[i - 1];
      first = second;
    }
  }

  return second;
}

void printVec(const std::vector<int>& vec) {
  for (const int& val: vec) {
    std::cout << val << ", ";
  }

  std::cout << std::endl;
}

int main() {
  std::vector<int> loots = {2};
  printVec(rob(loots));
  loots = {2, 1};
  printVec(rob(loots));
  loots = {1, 2};
  printVec(rob(loots));
  loots = {8, 10, 9, 40};
  printVec(rob(loots));
  loots = {8, 10, 9, 1};
  printVec(rob(loots));
  loots = {8, 10, 9, 1, 1};
  printVec(rob(loots));
  return 0;
}

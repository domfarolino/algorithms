#include <iostream>

// Source: https://leetcode.com/problems/climbing-stairs/description/

// Simple iterative fibonacci.
int climbStairs(int n) {
  int first = 1, second = 2, tmp;
  while (n > 1) {
    tmp = second + first;
    first = second;
    second = tmp;
    n--;
  }

  return first;
}

int main() {
  for (int i = 0; i < 8; ++i) {
    std::cout << climbStairs(i) << std::endl;
  }

  return 0;
}

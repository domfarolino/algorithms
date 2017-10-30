#include <iostream>

// Source: https://leetcode.com/problems/happy-number/

/**
 * A happy number is a number defined by the following process:
 * Starting with any positive integer, replace the number by the
 * sum of the squares of its digits, and repeat the process until
 * the number = 1 (where it will remain), or it loops endlessly in
 * a cycle which never includes 1. Those numbers for which this process
 * ends in 1 are happy numbers. We need some way to tell whether a number
 * gets repeated (and is in the infinite cycle, thus not happy). We could
 * use an unordered_set for this, however previous research shows that repeated
 * numbers will never go above 999, therefore we could keep a boolean array to act
 * as our set. Everytime we come across a number we set its value in our array to true
 * and every time we come across a number, if its index in our array has ever been set
 * to true we know this number is unhappy and can quit trying.
 */

bool isHappy(int n) {
  bool set[1000] = {false};
  int tmp;

  while (n != 1) {
    tmp = 0;

    while (n) {
      tmp += (n % 10)*(n % 10);
      n /= 10;
    }

    n = tmp;

    // Can work with our set if n < 1000
    if (n < 1000) {
      if (set[n]) return false;
      else set[n]++;
    }
  }

  return true;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << isHappy(n) << std::endl;
  return 0;
}

#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/self-dividing-numbers/

/**
 * The basis of this problem is fairly simple and naive
 * however there is one trick. So basically we want to,
 * for every number in the given range, test to see whether
 * it is a self-dividing number. We can factor the self-dividing
 * number test that works on an individual number out into another
 * function.
 *
 * This entails checking each digit inside a given number in
 * our aforementioned range. We can do this easily by keeping
 * a temporary number that is initially equal to the given number
 * we're testing. We'll check to see if the given number is divisible
 * by tmp % 10 if it ever isn't, we'll want to return false since we found
 * some digit inside the given number that our given number is not divisible
 * by.
 *
 * TODO(domfarolino): write about complexity and random edge case
 */

bool isSelfDividingNumber(int num) {
  int tmp = num;

  while (tmp) {
    if (!(tmp % 10) || num % (tmp % 10)) return false;
    tmp /= 10;
  }

  return true;
}

std::vector<int> selfDividingNumbers(int left, int right) {
  std::vector<int> returnVec;

  for (int i = left; i <= right; i++) {
    if (isSelfDividingNumber(i)) returnVec.push_back(i);
  }

  return returnVec;
}

void printVector(const std::vector<int>& vec) {
  std::cout << "[";

  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i];
    if (i + 1 < vec.size()) std::cout << ",";
  }

  std::cout << "]" << std::endl;
}

int main() {
  int num, left, right;
  std::vector<int> out;
  std::cin >> num;

  for (int i = 0; i < num; i++) {
    std::cin >> left >> right;
    out = selfDividingNumbers(left, right);
    printVector(out);
  }

  return 0;
}

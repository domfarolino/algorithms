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
 * by. The catch (something I first did not consider) how to handle our tmp variable
 * when it is equal to 0. For example, if a given number was `208`, eventually our tmp
 * will be `20`, and we'll be testing to see if `num % (tmp % 10)`. In this case however
 * `tmp % 10` is 0 since our reduced tmp variable is divisible by 10. In this case we'll
 * get a divide-by-zero error when evaluating `num % 0`. In this case we want to catch the
 * case where `tmp % 10` early so we don't accidentally dip into a situation where we divide
 * by zero. This is nice because it provides the behavior that we might expect if we didn't
 * expect `(num % (tmp % 10))` to throw an error. Of course any number that has a 0 in its digits
 * is not a self-dividing number.
 *
 * Time complexity: O(left - right)
 *   For each (left - right) number we perform the isSelfDividingNumber. The isSelfDividingNumber check
 *   performs O(log(k)) steps where `k` is the given number. Since we know the maximum number in our range
 *   (being 10000) this makes the complexity of this routine O(log(10000)), which is O(1) since we're dealing
 *   with a constant.
 * Space complexity: O(left - right)
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

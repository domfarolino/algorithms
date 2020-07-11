#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

// Source:
//   - https://www.hackerrank.com/contests/world-codesprint-6/challenges/bonetrousle
//   - https://www.hackerrank.com/challenges/bonetrousle/problem

/**
 * Bonetrousle
 * This is a really cool problem. The theory behind it is
 * rather simple after a couple of realizations are made. At
 * first however, I thought this was a DP problem, maybe something
 * similar to the minimum coin sum problem. I then realized it us much
 * simpler than that. The first realization I made was that we can easily
 * tell whether a solution even exists or not. We know the minimum number of
 * sticks of pasta we can buy has to be 1 + 2 + 3 + ... + B. This means the maximum
 * number of sticks of pasta we can buy is K + K-1 + K-2 + K-(B-1). Since changing some
 * box to one of its adjacent neighbors only adjusts the total sum by 1, it as long as `n`,
 * the desired number of sticks of pasta falls within the maximum and minimum sums, we can
 * guarantee that a solution will exist. In this case, we can move on. My first thought for
 * finding a solution was defaulting all of the box choices to 1 + 2 + 3 + ... + B, and while
 * our sum < n, we take the last box and change it from its default value to some box number that
 * optimizes our sum. This value will be < k if it makes sum = n, or will top out at k to get us as
 * close as possible. If still sum < n, we look at the next highest box and we again change its value
 * to optimize our sum. Note the higest value we can make this second custom box, is k-1 since we already
 * have one box at value k. This is something to watch out for. Further, when changing some default box value
 * to a custom one, we have to remember to subtract the default box value from our sum before adding the custom
 * value or else we artificially inflate our sum.
 *
 * In my first implementation of this problem, I am storing all of the custom box values so I can print through
 * them later. This means the number of default boxes will be B - customBoxes.size(). I later realized that I don't
 * actually have to store them for later printing. Instead I can print them as I calculate them. In this case I'll just
 * need to keep track of how many custom box values have been printed, and the value of the most recent one, so I know my
 * upper boundary for future boxes.
 */

unsigned long long sumFirstNums(const unsigned long long &x) {
  return (x * (x + 1)) / 2;
}

unsigned long long sumLastNums(const unsigned long long& lastNum, const unsigned long long& howMany) {
  unsigned long long returnSum = 0;
  for (unsigned long long i = 0; i < howMany; ++i) {
    returnSum += lastNum - i;
  }

  return returnSum;
}

void printAnswerExtraSpace(const unsigned long long &n, const unsigned long long &k, const unsigned long long &b) {
  if (sumFirstNums(b) > n || sumLastNums(k, b) < n) {
    std::cout << "-1";
  } else {
    unsigned long long sum = sumFirstNums(b);
    unsigned long long valToAdd = k + 1; // 1 more than the max value we can add for our first custom box
    std::vector<unsigned long long> customBoxes;

    while (sum < n) {
      // subtract last box value
      sum -= (b - customBoxes.size());

      // add largest value we need
      valToAdd = std::min(n - sum, valToAdd-1);

      sum += valToAdd;
      customBoxes.push_back(valToAdd);
    }

    for (unsigned long long i = 0; i < (b - customBoxes.size()); ++i) {
      std::cout << i+1;
      if (i != (b - customBoxes.size()-1) || customBoxes.size()) std::cout << " ";
    }

    for (unsigned long long i = 0; i < customBoxes.size(); ++i) {
      std::cout << customBoxes[i];
      if (i != customBoxes.size()-1) std::cout << " ";
    }
  }

  std::cout << '\n';
}

void printAnswerConstantSpace(const unsigned long long &n, const unsigned long long &k, const unsigned long long &b) {
  if (sumFirstNums(b) > n || sumLastNums(k, b) < n) {
    std::cout << "-1";
  } else {
    unsigned long long sum = sumFirstNums(b);
    unsigned long long valToAdd = k + 1;
    unsigned long long numCustomBoxes = 0;

    while (sum < n) {
      // subtract last box value
      sum -= (b - numCustomBoxes);

      // add largest value we need
      valToAdd = std::min(n - sum, valToAdd - 1);
      std::cout << valToAdd;

      sum += valToAdd;
      numCustomBoxes++;

      if (numCustomBoxes != b) std::cout << " ";
    }

    for (unsigned long long i = 0; i < (b - numCustomBoxes); ++i) {
      std::cout << i + 1;
      if (i != (b - numCustomBoxes - 1)) std::cout << " ";
    }

  }

  std::cout << '\n';
}

int main() {
  int t;
  std::cin >> t;
  unsigned long long n, k, b;

  std::cout << std::fixed << std::setprecision(0);

  for (int i = 0; i < t; ++i) {
    std::cin >> n >> k >> b;
    //printAnswerExtraSpace(n, k, b);
    printAnswerConstantSpace(n, k, b);
  }

  return 0;
}

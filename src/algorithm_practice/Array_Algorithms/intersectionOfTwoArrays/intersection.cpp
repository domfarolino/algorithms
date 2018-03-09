#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <unordered_set>

// Source: https://leetcode.com/problems/intersection-of-two-arrays/

/**
 * Intersection of Two Arrays
 * This is a pretty interesting problem. Two obvious solutions
 * surfaced for me, one of which is a linear time hashing solution
 * and the other was a O(nlog(n)) sorting and iterating based solution
 * GDoc writeup of my thoughts can be found here:
 * https://docs.google.com/document/d/14XTvLPcKRSUGka-v_u9rItGlI4AAHsASe_bwvcfwwf0/edit?usp=sharing
 */

// We use this helper to guarantee that `a` is the smaller element here
// This gives us O(min(|a|, |b|)) space complexity
std::vector<int> intersectionOfTwoArraysHashingHelper(const std::vector<int>& a, const std::vector<int>& b) {
  std::unordered_set<int> uSet;
  std::vector<int> returnVector;

  for (int i = 0; i < a.size(); ++i) {
    uSet.insert(a[i]);
  }

  for (int i = 0; i < b.size(); ++i) {
    if (uSet.find(b[i]) != uSet.end()) {
      returnVector.push_back(b[i]);
      uSet.erase(uSet.find(b[i]));
    }
  }

  return returnVector;
}

/**
 * Time complexity: O(a + b)
 * Space complexity: O(min(|a|, |b|))
 */
std::vector<int> intersectionOfTwoArraysHashing(std::vector<int>& a, std::vector<int>& b) {
  if (a.size() < b.size()) {
    return intersectionOfTwoArraysHashingHelper(a, b);
  } else {
    return intersectionOfTwoArraysHashingHelper(b, a);
  }
}

/**
 * Time complexity: O(nlog(n))
 * Space complexity: O(n)
 */
std::vector<int> intersectionOfTwoArraysSorting(std::vector<int>& a, std::vector<int>& b) {
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  std::vector<int> returnVector;

  // Counter variable for vector `b`
  int i = 0, j = 0;

  while (i < a.size() && j < b.size()) {
    if (a[i] == b[j]) {
      if (!i || a[i-1] != a[i]) returnVector.push_back(a[i]);
      i++;
      j++;
    } else if (a[i] > b[j]) {
      j++;
    } else {
      i++;
    }
  }

  return returnVector;
}

int main() {
  std::vector<int> a = {1, 2, 2, 1}, b = {2, 2};
  std::vector<int> intersectionFromHashing = intersectionOfTwoArraysHashing(a, b);
  std::vector<int> intersectionFromSorting = intersectionOfTwoArraysSorting(a, b);

  for (int i = 0; i < intersectionFromHashing.size(); ++i) {
    std::cout << intersectionFromHashing[i] << ", ";
  }

  std::cout << std::endl;

  for (int i = 0; i < intersectionFromSorting.size(); ++i) {
    std::cout << intersectionFromSorting[i] << ", ";
  }

  std::cout << std::endl;
  return 0;
}

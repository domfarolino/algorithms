#include <iostream>
#include <vector>

#include "binarySearchOccurrences.h"
#include "binarySearchOccurrencesRecursive.h"

/**
 * Driver program to test out the "first occurrence" and "last occurrence"
 * recursive and iterative variants, of good ole vanilla binary search. Please
 * use with piped stdin from `test.in`.
 */

int main() {
  int total, length, needle, tmp;
  std::vector<int> haystack;

  std::cin >> total;

  for (int i = 0; i < total; ++i) {
    std::cin >> length >> needle;
    haystack.reserve(length);

    for (int j = 0; j < length; ++j) {
      std::cin >> tmp;
      haystack.push_back(tmp);
    }

    std::cout << firstOccurrence(haystack, needle) << std::endl;
    std::cout << firstOccurrenceRecursive(haystack, 0, haystack.size() - 1, needle) << std::endl;
    std::cout << lastOccurrence(haystack, needle) << std::endl;
    std::cout << lastOccurrenceRecursive(haystack, 0, haystack.size() - 1, needle) << std::endl;
    haystack.clear();
  }

  return 0;
}

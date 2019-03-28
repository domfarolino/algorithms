#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/permutations/description/

/**
 * This file contains three independent implementations of functions
 * that generate all permutations of a given set† of distinct items.
 * The word "distinct" is relevant, because these algorithms will
 * generate "duplicate" permutations if the given values are non-distinct.
 *
 * † The algorithms all take in STL iterable data structures that support
 * the ::insert() method, meaning they operate on a std::string just as
 * they would a std::vector, etc.
 */

// Implementation #1.
template <typename T>
std::vector<T> permute(const T& items, int index = 0) {
  // Assert: items is a distinct set of items.

  std::vector<T> permutations;

  if (index >= items.size()) return permutations;
  if (index == items.size() - 1) {
    T base;
    base.insert(base.end(), items[index]);
    permutations.push_back(base);
    return permutations;
  }

  std::vector<T> sub_permutations;
  sub_permutations = permute(items, index + 1);

  for (int insert_idx = 0; insert_idx < items.size() - index; ++insert_idx) {
    for (T permutation: sub_permutations) {
      permutation.insert(permutation.begin() + insert_idx, items[index]);
      permutations.push_back(permutation);
    }
  }

  return permutations;
}

// Implementation #2.
template <typename T>
std::vector<T> permute_ordered(T items) {
  // Assert: items is a distinct set of items.

  std::vector<T> permutations;

  if (items.size() == 0) return permutations;
  if (items.size() == 1) {
    permutations.push_back(items);
    return permutations;
  }

  std::vector<T> sub_permutations;
  T sub_items;
  for (int i = 0; i < items.size(); ++i) {
    // Item at index |i| is the value to add to beginning of sub-permutations.
    // We should generate all permutations of the _rest_ of the items.
    sub_items.insert(sub_items.end(), items.begin(), items.begin() + i); // [0, i).
    sub_items.insert(sub_items.end(), items.begin() + i + 1, items.end()); // [i + 1, size).
    sub_permutations = permute(sub_items);

    for (T permutation: sub_permutations) {
      permutation.insert(permutation.begin(), items[i]);
      permutations.push_back(permutation);
    }

    sub_items.clear();
  }

  return permutations;
}

// Implementation #3.
template <typename T>
void permute_helper(T& items, std::vector<T>& permutations, int start) {
  if (start == items.size() - 1) {
    permutations.push_back(items);
    return;
  }

  for (int i = start; i < items.size(); ++i) {
    std::swap(items[start], items[i]);
    permute_helper(items, permutations, start + 1);
    std::swap(items[start], items[i]);
  }
}

template <typename T>
std::vector<T> permute2(T& items) {
  std::vector<T> permutations;
  permute_helper<T>(items, permutations, 0);
  return permutations;
}

int main() {
  std::string input1 = "ABCD";
  std::vector<std::string> permutations1 = permute(input1);

  std::vector<int> input2 = {1, 2, 3, 4};
  std::vector<std::vector<int>> permutations2 = permute(input2);

  std::cout << "Printing " << permutations1.size() << " permutations" << std::endl;
  for (const std::string& permutation: permutations1)
    std::cout << permutation << std::endl;

  std::cout << "Printing " << permutations2.size() << " permutations" << std::endl;
  for (const std::vector<int>& permutation: permutations2) {
    for (const int& member: permutation)
      std::cout << member << ", ";

    std::cout << std::endl;
  }

  return 0;
}

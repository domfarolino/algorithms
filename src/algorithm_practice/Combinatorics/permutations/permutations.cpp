#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/permutations/description/

template <typename T>
std::vector<std::vector<T>> permute(const std::vector<T>& items, int index = 0) {
  // Assert: items is a distinct set of items.

  std::vector<std::vector<T>> permutations;

  if (index >= items.size()) return permutations;
  if (index == items.size() - 1) {
    permutations.push_back({items[index]});
    return permutations;
  }

  std::vector<std::vector<T>> sub_permutations;
  sub_permutations = permute(items, index + 1);

  for (int insert_idx = 0; insert_idx < items.size() - index; ++insert_idx) {
    for (std::vector<T> permutation: sub_permutations) {
      permutation.insert(permutation.begin() + insert_idx, items[index]);
      permutations.push_back(permutation);
    }
  }

  return permutations;
}

template <typename T>
std::vector<std::vector<T>> permute_ordered(std::vector<T> items) {
  // Assert: items is a distinct set of items, length > 0.

  std::vector<std::vector<T>> permutations;

  if (items.size() == 0) return permutations;
  if (items.size() == 1) {
    permutations.push_back(items);
    return permutations;
  }

  std::vector<std::vector<T>> sub_permutations;
  std::vector<T> sub_items;
  for (int i = 0; i < items.size(); ++i) {
    // Item at index |i| is the value to add to beginning of sub-permutations.
    sub_items.insert(sub_items.end(), items.begin(), items.begin() + i);
    sub_items.insert(sub_items.end(), items.begin() + i + 1, items.end());
    sub_permutations = permute(sub_items);

    for (std::vector<T> permutation: sub_permutations) {
      permutation.insert(permutation.begin(), items[i]);
      permutations.push_back(permutation);
    }

    sub_items.clear();
  }

  return permutations;
}

int main() {
  std::vector<int> items = {1, 2, 3, 4};
  std::vector<std::vector<int>> permutations = permute(items);

  std::cout << "Printing " << permutations.size() << " permutations" << std::endl;
  for (const std::vector<int>& inner_vec: permutations) {

    for (const int& member: inner_vec) {
      std::cout << member << ", ";
    }

    std::cout << std::endl;

  }
  return 0;
}

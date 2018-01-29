#include <iostream>
#include <vector>
#include <algorithm>

// Source: CLRS

/**
 * Insertion sort algorithm
 * Overall thought process and formalities
 * Loop invariant: [S1, S2, ..., Si-1] is always in sorted order
 * Every time our outer loop comes across a new value we want to
 * place it in the previous array consisting of all original values
 * of [S1, S2, S3, ..., Si-1] in sorted order. If we find the correct
 * place for Si, then the array [S1, S2, S3, ..., Si] will now be sorted.
 * This loop invariant holds though every iteration of the loop from i = 1..n.
 * This means after the loop terminates finally, the entire array will consist
 * of the original elements in the input array in sorted order. More formally we
 * could prove that our inner while loop properly inserts a new value into the right
 * place in the sorted subarray.
 *
 * Simple sorting routine. We basically want to maintain a sorted
 * array and when we come across a new value, place the new value
 * in the sorted array then continue. Positioning a value in the
 * sorted array can happen one of two ways:
 *
 * Constantly swapping values until we don't need to anymore:
 *   [5, 6, 7, 4]
 * = [5, 6, 4, 7]
 * = [5, 4, 6, 7]
 * = [4, 5, 6, 7]
 *
 * Or we can keep shifting all the values up one until we don't need to anymore,
 * then just place the original key which we'll have to save separately because we
 * overwrote it with a shift, where it belongs:
 *   [5, 6, 7, 4] key = 4
 * = [5, 6, 7, 7]
 * = [5, 6, 6, 7]
 * = [5, 5, 6, 7]
 * = [4, 5, 6, 7]
 *
 *   [5, 7, 8, 6] key = 6
 * = [5, 7, 8, 8]
 * = [5, 7, 7, 8] * we compare key (6) with nums[j] (5) and stop
 * = [5, 6, 7, 8] * then overwite nums[j+1] with the key because the fits after nums[j] and was smaller than the prevoius nums[j+1]
 * Realize that if our value is already in the right place, nums[j+1] = key will technically do nothing
 */

void insertionSort(std::vector<int>& nums) {
  int j;
  for (int i = 1; i < nums.size(); ++i) {

    j = i - 1;
    while(j >= 0 && nums[j] > nums[j+1]) {
      std::swap(nums[j], nums[j+1]);
      j--;
    }
  }
}

// Corman solution
void insertionSortAlt(std::vector<int>& nums) {
  int j, key;
  for (int i = 1; i < nums.size(); ++i) {
    key = nums[i];

    j = i - 1;
    while(j >= 0 && nums[j] > key) {
      nums[j+1] = nums[j];
      j--;
    }

    nums[j+1] = key; // becuase nums[i] was most likely overwritten has been changed
  }
}

int main() {
  std::vector<int> v = {5, 7, 8, 6}; // -std=c++0x
  insertionSort(v);

  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i] << ", ";
  }

  std::cout << std::endl;
  return 0;
}

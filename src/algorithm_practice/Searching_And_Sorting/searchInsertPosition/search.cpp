#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/search-insert-position/

/**
 * Search Insert Position
 * Given a sorted array and a target value, return the index if
 * the target is found. If not, return the index where it would be
 * if it were inserted in order. You may assume no duplicates in the
 * array.
 *
 * This is basically binary search with some checking afterwards to determine
 * what exactly we're going to return. If the target element exists in the array
 * it is clear we don't actually have to anything outside of the normal binary search
 * behavior. When the target element doesn't exist, we get out of the main while loop
 * of the binary search algorithm in one of several ways. We know that our low and high
 * bounds have crossed, so we can tell where the new value should go by comparing it to
 * array[mid].
 *
 * If the left bound has jumped over the right bound, then we know ever value
 * from the indices 0...mid is less than our target, therefore we want to insert
 * target at mid + 1.
 *
 * If the right bound jumped lower than our lower bound, then we know every value from
 * indices mid...n-1 is higher than our target value, with arr[mid] being the smallest of
 * these. Inserting target at mid will shift all values larger than it to the right which is
 * exactly what we want to do, therefore we return mid.
 *
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 */

int search(const std::vector<int>& arr, int k) {
  if (!arr.size()) return 0;
  int l = 0, r = arr.size() - 1, m;

  while (l <= r) {
    m = (l + r) / 2;
    if (arr[m] < k) {
      l = m + 1;
    } else if (arr[m] > k) {
      r = m - 1;
    } else {
      return m;
    }
  }

  // return l; // this could allow us to not put the initial if statement
  if (arr[m] < k) return m + 1;
  else return m;
}

int main() {
  std::vector<int> arr = {1, 3, 5, 6};
  std::cout << search(arr, 5) << std::endl;
  return 0;
}

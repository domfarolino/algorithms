#include <vector>

/**
 * Iterative implementations of the "first occurrence" and "last occurrence"
 * binary search variants.
 * - First Occurrence
 * - Last Occurrrence
 * - Total number of occurrences ( = last - first + 1)
 *
 * Complexity analysis:
 * Time complexity: O(log(n))
 * Space complexity: O(1);
 */

int firstOccurrence(const std::vector<int>& arr, int value) {
  int left = 0, right = arr.size() - 1, mid;

  while (left <= right) {
    mid = left + (right - left) / 2;

    if (arr[mid] < value) {
      left = mid + 1;
    } else if (arr[mid] > value) {
      right = mid - 1;
    } else if (left != mid) {
      right = mid;
    } else {
      return mid;
    }
  }

  return -1;
}

int lastOccurrence(const std::vector<int>& arr, int value) {
  int left = 0, right = arr.size() - 1, mid;

  while (left <= right) {
    mid = left + (right - left) / 2;

    if (arr[mid] < value) {
      left = mid + 1;
    } else if (arr[mid] > value) {
      right = mid - 1;
    } else if (left + 1 < right) {
      left = mid;
    } else {
      return (arr[right] == value) ? right : left;
    }
  }

  return -1;
}

// TODO(domfarolino): This is currently unused; maybe test this?
int numOccurrences(const std::vector<int>& haystack, int needle) {
  int first = firstOccurrence(haystack, needle);
  if (first == -1) return first;

  int last = lastOccurrence(haystack, needle);
  return last - first + 1;
}

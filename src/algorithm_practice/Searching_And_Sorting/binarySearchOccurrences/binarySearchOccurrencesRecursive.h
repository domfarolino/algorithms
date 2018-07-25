#include <vector>

// Source: http://www.geeksforgeeks.org/count-number-of-occurrences-in-a-sorted-array/
// Souce: UVa (see AOAPC>V0>489)

/**
 * Recursive implementations of the "first occurrence" and "last occurrence"
 * binary search variants.
 * - First Occurrence
 * - Last Occurrrence
 * - Total number of occurrences ( = last - first + 1)
 *
 * Complexity analysis:
 * Time complexity: O(log(n))
 * Space complexity: O(log(n)); implicitly in stack frames for each log(n) "operation"
 */

int firstOccurrenceRecursive(const std::vector<int>& haystack, int low, int high, int needle) {
  // Set this now so if the while loop is never
  // entered we don't segfault on return conditional
  int mid = low + (high - low) / 2;

  while (low <= high) {
    mid = low + (high - low) / 2;

    if (haystack[mid] < needle) {
      low = mid + 1;
    } else if (haystack[mid] > needle) {
      high = mid - 1;
    } else {
      int farthestLeft = firstOccurrenceRecursive(haystack, low, mid - 1, needle);
      if (farthestLeft != -1) mid = farthestLeft;
      break;
    }
  }

  // TODO(domfarolino): We may index out-of-bounds here; fix this
  return (haystack[mid] == needle) ? mid : -1;
}

int lastOccurrenceRecursive(const std::vector<int>& haystack, int low, int high, int needle) {
  // Set this now so if the while loop is never
  // entered we don't segfault on return conditional
  int mid = low + (high - low) / 2;

  while (low <= high) {
    mid = low + (high - low) / 2;

    if (haystack[mid] < needle) {
      low = mid + 1;
    } else if (haystack[mid] > needle) {
      high = mid - 1;
    } else {
      int farthestRight = lastOccurrenceRecursive(haystack, mid + 1, high, needle);
      if (farthestRight != -1) mid = farthestRight;
      break;
    }
  }

  // TODO(domfarolino): We may index out-of-bounds here; fix this
  return (haystack[mid] == needle) ? mid : -1;
}

// TODO(domfarolino): This is currently unused; maybe test this?
int numOccurrencesUsingRecursive(const std::vector<int>& haystack, int needle) {
  int first = firstOccurrenceRecursive(haystack, 0, haystack.size() - 1, needle);
  if (first == -1) return first;

  int last = lastOccurrenceRecursive(haystack, 0, haystack.size() - 1, needle);
  return last - first + 1;
}

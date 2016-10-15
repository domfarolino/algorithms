#include <iostream>

/**
 * Binary Search
 * Designed to indicate whether or
 * not an element exists in a sorted
 * array of elements in O(log(n)). We
 * can make the function more robust by
 * accepting templated types as well as
 * returning an index of the element if
 * it exists or something like -1 if it
 * does not.
 */

using namespace std;

template <typename T>
int binarySearch(T arr[], int length, T val) {
  int l = 0, r = length - 1, mid;

  /**
   * We use <= because if the element exists, it is possible
   * l, r, and mid could all point to the element. In the case
   * the element does not exist, eventually l > r which is when
   * we can stop for sure.
   */
  while (l <= r) {
    mid = l + (r - l)/2; // This prevents integer overflow with large boundaries
    if (arr[mid] > val) {
      r = mid - 1;
    } else if (arr[mid] < val) {
      l = mid + 1;
    } else if (arr[mid] == val) {
      return mid;
    }
  }

  return -1;
}

int main() {
  int a[7] = {1, 2, 3, 4, 5, 6, 7};
  int size = sizeof(a)/sizeof(a[0]);

  // Print array
  cout << "{ ";

  for (int i = 0; i < size; ++i) {
    cout << a[i];

    if (i < size - 1) {
      cout << ", ";
    }
  }

  cout << " }" << endl;

  // "Test" binary search
  for (int i = 0; i < 10; ++i) {
    cout << "Index of " << i << ": " << binarySearch(a, 7, i) << endl;
  }

  return 0;
}

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Source: ??

/**
 * This file contains to algorithms that are modified
 * binary searches designed to return the index of a value
 *   1.) Closest to the value we wish to find
 *   2.) >= to the value we wish to find.
 *
 * To understand the simplicity of how this works we just need to
 * consider the possible outcomes:
 *
 * 1.) Value < first element
 *          Return the first element
 * 2.) Value > last element
 *          Return the last element
 * 3.) Value does not exist in the array, value > first elem && value < last elem
 *          Return next largest value in the array
 * 4.) Value exists in the array
 *          Return the value in the array
 *
 * A regular binary search halts when the left and right
 * bounds we're checking become inverted, such that the left
 * index becomes strictly greater than the right. This obviously
 * means that we didn't find the value we were looking for, but this
 * should mean that we can glean some information from the final values
 * of l and r. We have 3/4 of the above conditions to consider when we get
 * past the typical while loop of a binary search.
 *
 * 1.)
 * If the value we're seeking is less than the first element, the while loop
 * will stop when right bound = -1, left bound = 0. We want to return left bound.
 * This is actually the ONLY case where the loop will stop right after `r = mid - 1`.
 * This is important because it tells us a lot about the left pointer in every case.
 *
 * 2.)
 * In the opposite case, if the value we're seeking is greater than the last element
 * then the left bound will eventually become equal to the length of the array. In this
 * case we want to return:
 *          `l-1`, or `r` (index of last element) when finding closest value
 *          -1 when finding next largest
 *
 * 3.)
 * In the more interesting case where the value we're seeking is somewhere in between the
 * values of min and max but doesn't exist (since we're outside of the while loop), the left
 * and right bounds will narrow in as close as they can and eventually invert. Once inverted we
 * can know that the left bound will be at the next highest value, and the right bound at the next
 * smallest. We know this because just before they become inverted the left bound will always be set
 * to the next largest value, and to compensate the right will invert over the left becoming the next
 * smallest. In this case we just have to figure out where the smaller difference resides. Is it between
 * arr[l] and val, or arr[r] and val. Note to make sure that l and r are both valid indices we must run
 * the two previous conditional tests before this one!
 */

int binarySearchClosest(const vector<int>& arr, int val) {
  int l = 0, r = arr.size() - 1, mid;

  while (l <= r) {
    mid = l + (r - l) / 2;
    if (arr[mid] > val) {
      r = mid - 1;
    } else if (arr[mid] < val) {
      l = mid + 1;
    } else if (arr[mid] == val) {
      return mid;
    }
  }

  if (l >= arr.size()) { // l is out of bounds
    return r;
  } else if (r < 0) { // r is out of bounds
    return l;
  } else if (arr[l] - val < abs(arr[r] - val)) { // abs() on arr[r] since arr[r] is next lowest value
    return l;
  } else {
    return r;
  }
}

int binarySearchOrNextLargest(const vector<int>& arr, int val) {
  int l = 0, r = arr.size() - 1, mid;

  while (l <= r) {
    mid = l + (r - l) / 2;
    if (arr[mid] > val) {
      r = mid - 1;
    } else if (arr[mid] < val) {
      l = mid + 1;
    } else if (arr[mid] == val) {
      return mid;
    }
  }

  return (l >= arr.size()) ? -1 : l;
}


int main() {
  int T, n, searchValue, resultClosest, resultNextLargest;
  vector<int> test;
  cin >> T;

  // Driver loop
  for (int i = 0; i < T; ++i) {
    cin >> n >> searchValue;
    test.resize(n);
    for (int j = 0; j < n; ++j) {
      cin >> test[j];
    }

    resultClosest = binarySearchClosest(test, searchValue);
    resultNextLargest = binarySearchOrNextLargest(test, searchValue);

    cout << "Closest to " << searchValue << " is: " << test[resultClosest] << " at index: " << resultClosest << endl;
    cout << "Value >= to " << searchValue << " is: " << test[resultNextLargest] << " at index: " << resultNextLargest << endl;
    cout << endl;

    test.clear();
  }
  return 0;
}

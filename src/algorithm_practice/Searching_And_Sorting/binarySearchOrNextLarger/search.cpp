#include <iostream>
#include <vector>

using namespace std;

// Source: ??

/**
 * This algorithm is a modified binary search
 * designed to return the index of a value >= to
 * the value we wish to find. Note this algorithm
 * could easily be modified to return the index of
 * a value > the value we wish to find. We need to
 * consider some cases:
 *
 * 1.) Value < first element
 *          Return the first element
 * 2.) Value > last element
 *          Return -1, condition could not be met
 * 3.) Value exists in the array
 *          Return the value in the array
 * 4.) Value does not exist in the array, value > first elem && value < last elem
 *          Return next largest value in the array
 *
 * A regular binary search halts when the left and right
 * bounds we're checking become inverted, such that the left
 * index becomes strictly greater than the right, or the right
 * becomes strictly less than the left. This obviously means that
 * we didn't find the value we were looking for, but this should mean
 * that we can glean some information from the final values of l and r.
 * We have 3/4 of the above conditions to consider when we get past the typical
 * while loop of a binary search.
 *
 * If the value we're seeking is less than the first element, the while loop
 * will stop when right bound = -1, left bound = 0. We want to return left bound.
 *
 * In the opposite case, if the value we're seeking is greater than the last element
 * then the left bound will eventually become equal to the length of the array. In this
 * case we want to return -1. We can check for this with a simple conditional before the
 * return statement after the while loop.
 *
 * In the more interesting case where the value we're seeking is somewhere in between the
 * values of min and max but doesn't exist (since we're outside of the while loop), the left
 * and right bounds will narrow in as close as they can. Eventually the left bound will be set
 * to the next greatest value. To compensate, the right bound will then become lower than the left
 * bound in which we want to return the left bound.
 */

int binarySearch(vector<int>& arr, int val) {
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
  vector<int> test = {3, 4, 6};
  cout << binarySearch(test, 5) << endl;
  return 0;
}

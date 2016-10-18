#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Source: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=660&page=show_problem&problem=5103

/**
 * 7091-Height-Ordering
 * Simple! It is the problem of
 * inversion counting. See src/algorithm_practice/Searching_And_Sorting/numberOfInversions
 */

int mergeAndCountInversions(vector<int>& arr, int l, int m, int r) {
  vector<int> left(m - l + 1), right(r - m);

  for (int i = l; i <= m; i++) {
    left[i - l] = arr[i];
  }

  for (int i = m+1; i <= r; i++) {
    right[i - (m + 1)] = arr[i];
  }

  // I love me some sentinal values
  left.push_back(INT_MAX);
  right.push_back(INT_MAX);

  int lPtr = 0, rPtr = 0, returnNumberOfInversions = 0;
  for (int i = l; i <= r; ++i) {
    if (left[lPtr] <= right[rPtr]) {
      arr[i] = left[lPtr++];
    } else {
      returnNumberOfInversions += (m - l + 1 - lPtr);
      arr[i] = right[rPtr++];
    }
  }

  return returnNumberOfInversions;
}

int numberOfInversions(vector<int>& arr, int l, int r) {
  if (l < r) {
    int m = (l + r)/2, returnNumberOfInversions = 0;
    returnNumberOfInversions += numberOfInversions(arr, l, m);
    returnNumberOfInversions += numberOfInversions(arr, m+1, r);
    returnNumberOfInversions += mergeAndCountInversions(arr, l, m, r);
    return returnNumberOfInversions;
  } else return 0;
}

int main() {
  int numTests;
  cin >> numTests;
  vector<int> students(20);

  for (int i = 0; i < numTests; ++i) {
    cin >> students[0]; // get rid of test case, it's i+1 anyways
    for (int j = 0; j < 20; ++j) cin >> students[j];
    cout << i + 1 << " " << numberOfInversions(students, 0, 19) << endl;
  }

  return 0;
}

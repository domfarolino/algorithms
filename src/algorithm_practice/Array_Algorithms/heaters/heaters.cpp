#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Source: https://leetcode.com/contest/leetcode-weekly-contest-12/problems/heaters/

/**
 * Heaters
 * Problem description can be found in the above link. Essentially
 * the problem can be rather efficiently solved by utilizing a modified
 * binary search algorithm to return the closest element in a sorted array
 * to some value. This is useful because we can iterate through the houses
 * vector, trying to find the heater that is closest to the house and saying
 * "hey, our minimum radius must at least be the distance between some house
 * and its closest heater". This makes sense, so basically we sort the heaters
 * vector (since it is not guaranteed to be sorted) and perform the above operation.
 *
 * Complexity analysis, n = |Houses|, h = |Heaters|:
 * Time complexity: O(nlog(h))
 * Space complexity: O(h) // assuming merge sort
 */

int closestIndex(vector<int>& arr, int val) {
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

int findRadius(vector<int>& houses, vector<int>& heaters) {
  sort(heaters.begin(), heaters.end());

  int minRadius = 0, closestIndexHeater, diff;

  for (int i = 0; i < houses.size(); ++i) {
    closestIndexHeater = closestIndex(heaters, houses[i]);
    diff = abs(houses[i] - heaters[closestIndexHeater]);
    minRadius = max(minRadius, diff);
  }

  return minRadius;
}

int main() {
  vector<int> houses = {100, 110}, heaters = {101, 111}; // -std=c++0x
  cout << findRadius(houses, heaters) << endl;
  return 0;
}

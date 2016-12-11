// Source: https://leetcode.com/contest/leetcode-weekly-contest-12/problems/heaters/
class Solution {
public:
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
};

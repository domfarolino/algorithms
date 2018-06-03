// Source: https://leetcode.com/contest/weekly-contest-87/problems/longest-mountain-in-array/

class Solution {
public:
int longestMountain(const std::vector<int>& mountain) {
  if (mountain.size() < 3) return 0;
  int start = 0, next = 0, peak = 0, longestMtn = 0;

  while (start < mountain.size() - 2) {
    // Bring next up to start
    next = start;
    // Iterate to successively larger values
    while (next + 1 < mountain.size() && mountain[next + 1] > mountain[next]) next++;

    // If we were going to go out of bounds, break;
    if (next + 1 >= mountain.size()) break;

    // If we didn't make any progress, start++
    if (next == start) {
      start = next + 1;
      continue;
    }

    peak = next;
    std::cout << peak << std::endl;

    while (next + 1 < mountain.size() && mountain[next + 1] < mountain[next]) next++;

    // If we didn't make any progress, start++
    if (next == peak) {
      start = next + 1;
      continue;
    }

    longestMtn = std::max(next - start + 1, longestMtn);
    start = next;
  }

  return longestMtn;
}
};

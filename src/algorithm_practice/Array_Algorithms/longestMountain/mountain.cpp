#include <iostream>
#include <algorithm>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-87/problems/longest-mountain-in-array/

/**
 * Longest Mountain
 * This is a pretty cool problem. My first idea for this problem was that
 * for each potential mountain, we'd want to pick the starting point (first
 * value we come across), and basically iterate all the way to the peak, and
 * once we stop increasing in values, switch modes and iterate all the way to
 * the next valley. In my mind it was kind of like a state machine; in all cases
 * we're iterating forwards, but what we're looking for (successively larger or
 * smaller values) depended on what state we were in our mountain-finding. Since
 * there's only two real states we're going to be in my thoughts were that we didn't
 * really need to actually go all-in on the state-machine model, but could instead go
 * for two separate types of iteration (again looking for successively larger and then
 * smaller values) that would happen in order. We'd want to keep mountain-climbing until
 * our next mountain's start-position is out of bounds, in which case we stop and return
 * the length of the longest mountain we've seen.
 *
 * Some good edge cases to consider when looking at this problem are:
 * [1, 2, 3, 4], which has a mountain length of 0
 * [4, 3, 2, 1], which has a mountain length of 0
 * [1, 2, 1], which has a mountain length of 3
 * [1, 2, 1, 2, 3, 4, 5, 4], which has a mountain length of 6
 *
 * To measure the size of one mountain, we'll want some index variable to stick to the start
 * of a potential mountain. For each subsequent value that is both larger than the mountain's
 * start and in bounds, we'll set some index variable `next` to it, and keep going. Note that we
 * either stop when
 *  - We would have gone out of bounds, in which case this wouldn't be a mountain (no smaller vals after peak),
 *    and we're done.
 *  - The next value was not larger than the current value at the `next` location.
 *
 * If we stopped because of the second case, we know that we've either found our peak, or we made no
 * progress (the next value was <= to start position). If it's the former, we can bail our early and
 * just increment our start position. With the former, we can now transition into the "state" where we're
 * iterating forward again, but trying to find successively smaller values, and an eventual valley. From
 * here we want to go forward under similar conditions, and if we stop as a result from making no progress
 * from the peak, we also want to increment our start position and restart. If we stop because the next value
 * was not successively smaller, than we've found our valley! Here, we can can guarantee that we've found a
 * mountain at least of length 3 (since we have a start, peak, and end), so the length will be next - start + 1.
 * We can try to find the next mountain now, starting from the end of our previous mountain. Again, we'll do this
 * until our start position is out of bounds (this will be an all-encompassing while loop). We can actually do it
 * `while` our start index is < mountain.size() - 2, meaning it is the third-to-the-last index, since a mountain must
 * be at least three elements long.
 */

int longestMountain(const std::vector<int>& mountain) {
  if (mountain.size() < 3) return 0;
  int start = 0, next = 0, peak = 0, longestMtn = 0;

  while (start < mountain.size() - 2) {
    // Bring next up to start
    next = start;
    // Iterate to successively larger values
    while (next + 1 < mountain.size() && mountain[next + 1] > mountain[next]) next++;

    // If we were going to go out of bounds, break;
    // TODO(domfarolino): This probably isn't needed since we catch it below
    if (next + 1 >= mountain.size()) break;

    // If we didn't make any progress, start++
    if (next == start) {
      start = next + 1;
      continue;
    }

    peak = next;

    while (next + 1 < mountain.size() && mountain[next + 1] < mountain[next]) next++;

    // If we didn't make any progress, start++
    if (next == peak) {
      start = peak + 1;
      continue;
    }

    longestMtn = std::max(next - start + 1, longestMtn);
    start = next;
  }

  return longestMtn;
}

int main() {
  std::vector<int> mountain = {1};
  std::cout << longestMountain(mountain) << std::endl;
  mountain = {1, 2};
  std::cout << longestMountain(mountain) << std::endl;
  mountain = {1, 2, 1};
  std::cout << longestMountain(mountain) << std::endl;
  mountain = {1, 2, 3, 4};
  std::cout << longestMountain(mountain) << std::endl;
  mountain = {4, 3, 2, 1};
  std::cout << longestMountain(mountain) << std::endl;
  mountain = {0, 1, 2, 1, 2, 3, 4, 5, 4, 3};
  std::cout << longestMountain(mountain) << std::endl;
  mountain = {1, 2, 3, 2, 1, 1, 1, 2, 1};
  std::cout << longestMountain(mountain) << std::endl;
  return 0;
}

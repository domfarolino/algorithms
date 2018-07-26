#include <iostream>
#include <algorithm>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-82/problems/friends-of-appropriate-ages/

/**
 * Friends of Appropriate Ages
 * Very interesting problem! By working through a couple examples it should be
 * clear that any age younger than 15 cannot request the friendship of anyone else.
 * This is because we know an age cannot request any age older than itself, and that
 * the youngest age a 14-year-old can request would be 15 (14 / 2 + 8).
 * The problem description itself makes the naive solution fairly obvious. We can iterate
 * through the entire list of ages, and for each age `a`, iterate from index 0 until we hit
 * the oldest age `a` could request. If the age we're looking at can be requested by `a`, we
 * increment some counter variable. We'll just need a special case to make sure we `a` doesn't
 * request itself. It is important that we iterate through all the way to the last occurrence of
 * `a`, so that `a` has a chance at requesting other peers of the same age. This solution is simple,
 * but expensive.
 * Complexity analysis:
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 *
 * [Implemented below]
 * A more optimized solution can come from the realization we only really need to know how many "people"
 * are of each age. For example, when we're looking at `18` and iterating from the beginning of the age
 * list up to the last occurrence of `18`, we're wasting energy if we travel over 100 17's asking "Can 17
 * be requested by 18?". Instead it would be nice to ask "How many 17-year-olds" are there that all of the
 * 18-year-olds will request?". We can create a map which maps ages => num_people_of_that_age, of size 121.
 * Then instead of iterating through the entire list of ages, we'd iterate through the map in the same fashion.
 * For each age `a`, if there were > 0 people of that age, we'd loop from index 0 => `a` in our map, and for each
 * intermediate age `i`, if `i` was an age that `a` could request, we'd simply make map[a] * map[i] requests, and
 * reflect this in our counter variable. If map[i] = 0 (no people are of age `i`), but `i` is in `a`'s request range,
 * then we simply added 0 to our counter and move on. If map[i] >= 1, all people of age `a` will request all people of
 * age `i`, thus prompting the map[a] * map[i] requests. We have to special case to make sure people of age `a` only
 * generate map[a] * (map[a] - 1) requests though, since nobody will request themselves!
 * Complexity analysis:
 * Time complexity: O(n); O(n) (preprocessing/map-building) + O(120^2) = O(n) + O(1)
 * Space complexity: O(1); O(120) = O(1)
 *
 * [Implemented below]
 * A more interesting solution to me, but less efficient, was to iterate over the entire ages list as in the naive
 * solution, but instead of manually searching for the youngest and oldest ages we can request, use a variants of binary
 * search for both of these. This requires us intially sorting the ages list. Then for each `age`, we'll do two searches:
 * 1.) Search for the first occurrence of `age` / 2 + 8, or the next largest age
 * 2.) Search for the last occurrence of `age` (the oldest age we can request)
 * We'll only want to carry these searches out if `age` / 2 + 8 <= `age` of course. Then once we get the indices of these
 * searches, we simply add `lastIndex - firstIndex`. We want to make sure we don't add + 1 even though it might be tempting,
 * because at this point, the index of the `age` we're looking at is guaranteed to be in that range, and we can't request
 * ourself. This solution is nice because it offloads the work into searching and preprocessing, and keeps the core logic
 * relatively simple. If you made it this far, thanks for reading ^_^
 * Complexity analysis:
 * Time complexity: O(nlog(n)) + O(n*(2*log(n))) = O(nlog(n))
 * Space complexity: O(n)
 */

int numFriendRequestsOptimal(const std::vector<int>& ages) {
  int returnNumRequests = 0;
  int ageMap[121] = {0};
  // Pre-processing to build our age map
  for (int i = 0; i < ages.size(); ++i) {
    ageMap[ages[i]]++;
  }

  for (int age = 0; age < 121; ++age) {
    for (int i = (age / 2 + 8); i <= age; ++i) {
      returnNumRequests += (ageMap[age] * ageMap[i]);
      if (i == age) returnNumRequests -= ageMap[age];
    }
  }

  return returnNumRequests;
}

// For more documentation on this (and the below) variant of binary search, see
// the binarySearch* folders under https://github.com/domfarolino/algorithms/tree/master/src/algorithm_practice/Searching_And_Sorting
// and my blog post on useful binary search variants
int findFirstAgeOrNextLargest(const std::vector<int>& ages, int age) {
  int l = 0, r = ages.size() - 1, mid;

  while (l <= r) {
    mid = (l + r) / 2;
    if (ages[mid] > age) {
      r = mid - 1;
    } else if (ages[mid] < age) {
      l = mid + 1;
    } else if (l != mid) {
      r = mid;
    } else {
      return mid;
    }
  }

  // At this point we have not found the age we're
  // looking for, so one of the following is true:
  // 1.) r == -1, meaning every value in |ages| is > age
  // 2.) l == ages.size(), meaning every value in |ages| is < age
  // 3.) l == the index of the next age greater than |age| (first occurrence!)
  // In the case of (1) and (3), we want to return |l|. In the case of (2), we
  // need to return -1, since we could not find an age >= age.
  if (l == ages.size())
    return -1; // the caller of this will never search for an out-of-bounds value, but it is good to include this for completeness
  return l;
}

int findOldestAgeToRequest(const std::vector<int>& ages, int age) {
  int l = 0, r = ages.size() - 1, mid;

  while (l <= r) {
    mid = (l + r) / 2;
    if (ages[mid] < age) {
      l = mid + 1;
    } else if (ages[mid] > age) {
      r = mid - 1;
    } else if (l != mid) {
      l = mid;
    } else {
      return (ages[r] == age) ? r : l;
    }
  }

  return -1; // the caller of this will never search for a non-existent value, but it is good to include this for completeness
}

int numFriendRequests(std::vector<int> ages) {
  int numRequests = 0, youngestAgeToRequest, oldestAgeToRequest, youngestAgeCanRequest;

  std::sort(ages.begin(), ages.end());
  for (int i = 0; i < ages.size(); ++i) {
    youngestAgeCanRequest = ages[i] / 2 + 8;
    if (youngestAgeCanRequest > ages[i]) continue;

    youngestAgeToRequest = findFirstAgeOrNextLargest(ages, youngestAgeCanRequest);
    oldestAgeToRequest = findOldestAgeToRequest(ages, ages[i]);
    // Guarantee |youngestAgeToRequest| and |oldestAgeToRequest| are in non-decreasing order
    numRequests += (oldestAgeToRequest - youngestAgeToRequest);
  }
  return numRequests;
}

int main() {
  std::vector<int> ages = {3, 4, 5, 6};
  int requestsMade = numFriendRequests(ages);
  std::cout << requestsMade << std::endl;
  requestsMade = numFriendRequestsOptimal(ages);
  std::cout << requestsMade << std::endl;

  ages = {16, 16};
  requestsMade = numFriendRequests(ages);
  std::cout << requestsMade << std::endl;
  requestsMade = numFriendRequestsOptimal(ages);
  std::cout << requestsMade << std::endl;

  ages = {16, 16, 16, 17, 17, 19, 19, 19, 19, 19};
  requestsMade = numFriendRequests(ages);
  std::cout << requestsMade << std::endl;
  requestsMade = numFriendRequestsOptimal(ages);
  std::cout << requestsMade << std::endl;
  return 0;
}

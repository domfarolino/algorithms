// Source: https://leetcode.com/contest/weekly-contest-82/problems/friends-of-appropriate-ages/

class Solution {
public:
int numFriendRequests(const std::vector<int>& ages) {
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
};

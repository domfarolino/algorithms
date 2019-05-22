#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-103/problems/online-election/
// Source: https://leetcode.com/problems/online-election/description/

class Election {
private:
  std::vector<int> times, queryVec;
  int binarySearchOrNextSmallest(int val, int l, int r) {
    int m;
    while (l <= r) {
      m = (l + r) / 2;
      if (times[m] > val) {
        r = m - 1;
      } else if (times[m] < val) {
        l = m + 1;
      } else {
        return m;
      }
    }

    // times[r] is the next lowest time. Normally it'd be
    // possible for `r` to be < 0, however this question makes
    // the assumption that.
    return r;
  }

public:
  Election(const std::vector<int>& inPerson, const std::vector<int>& inTimes): times(inTimes) {
    std::unordered_map<int, int> candidateMaxes;
    std::pair<int, int> maxCandidate(0, INT_MIN);
    for (int candidate: inPerson) {
      candidateMaxes[candidate]++;
      if (candidateMaxes[candidate] >= maxCandidate.second) {
        maxCandidate.second = candidateMaxes[candidate];
        maxCandidate.first = candidate;
      }

      queryVec.push_back(maxCandidate.first);
    }
  }

  int query(int t) {
    // Assert t >= all times in given time vector
    int timeIndex = binarySearchOrNextSmallest(t, 0, times.size() - 1);
    return queryVec[timeIndex];
  }
};

int main() {
  std::vector<int> candidateVotes = {0, 1, 1, 0, 0, 1, 0}, times = {0, 5, 10, 15, 20, 25, 30};
  Election election(candidateVotes, times);
  std::cout << election.query(3) << std::endl;
  std::cout << election.query(12) << std::endl;
  std::cout << election.query(25) << std::endl;
  std::cout << election.query(15) << std::endl;
  std::cout << election.query(24) << std::endl;
  std::cout << election.query(8) << std::endl;
  return 0;
}

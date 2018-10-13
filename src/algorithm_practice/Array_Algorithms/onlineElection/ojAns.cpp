// Source: https://leetcode.com/contest/weekly-contest-103/problems/online-election/

class TopVotedCandidate {
private:
  std::vector<int> times;
  std::vector<int> queryVec;
int binarySearchOrNextSmallest(int val, int l, int r) {
  int mid;

  while (l <= r) {
    mid = l + (r - l) / 2;
    if (times[mid] > val) {
      r = mid - 1;
    } else if (times[mid] < val) {
      l = mid + 1;
    } else if (times[mid] == val) {
      return mid;
    }
  }

  return r;
}
public:
  TopVotedCandidate(const std::vector<int>& inPersons, const std::vector<int>& inTimes): times(inTimes) {
    std::unordered_map<int, int> candidateMaxes;
    std::pair<int, int> maxCandidate(0, INT_MIN);
    for (int candidate: inPersons) {
      candidateMaxes[candidate]++;
      if (candidateMaxes[candidate] >= maxCandidate.second) {
        maxCandidate.second = candidateMaxes[candidate];
        maxCandidate.first = candidate;
      }

      queryVec.push_back(maxCandidate.first);
    }
  }

  int q(int t) {
    int timeIndex = binarySearchOrNextSmallest(t, 0, times.size() - 1);
    return queryVec[timeIndex];
  }
};

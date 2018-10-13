// Source: https://leetcode.com/contest/weekly-contest-104/problems/partition-array-into-disjoint-intervals/

class Solution {
public:
    int partitionDisjoint(const vector<int>& A) {
      std::vector<int> leftMax = A, rightMin = A;
      int currMin = INT_MAX, currMax = INT_MIN;

      for (int i = 0; i < A.size(); ++i) {
        currMax = std::max(currMax, A[i]);
        leftMax[i] = currMax;
        currMin = std::min(currMin, A[A.size() - 1 - i]);
        rightMin[A.size() - 1 - i] = currMin;
      }

      int L = 0;
      currMax = leftMax[L];
      currMin = rightMin[L + 1];
      while (currMax > currMin) {
        L++;
        currMax = leftMax[L];
        currMin = rightMin[L + 1];
      }

      return L + 1;
    }
};

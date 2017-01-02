// Source: https://leetcode.com/problems/intersection-of-two-arrays/
class Solution {
public:
    vector<int> intersection(vector<int>& a, vector<int>& b) {
      if (a.size() < b.size()) {
        return intersectionOfTwoArraysHashingHelper(a, b);
      } else {
        return intersectionOfTwoArraysHashingHelper(b, a);
      }
    }

    // We use this helper to guarantee that `a` is the smaller element here
    // This gives us O(min(|a|, |b|)) space complexity
    vector<int> intersectionOfTwoArraysHashingHelper(vector<int>& a, vector<int>& b) {
      unordered_set<int> uSet;
      vector<int> returnVector;

      for (int i = 0; i < a.size(); ++i) {
        uSet.insert(a[i]);
      }

      for (int i = 0; i < b.size(); ++i) {
        if (uSet.find(b[i]) != uSet.end()) {
          returnVector.push_back(b[i]);
          uSet.erase(uSet.find(b[i]));
        }
      }

      return returnVector;
    }
};

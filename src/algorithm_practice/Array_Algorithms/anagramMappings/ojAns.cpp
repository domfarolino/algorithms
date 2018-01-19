// Source: https://leetcode.com/problems/find-anagram-mappings/

class Solution {
public:
    std::vector<int> anagramMappings(const std::vector<int>& a, const std::vector<int>& b) {
      std::vector<int> returnVec;
      std::unordered_map<int, int> uMap;

      // Initialize uMap with the indices all `b` values are at
      for (int i = 0; i < b.size(); i++) {
        uMap[b[i]] = i;
      }

      for (int i = 0; i < a.size(); i++) {
        returnVec.push_back(uMap[a[i]]);
      }

      return returnVec;
    }
};

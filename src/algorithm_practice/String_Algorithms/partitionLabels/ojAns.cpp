// Source: https://leetcode.com/problems/partition-labels/

class Solution {
public:
    std::vector<int> partitionLabels(const std::string& str) {
      std::vector<int> returnVec;
      std::unordered_map<char, int> lastMap;

      // Preprocess lastMap hash table with
      // indices of the last occurrences of each letter
      for (int i = 0; i < str.length(); i++) {
        lastMap[str[i]] = i;
      }

      int partBegin = 0, partEnd = 0;
      int i = 0;
      while (i < str.length()) {
        // Compute the end boundary
        partEnd = std::max(partEnd, lastMap[str[i]]);

        // We've reached the end of our partition
        if (i == partEnd) {
          returnVec.push_back(partEnd - partBegin + 1);
          i = partEnd + 1;
          partBegin = i;
          continue;
        }
        ++i;
      }

      return returnVec;
    }
};

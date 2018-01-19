#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

// Source: https://leetcode.com/problems/partition-labels/

/**
 * Partition Labels
 * Given a string of lowercase letters, partition the string
 * into as many partitions possible such that each letter appears
 * in at most one partition. Our output should be a list of the lengths
 * associated with each partition.
 *
 * Example:
 * In: "abcbcaaedffedd"
 * Out: ["abcbcaa", "edffedd"]
 *
 * The problem might seem difficult at first, but going through a few
 * examples makes it much more clear. The key is realizing each partition
 * must contain all occurrences of a letter as it spans through the given
 * string. So we'd start by looking at building the first partition. When
 * we come accross the first letter, we know the first partition must AT
 * LEAST contain all characters between the first and last occurrence of
 * this letter. As we iterate through the list we will only expand the length
 * of this partition if we come across characters between the aforementioned
 * span whose last occurrence appears outside of the current partition boundary.
 * So for example "abbab", we'd first come across "a", and if we search to find
 * it's last occurrence, we know our span must AT LEAST go from index 0 to 3. When
 * we come across the next letter "b", which occurrs before our current partition bound
 * `3`, searching for its last occurrence gives us an index that goes outside of our current
 * partition bound, so we know our partition must be expanded. Once we finally reach the partition
 * bound without hitting any more letters whose last occurrence is beyond the current bound, we can
 * store the length of this currently-passed-through partition in our return vector, and start over
 * at the next character.
 *
 * To implement this solution, we'll need two index counters, one for the beginning of the current
 * partition, and one for the current partition boundary, which of course may be moved back as we
 * iterate through this candidate partition.
 *
 * We'll also need a way to find the last occurrence of a given letter. We can do this in O(n) time
 * for a given letter as we sweep through partitions, however since we're iterating through every letter
 * as it is, this would lead to a solution whose time complexity is O(n^2) and space complexity is O(1).
 * To support fast-lookup of last-occurrences, we can use a hash table to store this information, and retrieve
 * the last occurrence of some letter in O(1), driving our solution down to a time complexity of O(n) while using
 * O(n) space (for the storage of the table during some initial preprocessing).
 */

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
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

void printVector(const std::vector<int>& vec) {
  std::cout << "[";
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i];
    if (i + 1 < vec.size()) std::cout << ", ";
  }

  std::cout << "]" << std::endl;
}

int main() {
  std::string testString = "ababcbacadefegdehijhklij";
  std::vector<int> result = partitionLabels(testString);
  printVector(result);

  testString = "ab";
  result = partitionLabels(testString);
  printVector(result);
  return 0;
}

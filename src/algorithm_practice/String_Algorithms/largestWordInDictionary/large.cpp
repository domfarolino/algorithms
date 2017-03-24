#include <iostream>
#include <vector>
#include <string>

// Source: http://www.geeksforgeeks.org/find-largest-word-dictionary-deleting-characters-given-string/
// Source: http://practice.geeksforgeeks.org/problem-page.php?pid=1710

/**
 * Largest word in dictionary
 * The first small leap is realizing that the problem is
 * basically determining whether or not one string's characters
 * exist in the same order (not necessarily contiguously) in another
 * string. Note "deleting" them, as the problem puts it, is just skipping
 * characters that appear in the input string that do not appear in a particular
 * string in the dictionary. This is a trivial algorithm, as we just need to maintain
 * current index pointers keeping our position in both strings as we iterate through. We
 * want to stay at the same character in the dictionary string and iterate through our input
 * string until we find a character matching the one in our dictionary string. Once we find a
 * match, we can increment our dictionary string index pointer by one, and again keep iterating
 * until we find our next match. We'll want to keep this up until either we run out of characters
 * in our dictionary string or our master string, whichever happens first. We can return true if our
 * dictionary string index pointer as made it through ALL of the characters in the dictionary string
 * and false otherwise.
 *
 * Keeping track of the largest string that is a subsequence of the input string is also trivial.
 *
 * Complexity analysis:
 * Time complexity: O(N*n*k) (N = dict length, n = masterString.size(), k = dictionary word length)
 * Space complexity: O(1)
 */

bool areSubsequences(const std::string &dictString, const std::string &masterString) {
  int i = 0, j = 0;

  while (i < dictString.length() && j < masterString.length()) {
    if (dictString[i] == masterString[j]) {
      ++i;
    }
    ++j;
  }

  return i == dictString.length();
}

std::string longestSubsequence(const std::vector<std::string> &dict, const std::string &masterString) {
  std::string longestString = "";

  for (int i = 0; i < dict.size(); ++i) {
    if (dict[i].length() > longestString.length() && areSubsequences(dict[i], masterString)) {
      longestString = dict[i];
    }
  }

  return longestString;
}

int main() {
  int T, dictLength;
  std::vector<std::string> dict;
  std::string masterString;

  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    std::cin >> dictLength;
    dict.resize(dictLength);

    for (int i = 0; i < dictLength; ++i) {
      std::cin >> dict[i];
    }

    std::cin >> masterString;

    std::cout << longestSubsequence(dict, masterString) << std::endl;
    dict.clear();
  }
  return 0;
}

#include <iostream>
#include <string>
#include <algorithm> // std::sort

// Source: https://leetcode.com/problems/find-the-difference/

/**
 * Find the difference
 * You are given to strings s and t. Both are composed
 * of only lowercase letters and string t is generated
 * by randomly shuffling string s and inserting a single
 * character into a random position. The goal of the algorithm
 * is to find the single character in t that is not in s.
 *
 * One way to solve this is to simply sort both strings and
 * then run through each string until the characters are not
 * equal. This character in t will be the one to return.
 * Complexity analysis:
 * Time complexity: O(nlog(n))
 * Space complexity: O(n)
 *
 * There exists a more optimized solution. Note we need to know the
 * number of times some character appears in s and t. Since we'll need
 * some information associated with each character we can use an unordered
 * hash map. The map will be used to store a char as a key and the number of
 * times it exists as its its value. We'll go through string s incrementing the
 * number of times each character exists and then go through string t decrementing
 * the number of times each character exists. When we come across a character in t that
 * either does not exist in a, or exists more times in t than in s, the entry in the map
 * will be 0, and we know when we try to decrement 0 that character is the one to return.
 * Note that since we have fairly tight constraints on the data each string will be composed
 * of (all lowercase letters) we can create our own version of a hash map by utilizing an integer
 * array where each index is some (key - 'a'), and the number at that index is the key's value.
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 * Note this problem can be solved just like Single Number https://leetcode.com/problems/single-number/
 */

char findTheDifferenceSort(std::string& s, std::string& t) {
  std::sort(s.begin(), s.end());
  std::sort(t.begin(), t.end());

  int i = 0;
  for (; i < s.length(); ++i) {
    if (s[i] != t[i]) break;
  }

  // Either returns the non-matching character from t or
  // the last character of t (which won't match if we get that far)
  return t[i];
}

char findTheDifferenceHash(const std::string &s, const std::string &t) {
  int charMap[26] = {0}; // init all values to 0
  char returnChar;

  for (int i = 0; i < s.size(); ++i) {
    charMap[s[i] - 'a']++; // same as uSet.insert(s[i]);
  }

  for (int i = 0; i < t.size(); ++i) {
    if (charMap[t[i] - 'a'] == 0) {
      returnChar = t[i];
      break;
    }
    charMap[t[i] - 'a']--;
  }

  return returnChar;
}

int main() {
  std::string s, t;
  std::cin >> s >> t;

  std::cout << findTheDifferenceSort(s, t) << std::endl;
  std::cout << findTheDifferenceHash(s, t) << std::endl;
  return 0;
}

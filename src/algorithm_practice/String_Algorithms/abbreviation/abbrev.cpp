#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

// Source: https://www.hackerrank.com/contests/world-codesprint-6/challenges/abbr

/**
 * Abbreviation
 * Interesting problem.
 * This problem apparently has a widely
 * accepted O(n^2) dynamic programming answer however
 * I did not naturally come up with that solution. Mine
 * was a regular O(n^2) solution with O(1) space complexity.
 *
 * The first realization I made was that since we are given the
 * most freedom with the lowercase letters we should take a look
 * at the requirements that must be met for the uppercase ones. It
 * is clear that we cannot delete or displace any uppercase characters
 * in the first string so it is important that any uppercase characters
 * that do exist in the first string exist so in the relative order they
 * appear in the second string. It is also essential to realize that the
 * first string can not have any capital letters that do not appear in the
 * second string because there would be no way to ammend the first string
 * given our constraints, to form the second string. In this case we need to
 * start looking at the first string, and for each character make sure that
 * not only it appears in the second string, but that it appears in the second
 * string after the position of the last found character in the second string.
 * This ensure we catch capital letters that appear k times in the first string
 * but only k-1 times in the second string. This is important because we cannot
 * mutate capital letters.
 *
 * After our first string passes the capitalsRelativeOrder test we then need
 * to see if there are the necessary lowercase characters in between the capitals
 * in proper relative order to make the proper abbreviation. We can do this by searching
 * for every character in the second string to find its position in the first. When searching
 * for some character from second string in the first string we'll either come across an uppercase
 * or lowercase character. If we see an uppercase then surely its relative position has been accounted
 * for, however if we only see a lowercase then it must one we can turn to uppercase to make our abbrev.
 * To make sure that all lowercase characters are in the right place for us to make them work we need to
 * keep track of the position in the first string that we found our last character at, and then only search
 * from there to the end of the string for future character. This ensures that when we find a character in the
 * first string it is actually in the correct relative order as the characters in the second string.
 *
 * The reason we need capitalsRelativeOrder in the first place is because if we just did the searching routine
 * described above, we could come across the following example:
 *
 * s1 = ABBC
 * s2 = ABC
 * In this case there us no way to turn s1 into s2, therefore we need to return false however our algorithm.
 * This why in this algorithm I have two routines. One starting with characters from the first string and searching
 * in the second, and another starting with characters in the second string and finding them in the first.
 *
 * Time complexity: O(n^2) (find operation is O(n) and we call it O(n) times)
 * Space complexity: O(1)
 */

bool capitalsRelativeOrder(std::string& s1, std::string& s2) {
  int pos = 0;
  for (int i = 0; i < s1.length(); ++i) {
    if (s1[i] >= 65 && s1[i] <= 90) { // if (s1[i] >= 'A' && s1[i] <= 'Z') {
      if (s2.find(s1[i], pos) == std::string::npos) {
        return false;
      } else if (s2.find(s1[i], pos) != std::string::npos) {
        pos = s2.find(s1[i], pos) + 1;
      }
    }
  }

  return true;
}

bool canMakeAbbrev(std::string& s1, std::string& s2) {
  if (!capitalsRelativeOrder(s1, s2)) return false;
  int pos = 0;
  for (int i = 0; i < s2.length(); ++i) {
    if (s1.find(s2[i], pos) == std::string::npos && s1.find(char(s2[i] + 32), pos) == std::string::npos) {
      return false;
    } else if (s1.find(s2[i], pos) != std::string::npos || s1.find(char(s2[i] + 32), pos) != std::string::npos) {
      pos = i;
    }
  }

  return true;
}

int main() {
  int q;
  std::string s1, s2;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    std::cin >> s1 >> s2;
    if (canMakeAbbrev(s1, s2)) {
      std::cout << "YES";
    } else {
      std::cout << "NO";
    }
    std::cout << std::endl;
  }

  return 0;
}

#include <iostream>
#include <string>

// Source: https://leetcode.com/contest/weekly-contest-87/problems/backspace-string-compare/

/**
 * Given two strings, determine if they resolve to equal text
 * when typed into a text editor. '#' means backspace. The premise
 * of this algorithm is fairly simple, it's mostly just a coding agility
 * problem. Some good questions if this were an interview question:
 *
 * 1.) Could we assume that there will not be more #'s than there are
 *     resolved characters in the string at any given point? (Can we assume
 *     that a user will not backspace on an empty string?) A yes means we could
 *     probably simplify our logic a little but, but a no is not terribly difficult
 *     to deal with at all.
 * 2.) Will the string be ascii characters only?
 *
 * The naive solution is to maintain two "resolved" strings, which contain the
 * actual text that the editor would see, and then return the result of the final
 * comparison. To compute the resolved strings corresponding to the input strings
 * we can iterate through them, and if we come across a #, we remove the last value
 * we added to the resolved string (if it isn't empty), else we add the character to
 * the resolved string. We can do this for each string, and return the comparison between
 * the two resolved strings.
 *
 * Complexity analysis
 * Time complexity: O(n + m), where n and m are the lengths of the corresponding input strings
 * Space complexity: O(n + m), since we have to store resolved strings that could be at their
 * longest, copies of the input strings.
 */

bool backspaceCompare(const std::string& s1, const std::string& s2) {
  std::string resolve1, resolve2;

  for (int i = 0; i < s1.length(); i++) {
    if (s1[i] == '#') {
      if (resolve1.length())
        resolve1.pop_back();
    } else {
      resolve1.push_back(s1[i]);
    }
  }

  for (int i = 0; i < s2.length(); i++) {
    if (s2[i] == '#') {
      if (resolve2.length())
        resolve2.pop_back();
    } else {
      resolve2.push_back(s2[i]);
    }
  }

  return resolve1 == resolve2;
}

int main() {
  std::string s1 = "##", s2 = "";
  std::cout << backspaceCompare(s1, s2) << std::endl;
  s1 = "a#b#aa";
  s2 = "abceta########a#b#c#aaa#";
  std::cout << backspaceCompare(s1, s2) << std::endl;
  s1 = "abc####ac";
  s2 = "acb##";
  std::cout << backspaceCompare(s1, s2) << std::endl;
  return 0;
}

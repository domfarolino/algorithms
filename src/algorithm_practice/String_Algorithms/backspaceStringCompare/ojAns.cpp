// Source: https://leetcode.com/contest/weekly-contest-87/problems/backspace-string-compare/

class Solution {
public:
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
};

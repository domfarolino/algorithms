// Source: https://leetcode.com/problems/find-the-difference/
class Solution {
public:
    char findTheDifference(string s, string t) {
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
};

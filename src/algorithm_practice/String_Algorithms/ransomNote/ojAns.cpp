// Source: https://leetcode.com/problems/ransom-note/
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int hashTable[26] = {0}; // init elements => 0
        for (int i = 0; i < magazine.size(); ++i) {
            hashTable[magazine[i] - 'a']++;
        }

        for (int i = 0; i < ransomNote.size(); ++i) {
            if (hashTable[ransomNote[i] - 'a'] == 0) {
                return false;
            } else hashTable[ransomNote[i] - 'a']--;
        }

        return true;
    }
};

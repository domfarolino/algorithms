// https://leetcode.com/contest/9/problems/reconstruct-original-digits-from-english/
class Solution {
public:
    //unordered_map<char, long> inputMap;
    long inputMap[26];

    bool findAndRemove(string haystack) {
        for (int i = 0; i < haystack.length(); ++i) {
            if (inputMap[haystack[i] - 97] == 0) return false;
        }

        for (int i = 0; i < haystack.length(); ++i) {
            inputMap[haystack[i] - 97]--;
        }

        return true;
    }

    void initMap(string& s) {
        for (int i = 0; i < 26; ++i) {
            inputMap[i] = 0;
        }
        for (long i = 0; i < s.length(); ++i) {
            inputMap[s[i] - 97]++;
        }
    }

    string originalDigits(string s) {
        initMap(s);
        string out0 = "",
                out1 = "",
                out2 = "",
                out3 = "",
                out4 = "",
                out5 = "",
                out6 = "",
                out7 = "",
                out8 = "",
                out9 = "";

        while (findAndRemove("eight")) out8 += "8";
        while (findAndRemove("six"))   out6 += "6";
        while (findAndRemove("seven")) out7 += "7";
        while (findAndRemove("four"))  out4 += "4";
        while (findAndRemove("five"))  out5 += "5";
        while (findAndRemove("three")) out3 += "3";
        while (findAndRemove("two"))   out2 += "2";
        while (findAndRemove("nine"))  out9 += "9";
        while (findAndRemove("zero"))  out0 += "0";
        while (findAndRemove("one"))   out1 += "1";

        return out0 + out1 + out2 + out3 + out4 + out5 + out6 + out7 + out8 + out9;
    }
};

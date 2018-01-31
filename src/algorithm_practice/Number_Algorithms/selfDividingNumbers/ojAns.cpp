// Source: https://leetcode.com/problems/self-dividing-numbers/

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> returnVec;

        for (int i = left; i <= right; i++) {
            if (isSelfDividingNumber(i)) returnVec.push_back(i);
        }
        return returnVec;
    }

    bool isSelfDividingNumber(int num) {
        int tmp = num;
        while (tmp) {
            if (!(tmp % 10) || num % (tmp % 10)) return false;
            tmp /= 10;
        }

        return true;
    }
};

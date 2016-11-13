// Source: https://leetcode.com/contest/smarking-algorithm-contest-3/problems/minimum-moves-to-equal-array-elements/
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int minElem = INT_MAX, minIndex, maxElem = INT_MIN, maxIndex;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > maxElem) {
                maxElem = nums[i];
                maxIndex = i;
            }

            if (nums[i] < minElem) {
                minElem = nums[i];
                minIndex = i;
            }
        }

        int retMoves = maxElem - minElem;

        for (int i = 0; i < nums.size(); ++i) {
            if (i != minIndex && i != maxIndex) {
                retMoves += nums[i] - minElem;
            }
        }

        return retMoves;
    }
};

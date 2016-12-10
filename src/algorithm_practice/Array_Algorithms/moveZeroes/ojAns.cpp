// Source: https://leetcode.com/problems/move-zeroes/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i]) {
                nums[j] = nums[i];
                j++;
            }
        }

        for (j; j && j < nums.size(); ++j) {
            nums[j] = 0;
        }
    }
};

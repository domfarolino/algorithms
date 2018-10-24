// Source: https://leetcode.com/problems/two-sum/description/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::vector<int> returnVec;
        std::unordered_map<int, int> uMap;
        for (int i = 0; i < nums.size(); ++i) {
            if (uMap.find(target - nums[i]) != uMap.end()) {
                returnVec = {uMap[target - nums[i]], i};
                return returnVec;
            } else {
                uMap[nums[i]] = i;
            }
        }

        return returnVec; // should never get here
    }
};

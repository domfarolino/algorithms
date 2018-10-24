#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> twoSum(const std::vector<int>& nums, int k) {
  std::vector<int> returnVec;
  std::unordered_map<int, int> uMap;

  for (int i = 0; i < nums.size(); ++i) {
    if (uMap.find(k - nums[i]) != uMap.end()) {
      returnVec = {uMap[k - nums[i]], i};
      return returnVec;
    } else
      uMap[nums[i]] = i;
  }

  return returnVec;
}

int main() {
  std::vector<int> a = {1, 2, 4, 4}, b = {2, 2, 6};
  std::vector<int> result = twoSum(a, 8);

  std::cout << result[0] << ", " << result[1] << std::endl;
  result = twoSum(b, 8);
  std::cout << result[0] << ", " << result[1] << std::endl;
  return 0;
}

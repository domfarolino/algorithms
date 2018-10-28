#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <climits>
#include <cstdlib>

// Source: https://leetcode.com/problems/3sum/description/

/**
 * 3Sum
 *
 * For a detailed description of the problem and several different
 * solution approaches, see the README in this directory.
 */

// One-pass version.
std::vector<std::vector<int>> threeSumOnePass(std::vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
  std::vector<std::vector<int>> returnVec;
  std::unordered_set<int> exists;

  int tmp;
  bool foundComplementWithThisPair = false;
  for (int i = 0; i < int(nums.size()) - 1; ++i) {
    if (i != 0 && nums[i] == nums[i - 1]) continue;
    for (int j = i + 1; j < nums.size(); ++j) {
      if (j > i + 1 && nums[j - 1] == nums[j] && foundComplementWithThisPair) continue;
      tmp = nums[i] + nums[j];
      foundComplementWithThisPair = false;
      if (exists.find(-tmp) != exists.end()) {
        std::vector<int> newVec = {nums[i], nums[j], -tmp};
        returnVec.push_back(newVec);
        foundComplementWithThisPair = true;
      }

      exists.insert(nums[j]);
    }

    exists.clear();
  }

  return returnVec;
}

// Two-pass more intuitive (IMLTHO) version.
std::vector<std::vector<int>> threeSumTwoPass(std::vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
  std::vector<std::vector<int>> returnVec;
  std::unordered_map<int, int> exists;
  for (int i = 0; i < nums.size(); ++i)
    exists[nums[i]] = i;

  int tmp;
  for (int i = 0; i < int(nums.size()) - 1; ++i) {
    if (i != 0 && nums[i] == nums[i - 1]) continue;
    for (int j = i + 1; j < nums.size(); ++j) {
      if (j != i + 1 && nums[j] == nums[j - 1]) continue;
      tmp = nums[i] + nums[j];
      if (exists[-tmp] > j) {
        std::vector<int> newVec = {nums[i], nums[j], -tmp};
        returnVec.push_back(newVec);
      }
    }
  }

  return returnVec;
}

int binarySearch(const std::vector<int>& arr, int l, int r, int val) {
  int m;
  while (l <= r) {
    m = (l + r) / 2;
    if (arr[m] < val) {
      l = m + 1;
    } else if (arr[m] > val) {
      r = m - 1;
    } else
      return m;
  }

  return -1;
}

std::vector<std::vector<int>> threeSumSearch(std::vector<int>& nums) {
  std::vector<std::vector<int>> returnVec;
  std::sort(nums.begin(), nums.end());

  int tmp, find;
  for (int i = 0; i < int(nums.size()) - 1; ++i) {
    if (i != 0 && nums[i] == nums[i - 1]) continue;
    for (int j = i + 1; j < nums.size(); ++j) {
      if (j != i + 1 && nums[j] == nums[j - 1]) continue;
      tmp = nums[i] + nums[j];
      find = binarySearch(nums, j + 1, nums.size() - 1, -tmp);
      if (find != -1) {
        std::vector<int> newVec = {nums[i], nums[j], nums[find]};
        returnVec.push_back(newVec);
      }
    }
  }

  return returnVec;
}

int main() {
  srand(0);
  std::vector<int> a;
  std::vector<int> b;
  std::vector<int> c;

  int s = 1500;
  std::cout << "# Size" << '\t' << "Hashing build-up O(n^2)" << '\t' << "Hashing pre-processing O(n^2)" << "Search-and-sort O(n^2log(n))" << std::endl;
  int push;
  for (int i = 2; i <= s; i += 2) {
    for (int j = 0; j < i; ++j) {
      push = rand() % 20000;
      if (rand() % 3) push *= -1;
      a.push_back(push);
    }

      b = a;
      c = a;

      clock_t clock_a_start = clock();
      threeSumOnePass(a);
      clock_t clock_a_stop = clock();

      clock_t clock_b_start = clock();
      threeSumTwoPass(b);
      clock_t clock_b_stop = clock();

      clock_t clock_c_start = clock();
      threeSumSearch(c);
      clock_t clock_c_stop = clock();

      std::cout << i << '\t';
      std::cout << (float)(clock_a_stop - clock_a_start)/(CLOCKS_PER_SEC/1000) << '\t';
      std::cout << (float)(clock_b_stop - clock_b_start)/(CLOCKS_PER_SEC/1000) << '\t';
      std::cout << (float)(clock_c_stop - clock_c_start)/(CLOCKS_PER_SEC/1000) << std::endl;

      a.clear();
  }
}

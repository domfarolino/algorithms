#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/range-sum-query-immutable/description/

class RangeSumQuery {
private:
  std::vector<int> left;

public:
  RangeSumQuery(const std::vector<int>& input): left(input.size() + 1, 0) {
    for (int i = 1; i < left.size(); ++i)
      left[i] = input[i - 1] + left[i - 1];
  }

  int query(int i, int j) {
    return left[j + 1] - left[i];
  }
};

int main() {
  std::vector<int> range = {-2, 0, 3, -5, 2, -1};
  RangeSumQuery rsq(range);
  std::cout << rsq.query(0, 2) << std::endl;
  std::cout << rsq.query(2, 5) << std::endl;
  std::cout << rsq.query(0, 5) << std::endl;
  return 0;
}

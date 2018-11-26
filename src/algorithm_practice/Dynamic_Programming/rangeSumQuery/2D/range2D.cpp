#include <iostream>
#include <vector>

class RangeSumQuery2D {
private:
  std::vector<std::vector<int>> dp;

public:
  RangeSumQuery2D(const std::vector<std::vector<int>>& matrix): dp(matrix) {
    // Dynamic programming preprocessing.

    for (int r = 0; r < dp.size(); ++r) {
      for (int c = 0; c < dp[r].size(); ++c) {
        if (r == 0 && c >= 1)
          dp[r][c] += dp[r][c - 1];
        else if (c == 0 && r >= 1)
          dp[r][c] += dp[r - 1][c];
        else if (r >= 1 && c >= 1)
          dp[r][c] += (dp[r - 1][c] + dp[r][c - 1] - dp[r - 1][c - 1]);
      } // end for.
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    int allInclusive = dp[row2][col2];
    int allLeft = (col1 == 0) ? 0 : dp[row2][col1 - 1];
    int allAbove = (row1 == 0) ? 0 : dp[row1 - 1][col2];
    int doubleCounted = (row1 == 0 || col1 == 0) ? 0 : dp[row1 - 1][col1 - 1];

    return allInclusive - allLeft - allAbove + doubleCounted;
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {{3, 0, 1, 4, 2},
                                          {5, 6, 3, 2, 1},
                                          {1, 2, 0, 1, 5},
                                          {4, 1, 0, 1, 7},
                                          {1, 0, 3, 0, 5}};

  RangeSumQuery2D rsq(matrix);
  std::cout << rsq.sumRegion(2, 1, 4, 3) << std::endl;
  std::cout << rsq.sumRegion(1, 1, 2, 2) << std::endl;
  std::cout << rsq.sumRegion(1, 2, 2, 4) << std::endl;
  std::cout << rsq.sumRegion(1, 3, 1, 3) << std::endl;
  std::cout << rsq.sumRegion(2, 2, 2, 2) << std::endl;
  std::cout << rsq.sumRegion(0, 0, 0, 0) << std::endl;
  return 0;
}

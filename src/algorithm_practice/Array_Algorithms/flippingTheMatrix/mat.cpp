#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

// Source:
//   - https://www.hackerrank.com/contests/world-codesprint-6/challenges/flipping-the-matrix
//   - https://www.hackerrank.com/challenges/flipping-the-matrix

/**
 * Flipping the matrix
 * Each value in the upper left
 * quadrant of has three other corresponding
 * values in the matrix. They are in the other
 * three quadrants. The key realization to make
 * is that it is possible to replace some quadrant
 * value with any of the other three candidates without
 * changing any other values in any other quadrant. This
 * allows us to not worry about tradeoffs we might think we
 * need to consider when reversing a row or a column. With this
 * realization under our belt we don't have to go through any real
 * reversing actions, instead we can just choose the maximum of all
 * candidates for some position, for all n positions.
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 */

void initMatrix(std::vector<std::vector<int>>& inputMatrix, int n) {
  inputMatrix.clear();
  inputMatrix.resize(n * 2, std::vector<int>(n * 2));
  for (int i = 0; i < n * 2; ++i) {
    for (int j = 0; j < n * 2; ++j) {
      std::cin >> inputMatrix[i][j];
    }
  }
}

int max(int m1, int m2, int m3, int m4) {
  return std::max(m4, std::max(m3, std::max(m1, m2)));
}

long maxSum(std::vector<std::vector<int>>& matrix) {
  long returnMaxSum = 0;
  int topLeft, topRight, bottomLeft, bottomRight;

  for (int i = 0; i < matrix.size() / 2; ++i) {
    for (int j = 0; j < matrix.size() / 2; ++j) {
      topLeft = matrix[i][j];
      topRight = matrix[i][matrix.size() - 1 - j];
      bottomLeft = matrix[matrix.size() - 1 - i][j];
      bottomRight = matrix[matrix.size() - 1 - i][matrix.size() - 1 - j];
      returnMaxSum += max(topLeft, topRight, bottomLeft, bottomRight);
    }
  }

  return returnMaxSum;
}

int main() {
  int q, n;
  std::cin >> q;
  std::vector<std::vector<int>> matrix;

  for (int i = 0; i < q; ++i) {
    std::cin >> n;
    initMatrix(matrix, n);
    std::cout << maxSum(matrix) << std::endl;
  }

  return 0;
}

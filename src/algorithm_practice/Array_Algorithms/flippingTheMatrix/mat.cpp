#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Source: https://www.hackerrank.com/contests/world-codesprint-6/challenges/flipping-the-matrix

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

void initMatrix(vector<vector<int> >& inputMatrix, int n) {
  inputMatrix.clear();
  inputMatrix.resize(2*n, vector<int>(2*n));
  for (int i = 0; i < 2*n; ++i) {
    for (int j = 0; j < 2*n; ++j) {
      cin >> inputMatrix[i][j];
    }
  }
}

int max(int m1, int m2, int m3, int m4) {
  return max(m4, max(m3, max(m1, m2)));
}

long maxSum(vector<vector<int> >& matrix) {
  long returnMaxSum = 0;
  int topLeft, topRight, bottomLeft, bottomRight;

  for (int i = 0; i < matrix.size()/2; ++i) {
    for (int j = 0; j < matrix.size()/2; ++j) {
      topLeft = matrix[i][j];
      topRight = matrix[i][matrix.size()-1-j];
      bottomLeft = matrix[matrix.size()-1-i][j];
      bottomRight = matrix[matrix.size()-1-i][matrix.size()-1-j];
      returnMaxSum += max(topLeft, topRight, bottomLeft, bottomRight);
    }
  }

  return returnMaxSum;
}

int main() {
  int q, n;
  cin >> q;
  vector<vector<int> > matrix;

  for (int i = 0; i < q; ++i) {
    cin >> n;
    initMatrix(matrix, n);
    cout << maxSum(matrix) << endl;
  }

  return 0;
}

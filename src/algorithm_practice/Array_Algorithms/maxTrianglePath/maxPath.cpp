#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Source: Yodle careers

/**
 * Given stdin that represents a triangle
 * where any given row has one more element
 * the previous row, assume these rows contain
 * integer values and return the maximum sum of
 * some path starting at the top and moving to adjacent
 * numbers on the row below until you get to the bottom.
 *
 * I think it is best to model the input as a two dimensional
 * vector. The recursive definition for this problem is trivial:
 * maxPath(r, c) = triangle[r][c] + max(maxPath(r + 1, c), maxPath(r + 1, c + 1)).
 * In this case, r and c stand for "rows" and "columns" and if ever r and c are
 * out of bounds, the sum to return is 0 (this acts as our base case).
 * This algorithm can be very slow because it implements tree recursion
 * and does not reuse any calculated data over again.
 * Time complexity: O(n^2)
 * Space complexity: O(h) height of the triangle
 *
 * The iterative solution is more efficient and stems from our need to save
 * and reuse data we've already calculated. This is exactly how dynamica programming
 * works, and in this case it is easy to implement because we have the overlapping
 * subproblem property as well as the optimal substructure given by our recursive definition.
 * What we can do is build a two dimensional array the same size as our input and call it memo.
 * memo[r][c] would contain the maximum sum possible you could attain while ending at point [r][c].
 * We can build our two dimensional vector from the top down using "tabulation". Our new iterative
 * definition becomes: memo[r][c] = triangle[r][c] + max(memo[r-1][c], memo[r-1][c-1]). memo[0][0]
 * is equivalent to triangle[0][0] of course. Our return value will be the largest value in our memo
 * or if the triangle allows negative numbers, the largest memo value in the last row.
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

// Utility function to print triangle
void print2DVector(const vector<vector<unsigned long> >& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = 0; j <= i; ++j) {
      cout << vec[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  int numRows;
  cin >> numRows;
  // Assuming no triangle values are less than 0
  vector<vector<unsigned long> > triangle(numRows, vector<unsigned long>());

  for (int r = 0; r < numRows; ++r) {
    triangle[r].resize(r+1);
    for (int c = 0; c <= r; ++ c) {
      cin >> triangle[r][c];
      if (!r && !c) continue;
      else if (!c) triangle[r][c] += triangle[r-1][c];
      else triangle[r][c] += max(triangle[r-1][c], triangle[r-1][c-1]);
    }
  }

  cout << "maxPathSum: " << *max_element(triangle[triangle.size()-1].begin(), triangle[triangle.size()-1].end()) << endl;
  return 0;
}

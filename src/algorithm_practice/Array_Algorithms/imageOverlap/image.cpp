#include <iostream>
#include <algorithm>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-84/problems/image-overlap/

/**
 * Image Overlap
 * Personally I couldn't find a good optimized solution for this one. Initially I
 * thought a good way might be to break the problem down to a simpler form. The first
 * thing I wanted to ensure was correct was that it didn't matter which image we "shifted"
 * in any direction; shifting one cannot produce an overlap value that shifting the other in
 * the inverse direction cannot. This is true :). I then thought that perhaps a good way to approach
 * a simplified version of this problem was to calculate the maximum overlap values achieved with all
 * horizontal shifts of the B image, and then all vertical shifts of the B image. There are 2*(n - 1) + 1
 * ways you can shift image B of size n * n, such that B still has at least one row or column overlapping
 * with A. This could tell you whether it was beneficial to shift B either left/right or up/down to maximize
 * overlap value, but falls apart in some cases where a diagonal shift is best. For example, we might have a
 * low overlap with a horizontal B shift of 2, and low overlap with a vertical B shift of 2, but a very high
 * overlap when these were combined to form a diagonal shift; this solution fails to communicate this.
 *
 * I opted for the brute force solution, which isn't terribly slow for small values of n (see complexity below).
 * Basically the plan was two-fold:
 * 1.) Iterate through all possible "shifts" of B, maintaining variables for the magnitude of row- and column-shifts
 *     B is undergoing.
 * 2.) Write a factored-out function that takes in two images A and B, and two values for the row- and column-shift
 *     magnitude. This function should be able to return the |1| overlap amount that image B, when shifted by the given
 *     amount of rows and columns, shares with image A.
 *
 * Most of the tricks are in (2), which itself is actually relatively easy. It is key to see that when B is shifted, there
 * are is some number of rows and columns in A that we won't compare with anything, this we can ignore them. We just have to
 * make sure handle negative shifts correctly. The logic is relatively easy, see below:
 *
 * Complexity analysis:
 * Time complexity: O((2*(n - 1))^2 * n^2) ∈ O(n^4)
 * Space complexity: O(1)
 */

int overlapAmount(const std::vector<std::vector<int> >& a, const std::vector<std::vector<int> >& b, int rShift, int cShift) {
  int returnOverlapAmount = 0;

  for (int r = 0, rowShift = rShift; r < a.size() && rowShift < (int)a.size(); ++r, ++rowShift) {
    if (rowShift < 0) continue;

    for (int c = 0, colShift = cShift; c < a.size() && colShift < (int)a.size(); ++c, ++colShift) {
      if (colShift < 0) continue;
      if (a[r][c] && b[rowShift][colShift]) returnOverlapAmount++;
    }

  }

  return returnOverlapAmount;
}

int largestOverlap(const std::vector<std::vector<int> >& a, const std::vector<std::vector<int> >& b) {
  int n = a.size(); // a & b are square matrices
  int maxOverlap = 0;

  // Shift b's rows from -(n - 1) => n - 1
  for (int r = -(n - 1); r <= n - 1; ++r) {

    // Shift b's cols from -(n - 1) => n - 1
    for (int c = -(n - 1); c <= n - 1; ++c) {
      maxOverlap = std::max(maxOverlap, overlapAmount(a, b, r, c));
    }

  }

  return maxOverlap;
}

int main() {
  std::vector<std::vector<int> > a = {{1, 1, 0}, {0, 1, 0}, {0, 1, 0}};
  std::vector<std::vector<int> > b = {{0, 0, 0}, {0, 1, 1}, {0, 0, 1}};
  std::cout << largestOverlap(a, b) << std::endl;

  a = {{0,0,0,0,0},{0,1,0,0,0},{0,0,1,0,0},{0,0,0,0,1},{0,1,0,0,1}};
  b = {{1,0,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{0,1,1,1,1},{1,0,1,1,1}};
  std::cout << largestOverlap(a, b) << std::endl;

  a = {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}};
  b = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0}};
  std::cout << largestOverlap(a, b) << std::endl;
  return 0;
}

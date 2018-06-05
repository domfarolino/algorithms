#include <iostream>
#include <vector>
#include <unordered_set>

// Source: https://leetcode.com/contest/weekly-contest-86/problems/magic-squares-in-grid/

/**
 * Magic Squares in Grid
 * This problem is relatively straightforward, just a few gotchas
 * if you don't consider all of the cases. It's pretty trivial to implement,
 * and is mostly brute-force. A couple things caught me up, so consider all of
 * these cases:
 *
 * - Ensure that all of the values in a candidate grid are unique
 * - Ensure all of the values in a candidate grid are 1 <= x <= 9
 * - Ensure all of the necessary sums are unique
 *
 * Complexity analysis
 * Time complexity: O(n * m), we're iterating a number of times proportional to the size of the entire grid
 * Space complexity: O(1), we don't need to store additional info proportional to the input size, and can eve
 *   take the input size as a const reference to avoid copying :)
 */

// Time complexity: O(1)
// Space complexity: O(1)
// Magic 3x3 grid detector helper function
// Caller must guarantee that this function will not go off the end of
// either a column or row
bool isMagic(const std::vector<std::vector<int> >& grid, int x, int y) {
  int tl = grid[x][y], tm = grid[x][y + 1], tr = grid[x][y + 2],
      ml = grid[x + 1][y], mm = grid[x + 1][y + 1], mr = grid[x + 1][y + 2],
      bl = grid[x + 2][y], bm = grid[x + 2][y + 1], br = grid[x + 2][y + 2];
  std::unordered_set<int> s = {tl, tm, tr, ml, mm, mr, bl, bm, br};
  if (s.size() != 9) return false;
  for (std::unordered_set<int>::const_iterator b = s.begin(); b != s.end(); b++) {
    if (*b >= 10 || *b <= 0) return false;
  }

  int r1sum = tl + tm + tr;
  int r2sum = ml + mm + mr;
  int r3sum = bl + bm + br;

  int c1sum = tl + ml + bl;
  int c2sum = tm + mm + bm;
  int c3sum = tr + mr + br;

  int d1sum = tl + mm + br;
  int d2sum = tr + mm + bl;
  s = {r1sum, r2sum, r3sum, c1sum, c2sum, c3sum, d1sum, d2sum};
  return (s.size() == 1);
}

int numMagicSquares(const std::vector<std::vector<int> >& grid) {
  int numMagic = 0;
  if (grid.size() < 3 || grid[1].size() < 3) return numMagic;
  for (int r = 0; r < grid.size() - 2; r++) {
    for (int c = 0; c < grid[1].size() - 2; c++) {
      if (isMagic(grid, r, c)) numMagic++;
    }
  }

  return numMagic;
}

int main() {
  std::vector<std::vector<int> > grid = {
                                          {4, 3, 8, 4},
                                          {9, 5, 1, 9},
                                          {2, 7, 6, 2}
                                        };
  std::cout << numMagicSquares(grid) << std::endl;
  grid = {
          {10, 3, 5},
          {1, 6, 11},
          {7, 9, 2}
        };
  std::cout << numMagicSquares(grid) << std::endl;
  grid = {{8}};
  std::cout << numMagicSquares(grid) << std::endl;
  grid = {
          {7, 0, 5},
          {2, 4, 6},
          {3, 8, 1}
        };
  std::cout << numMagicSquares(grid) << std::endl;
  return 0;
}

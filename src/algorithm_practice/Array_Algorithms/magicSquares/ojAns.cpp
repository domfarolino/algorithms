// Source: https://leetcode.com/contest/weekly-contest-86/problems/magic-squares-in-grid/

class Solution {
public:
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

int numMagicSquaresInside(const std::vector<std::vector<int> >& grid) {
  int numMagic = 0;
  if (grid.size() < 3 || grid[1].size() < 3) return numMagic;
  for (int r = 0; r < grid.size() - 2; r++) {
    for (int c = 0; c < grid[1].size() - 2; c++) {
      if (isMagic(grid, r, c)) numMagic++;
    }
  }

  return numMagic;
}

};

// Source: https://leetcode.com/contest/weekly-contest-84/problems/image-overlap/

class Solution {
public:
int overlapAmount(const std::vector<std::vector<int> >& a, const std::vector<std::vector<int> >& b, int rShift, int cShift) {
  //std::cout << "Seeing how much overlap we get with B shifted (" << rShift << "," << cShift << ")" << std::endl;
  int returnOverlapAmount = 0;

  for (int r = 0, rowShift = rShift; r < a.size() && rowShift < (int)a.size(); ++r, ++rowShift) {
    if (rowShift < 0) continue;

    for (int c = 0, colShift = cShift; c < a.size() && colShift < (int)a.size(); ++c, ++colShift) {
      if (colShift < 0) continue;

      if (a[r][c] && b[rowShift][colShift]) {
        //std::cout << "  With B shifted " << rShift << "," << cShift << " we found 1's at A(" << r << "," << c << ") & B(" << rowShift << "," << colShift << ")" << std::endl;
        returnOverlapAmount++;
      } //else std::cout << "  Nothing @ A(" << r << "," << c << ") & B(" << rowShift << "," << colShift << ")" << std::endl;
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
};

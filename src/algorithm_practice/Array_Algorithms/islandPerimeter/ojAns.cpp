// Source: https://leetcode.com/problems/island-perimeter/
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
      int totalPerimCount = 0;
      for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
          if (grid[i][j]) {
            if (i == 0 || grid[i - 1][j] == 0) totalPerimCount++;
            if (i == grid.size() - 1 || grid[i+1][j] == 0) totalPerimCount++;
            if (j == 0 || grid[i][j - 1] == 0) totalPerimCount++;
            if (j == grid[0].size() - 1 || grid[i][j+1] == 0) totalPerimCount++;
          }
        }
      }

      return totalPerimCount;
    }
};

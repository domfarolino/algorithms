// 0: Touches nothing
// 1: |       Pacific
// 2: |       Atlantic
// 3: |       Pacific & Atlantic
int dfsNaive(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>& visited, int r, int c, int parent = INT_MAX) {
  if (r < 0 || c < 0 || r >= matrix.size() || c >= matrix[r].size() ||
      visited[r][c] || matrix[r][c] > parent) {
    return 0;
  }

  bool isPacific = false, isAtlantic = false;
  // Base cases
  if ((r == 0 && c == 0) && (r == matrix.size() - 1 && c == matrix[r].size() - 1)) return 3;
  if (r == 0 || c == 0) isPacific = true;
  if (r == matrix.size() - 1 || c == matrix[r].size() - 1) isAtlantic = true;

  // Mark (r, c) as "visited".
  visited[r][c] = true;

  // Recurse
  int top = dfsNaive(matrix, visited, r - 1, c, matrix[r][c]), left = dfsNaive(matrix, visited, r, c - 1, matrix[r][c]),
      bottom = dfsNaive(matrix, visited, r + 1, c, matrix[r][c]), right = dfsNaive(matrix, visited, r, c + 1, matrix[r][c]);

  // Return relevant values.
  bool touchesBoth     = ((isPacific && isAtlantic) || top == 3 || left == 3 || bottom == 3 || right == 3);
  bool touchesPacific  = (isPacific || top == 1 || left == 1 || bottom == 1 || right == 1);
  bool touchesAtlantic = (isAtlantic || top == 2 || left == 2 || bottom == 2 || right == 2);

  if (touchesBoth || (touchesPacific && touchesAtlantic)) return 3;
  else if (touchesPacific) return 1;
  else if (touchesAtlantic) return 2;

  return 0;
}

// Naive algorithm.
// Complexity analysis:
//  - Time complexity: O((n*m)^2)
//  - Space complexity: O(n*m)
std::vector<std::pair<int, int>> pacificAtlanticNaive(const std::vector<std::vector<int>>& matrix) {
  std::vector<std::pair<int, int>> returnPairs;
  if (!matrix.size() || !matrix[0].size()) return returnPairs;
  std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));
  for (int r = 0; r < matrix.size(); ++r) {
    for (int c = 0; c < matrix[r].size(); ++c) {
      // Reset the visited matrix.
      for (std::vector<bool>& visitedRow: visited)
        for (int i = 0; i < visitedRow.size(); ++i)
          visitedRow[i] = false;
      if (dfsNaive(matrix, visited, r, c) == 3)
        returnPairs.push_back(std::make_pair(r, c));
    }
  }

  return returnPairs;
}

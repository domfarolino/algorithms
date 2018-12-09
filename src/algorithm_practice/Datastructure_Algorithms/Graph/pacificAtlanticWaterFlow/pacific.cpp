#include <iostream>
#include <climits>
#include <utility>
#include <vector>

// Source: https://leetcode.com/problems/pacific-atlantic-water-flow/description/

// 0: Touches nothing
// 1: |       Pacific
// 2: |       Atlantic
// 3: |       Pacific & Atlantic
int dfs(std::vector<std::vector<int>>& matrix, int r, int c, int parent = INT_MAX) {
  if (r < 0 || c < 0 || r >= matrix.size() || c >= matrix[r].size() ||
      matrix[r][c] == -1 || matrix[r][c] > parent) {
    return 0;
  }

  bool isPacific = false, isAtlantic = false;
  // Base cases
  if ((r == 0 && c == 0) && (r == matrix.size() - 1 && c == matrix[r].size() - 1)) return 3;
  if (r == 0 || c == 0) isPacific = true;
  if (r == matrix.size() - 1 || c == matrix[r].size() - 1) isAtlantic = true;

  // Mark (r, c) as "visited".
  int tmp = matrix[r][c];
  matrix[r][c] = -1;

  // Recurse
  int top = dfs(matrix, r - 1, c, tmp), left = dfs(matrix, r, c - 1, tmp),
      bottom = dfs(matrix, r + 1, c, tmp), right = dfs(matrix, r, c + 1, tmp);

  matrix[r][c] = tmp;

  // Return relevant values.
  bool touchesBoth     = ((isPacific && isAtlantic) || top == 3 || left == 3 || bottom == 3 || right == 3);
  bool touchesPacific  = (isPacific || top == 1 || left == 1 || bottom == 1 || right == 1);
  bool touchesAtlantic = (isAtlantic || top == 2 || left == 2 || bottom == 2 || right == 2);

  if (touchesBoth || (touchesPacific && touchesAtlantic)) {
    return 3;
  } else if (touchesPacific) {
    return 1;
  } else if (touchesAtlantic) {
    return 2;
  }

  return 0;
}

// Naive algorithm.
// Complexity analysis:
//  - Time complexity: O(n^2)
//  - Space complexity: O(1)
std::vector<std::pair<int, int>> pacificAtlanticNaive(std::vector<std::vector<int>>& matrix) {
  std::vector<std::pair<int, int>> returnPairs;
  for (int r = 0; r < matrix.size(); ++r) {
    for (int c = 0; c < matrix[r].size(); ++c) {
      if (dfs(matrix, r, c) == 3)
        returnPairs.push_back(std::make_pair(r, c));
    }
  }

  return returnPairs;
}

// Optimized algorithm.
// Complexity analysis:
//  - Time complexity: O(n)
//  - Space complexity: O(n)
std::vector<std::pair<int, int>> pacificAtlantic(std::vector<std::vector<int>>& matrix) {
  std::vector<std::pair<int, int>> returnPairs;
  return returnPairs;
}

void printResults(std::vector<std::pair<int, int>>& pairs) {
  for (std::pair<int, int>& pair: pairs) {
    std::cout << "[" << pair.first << "," << pair.second << "]" << std::endl;
  }
}

int main() {
  int r, c;

  std::cout << "Enter the number of rows: " << std::endl;
  std::cin >> r;

  std::cout << "Enter the number of columns: " << std::endl;
  std::cin >> c;

  std::vector<std::vector<int>> matrix(r, std::vector<int>(c, 0));

  // Read in the matrix
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      std::cin >> matrix[i][j];
    }
  }

  std::vector<std::pair<int, int>> pairs = pacificAtlanticNaive(matrix);
  printResults(pairs);
  return 0;
}

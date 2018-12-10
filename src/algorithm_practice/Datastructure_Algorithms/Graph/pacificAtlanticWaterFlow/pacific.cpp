#include <iostream>
#include <cstdlib> // for rand() etc.
#include <cassert>
#include <climits>
#include <utility>
#include <vector>

// Source: https://leetcode.com/problems/pacific-atlantic-water-flow/description/

#include "pacificNaiveInclude.cpp"

void dfs(const std::vector<std::vector<int>>& matrix,
         std::vector<std::vector<bool>>& ocean,
         int r, int c, int parent = INT_MIN) {
  if (r < 0 || c < 0 || r >= matrix.size() || c >= matrix[r].size() ||
      ocean[r][c] || matrix[r][c] < parent) {
    return;
  }

  // Assert: (r, c) is in bounds
  ocean[r][c] = true;

  // Recurse.
  dfs(matrix, ocean, r - 1, c, matrix[r][c]);
  dfs(matrix, ocean, r, c - 1, matrix[r][c]);
  dfs(matrix, ocean, r + 1, c, matrix[r][c]);
  dfs(matrix, ocean, r, c + 1, matrix[r][c]);
}

// Optimized algorithm.
// Complexity analysis:
//  - Time complexity: O(n*m)
//  - Space complexity: O(n*m)
std::vector<std::pair<int, int>> pacificAtlantic(const std::vector<std::vector<int>>& matrix) {
  std::vector<std::pair<int, int>> returnPairs;
  if (!matrix.size()) return returnPairs;
  std::vector<std::vector<bool>> touchesPacific(matrix.size(), std::vector<bool>(matrix[0].size(), false)),
                                 touchesAtlantic(matrix.size(), std::vector<bool>(matrix[0].size(), false));

  for (int r = 0; r < matrix.size(); ++r) {
    dfs(matrix, touchesPacific, r, 0);
    dfs(matrix, touchesAtlantic, r, matrix[r].size() - 1);
  }

  for (int c = 0; c < matrix[0].size(); ++c) {
    dfs(matrix, touchesPacific, 0, c);
    dfs(matrix, touchesAtlantic, matrix.size() - 1, c);
  }

  for (int r = 0; r < matrix.size(); ++r) {
    for (int c = 0; c < matrix[r].size(); ++c) {
      if (touchesPacific[r][c] && touchesAtlantic[r][c])
        returnPairs.push_back(std::make_pair(r, c));
    }
  }

  return returnPairs;
}

void printResults(std::vector<std::pair<int, int>>& pairs) {
  for (std::pair<int, int>& pair: pairs) {
    std::cout << "[" << pair.first << "," << pair.second << "]" << std::endl;
  }
}

int main() {
  // Uncomment the below section, and comment-out the below-below section
  // in order to test the algorithms on input from stdin (like test.in for
  // example).
  /*
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

  std::vector<std::pair<int, int>> pairsNaive = pacificAtlanticNaive(matrix);
  std::vector<std::pair<int, int>> pairs = pacificAtlantic(matrix);
  printResults(pairsNaive);
  */
  srand(time(NULL));
  int n;
  std::vector<std::vector<int>> matrix;
  for (n = 0; n < 55; n += 1) {
    matrix = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        matrix[r][c] = rand() % 4;
      }
    }

    // Run the algorithms with the newly randomized matrix.
    clock_t clock_a_start = clock();
    std::vector<std::pair<int, int>> pairsNaive = pacificAtlanticNaive(matrix);
    clock_t clock_a_stop = clock();

    clock_t clock_b_start = clock();
    std::vector<std::pair<int, int>> pairs = pacificAtlantic(matrix);
    clock_t clock_b_stop = clock();

    assert(pairsNaive == pairs);

    std::cout << n*n << '\t';
    std::cout << (float)(clock_a_stop - clock_a_start) / (CLOCKS_PER_SEC / 1000) << '\t';
    std::cout << (float)(clock_b_stop - clock_b_start) / (CLOCKS_PER_SEC / 1000) << std::endl;
  }

  return 0;
}

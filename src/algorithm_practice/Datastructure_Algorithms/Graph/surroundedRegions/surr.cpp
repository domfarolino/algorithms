#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

// Source: https://leetcode.com/problems/surrounded-regions/description/

/**
 * Surrounded Regions
 */

struct pairHash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

void dfsGetEscaped(int r, int c, std::unordered_set<std::pair<int, int>, pairHash>& visited, const std::vector<std::vector<char> >& board) {
  if (r < 0 || r >= board.size() ||
      c < 0 || c >= board[0].size() ||
      board[r][c] == 'X' ||
      visited.find(std::make_pair(r, c)) != visited.end()) {
    return;
  }

  // Visit current node.
  visited.insert(std::make_pair(r, c));

  // Recurse on all potential neighbors.
  dfsGetEscaped(r + 1, c, visited, board);
  dfsGetEscaped(r - 1, c, visited, board);
  dfsGetEscaped(r, c + 1, visited, board);
  dfsGetEscaped(r, c - 1, visited, board);
}

// Swap out instances of `dfsGetEscaped` with `bfsGetEscaped` to use the
// other form of this solution.
void convertSurroundedRegions(std::vector<std::vector<char> >& board) {
  // Necessary, given the way that we build our `visited` set.
  if (!board.size()) return;

  std::unordered_set<std::pair<int, int>, pairHash> visited;

  // Visit all "O"s touching the outside rows.
  for (int c = 0; c < board[0].size(); ++c) {
    dfsGetEscaped(0, c, visited, board);
    dfsGetEscaped(board.size() - 1, c, visited, board);
  }

  // Visit all "O"s touching the outside columns.
  for (int r = 0; r < board.size(); ++r) {
    dfsGetEscaped(r, 0, visited, board);
    dfsGetEscaped(r, board[0].size() - 1, visited, board);
  }

  for (int r = 0; r < board.size(); ++r) {
    for (int c = 0; c < board[r].size(); ++c) {
      if (visited.find(std::make_pair(r, c)) == visited.end())
        board[r][c] = 'X';
    }
  }
}

// Helper function to print matrix.
void printMatrix(const std::vector<std::vector<char> >& board) {
  for (int r = 0; r < board.size(); ++r) {
    for (int c = 0; c < board[r].size(); ++c) {
      std::cout << board[r][c] << ", ";
    }

    std::cout << std::endl;
  }
}

int main() {
  std::vector<std::vector<char> > board = {{'X', 'X', 'X'}, {'X', 'O', 'O'}, {'X', 'X', 'X'}};
  std::cout << "Before:" << std::endl;
  printMatrix(board);

  std::cout << std::endl << "After:" << std::endl;
  convertSurroundedRegions(board);
  printMatrix(board);

  board[1][2] = 'X';
  std::cout << std::endl << "Before:" << std::endl;
  printMatrix(board);

  std::cout << std::endl << "After:" << std::endl;
  convertSurroundedRegions(board);
  printMatrix(board);

  return 0;
}

#include <iostream>

// Source: Cracking the Coding Interview (5th Edition) (I think?)

/**
 * Given a 3x3 tic tac toe board you are to write an algorithm
 * to determine if there is a winner.
 *
 * Input will be a 3x3 array of integers where value 1 indicates an "x",
 * 2 indicates a "o", and 0 indicates an empty space. You are to return 1
 * if "x" wins, 2 if "o" wins, 0 if there is no winner and the board is not
 * full, -1 if there is no winner and the board is full.
 *
 * My first idea is that we'd want to go through every position on the board and
 * for non-zero integers, determine if the integer is part of a 3-character-long streak
 * or not. Thinking about this was pretty messy as we end up dealing with a ton of conditionals
 * since we're checking streaks that start on all the edges of the board.
 *
 * The solution I eventually arrived at was probably not the most efficient solution but it was
 * much cleaner. Basically for each row, we check each column to determine if there was a winner.
 * Then we perform another pass on each column and check each row to determine if there was a winner
 * yet again. If we don't find a winner this way, we have to check the two diagonals. This whole time
 * we can keep track of whether the board is full or not (whether we've seen at least one zero or not)
 * so that in the case where we don't find a winner, we can quickly return either 0 or -1 indicating
 * whether the board is full or not.
 *
 * Time complexity: O(n^2) where n is the size of one side of the square board
 * Space complexity: O(1)
 */

int isWinner(int board[3][3]) {
  bool sawZero = false;
  int countX, countO;

  // Check if a winner exists in a row
  for (int r = 0; r < 3; r++) {
    countX = 0;
    countO = 0;
    for (int c = 0; c < 3; c++) {
      if (board[r][c] == 1) {
        countX++;
      } else if (board[r][c] == 2) {
        countO++;
      } else sawZero = true;
    }

    if (countX == 3) return 1;
    if (countO == 3) return 2;
  }

  // Check if a winner exists in a column
  for (int c = 0; c < 3; c++) {
    countX = 0;
    countO = 0;
    for (int r = 0; r < 3; r++) {
      if (board[r][c] == 1) {
        countX++;
      } else if (board[r][c] == 2) {
        countO++;
      }
    }

    if (countX == 3) return 1;
    if (countO == 3) return 2;
  }

  // Check for diagonal winner
  if (board[0][0] == board[1][1] == board[2][2] ||
      board[0][2] == board[1][1] == board[2][0]) return board[1][1];
  return (sawZero) ? 0 : -1;
}

int main() {
  int board[3][3] = {{2, 2, 1},
                     {1, 1, 2},
                     {1, 1, 2}
                    };
  std::cout << "Winner: " << isWinner(board) << std::endl;
  return 0;
}

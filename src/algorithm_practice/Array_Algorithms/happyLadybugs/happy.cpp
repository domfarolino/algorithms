#include <iostream>
#include <string>

using namespace std;

// Source: https://www.hackerrank.com/challenges/happy-ladybugs

/**
 * Happy Ladybugs
 * This is a rather simple problem but I enjoyed it.
 * The description can be found in the above source link.
 * This algorithm exibits a common pattern found in ones alike
 * in that it will give you some problem, present to you the solution
 * in the form of a long process that must be gone through, and then only
 * ask you to output some boolean, or maybe the number of times some condition
 * was met. Often, when this is the only required information you can likely get
 * around actually computing the guts of the obvious algorithm but just finding what
 * some condition in the input data that correlates to the output you need.
 *
 * In this case we need to decide if some string of characters is essentially "happy".
 * The definition of "happy" can be found in the problem description but basically we need
 * to look at the input. Either we are given a happy string, or a not-happy string. If the string
 * representing the board is not happy then we need to decide whether it can be made happy or not.
 * In this case any board string can be happy if the number of each type of character > 1 and there
 * is at least ONE empty space in it to move bugs around on the board. If this condition is met then
 * the board can be made happy and we output "YES". We can do this easily by storing the number of times
 * each character appears, and storing some boolean to correspond whether or not there is a space in the
 * string. Note that we can be given an input string which contains no spaces at all, but is happy. In this
 * case our algorithm would return indicate that the string is happy since there are no spaces, so what we first
 * need to do is see if the given string is happy to begin with. Then if it is not, we move onto seeing if it can
 * be made happy, with our aforementioned conditions.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

/**
 * This function is used to determine whether
 * or not some input string is already happy. It
 * is a bit messy, but basically what we need to do
 * is start at some character, and if it has at least
 * one identical neighbor, we need to find either:
 *   1.) The next character that is not the same color
 *   2.) The next character after some space (whether its the same color as the previous one or not)
 * If each found character has at least one identical neighbor then the string is happy.
 */
bool isHappy(string board) {
  char currentColor;
  bool spaceFlag;

  int i = 0;

  while (i < board.size()) {
    spaceFlag = false;
    currentColor = board[i];

    if (i + 1 < board.size() && board[i + 1] == currentColor) {
      i++;
      while (i < board.size()) {
        /**
         * We want to break for the next non-identical neighbor
         * or the very next color after some '_' character (same
         * color or not, doesn't matter since it is space separated)
         */
        if (board[i] == currentColor && spaceFlag) break;
        if (board[i] != currentColor && board[i] != '_') break;

        // Set spaceFlag when we come across one, so we know to break on very next non-space character/color
        if (board[i] == '_') spaceFlag = true;
        i++;
      }
    } else return false;
  }

  return true;
}

bool canBeHappy(string board) {
  if (isHappy(board)) return true; // if its happy, don't move on (might fail our space check)

  int boardMap[26] = {0}; // init to 0
  bool atLeastOneSpace = false;

  for (int i = 0; i < board.length(); ++i) {
    if (board[i] >= 65 && board[i] <= 90) {
      boardMap[board[i] - 65]++;
    } else {
      atLeastOneSpace = true;
    }
  }

  for (int i = 0; i < 26; ++i) {
    if (boardMap[i] == 1) return false;
  }

  return atLeastOneSpace;
}

int main() {
  int queries, n;
  string b;
  cin >> queries;

  for (int i = 0; i < queries; ++i) {
    cin >> n;
    cin >> b;

    if (canBeHappy(b)) {
      cout << "YES";
    } else {
      cout << "NO";
    }

    cout << endl;
  }

  return 0;
}

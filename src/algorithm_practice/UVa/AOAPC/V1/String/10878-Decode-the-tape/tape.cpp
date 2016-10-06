#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=96&page=show_problem&problem=1819

/**
 * Decode the tape
 * The algorithm is pretty easy in theory and
 * coding intensity. The example input provides
 * us with a tape that should provoke us to realize
 * each non-boundary line of the tape represents an ASCII
 * character. Figuring out how to map a strip of the tape to
 * a single character is more difficult. The keen eye will see
 * that there are only two types of characters within the bars `|`
 * of each strip (with the exception of the useless period). The key
 * realization here is to see that each strip is really a binary number
 * made up of a combination of spaces (representing 0s) and letter `o`s
 * (representing 1s). We know that the ASCII table consists of 256 characters
 * meaning we must need log2(256) = 8 bits (since we don't actually have to represent
 * the number 256, only 0-255) to represent any ASCII character. There are exactly 8,
 * bit-representing characters (we are not including the meaningless period) in each strip.
 * We can either go through each strip and create the ASCII table value with bit manipulation
 * or brute force strip traversal.
 *
 * Brute force strip traversal:
 * The method I first came up with was to manually traverse all of the spaces or "o"s in
 * each strip and add a corresponding power of two depending on its position in the strip.
 *
 * Bit manipulation
 * The more maintainable and versatile approach would be to traverse each strip in reverse order which
 * start us at the least significant bit. We then maintain some integer variable which we can bit shift
 * every time we encounter a space or "o" char.. If we come across a "o" however, we add the current value
 * of this variable to some "sum" variable before we shift its bits. At the very last iteration, we will shift
 * our value all the way up to 256 (which we'll never use since our for loop condition will no longer be true).
 */

void tapeRowToCharacter(string tapeRow) {
  int currentAsciiVal = 1;
  int sum = 0;

  int i = tapeRow.length();
  for (int i = tapeRow.length(); i >= 0; --i) {
    if (tapeRow[i] == ' ') {
      currentAsciiVal <<= 1; // keeping this here and not moving out so the algorithm is more clear
    } else if (tapeRow[i] == 'o') {
      sum += currentAsciiVal;
      currentAsciiVal <<= 1;
    }
  }
  
  cout << char(sum);
}

int main() {
  string tmp;

  while (getline(cin, tmp)) {
    if (tmp[0] == '|') tapeRowToCharacter(tmp);
  }
  
  return 0;
}
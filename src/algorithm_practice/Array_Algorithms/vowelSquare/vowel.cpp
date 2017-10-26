#include <iostream>
#include <string>

// Source: https://coderbyte.com/information/Vowel%20Square

/**
 * Vowel Square
 * The idea of this algorithm is that you are given an array of
 * strings which represents a two-dimensional matrix of characters.
 * The goal is to determine whether or not a 2x2 square consisting
 * only of vowels exists in the matrix. The input will be the array
 * of strings, and the output should be a string whose format is "r-c"
 * where r is the row number of the top-left element in the 2x2 square
 * and c is it's column number. You should return "not found" if no square
 * exists.
 *
 * The idea is pretty basic. Essentially for each row, we want to iterate
 * through each column and see if the current position we're at happens to
 * be the top-left corner of a 2x2 all-vowel square. This just requires us
 * to look at 4 adjacent values for every position we visit. We should also
 * realize that since we're looking for a 2x2 square, the last row and last
 * column could never be the top-left corner of said square, therefore we can
 * choose to not iterate over these positions in the matrix. This is an important
 * realization so that we don't try and index outside of the matrix.
 *
 * Time complexity: O(n*m)
 * Space complexity: O(1)
 */

bool isVowel(const char& c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

std::string vowelSquare(const std::string& strArr[], int rows) {
  int cols = (rows) ? strArr[0].length() : 0;
  for (int r = 0; r < rows - 1; ++r) {
    for (int c = 0; c < cols - 1; ++c) {
      if (isVowel(strArr[r][c]) && isVowel(strArr[r][c+1]) && isVowel(strArr[r+1][c]) && isVowel(strArr[r+1][c+1])) {
        return std::to_string(r) + "-" + std::to_string(c);
      }
    }
  }

  return "not found";
}

int main() {
  std::string A[] = {"abccd", "eeeee", "aaaaa"};
  std::cout << vowelSquare(A, sizeof(A)/sizeof(A[0])) << std::endl;
  return 0;
}

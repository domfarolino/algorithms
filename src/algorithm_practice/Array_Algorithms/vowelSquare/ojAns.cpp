// Source: https://coderbyte.com/information/Vowel%20Square
#include <iostream>

bool isVowel(const char& c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

std::string vowelSquare(std::string strArr[], int rows) {
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
  std::string A[] = gets(stdin);
  std::cout << vowelSquare(A, sizeof(A)/sizeof(A[0]));
  return 0;
}

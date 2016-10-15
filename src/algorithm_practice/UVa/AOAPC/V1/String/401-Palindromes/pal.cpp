#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=96&page=show_problem&problem=342

/**
 * Palindromes
 * This solution needs more documentation
 */

bool isPalindrome(const string& input) {
  int low = 0, high = input.size()-1;

  while (low <= high) {
    if (input[low] != input[high]) return false;
    low++;
    high--;
  }

  return true;
}

bool isMirroredString(const string& input, const unordered_map<char, char>& reverses) {
  int low = 0, high = input.size()-1;

  while (low <= high) {
    if (reverses.find(input[low]) == reverses.end() ||
        reverses.find(input[high]) == reverses.end() ||
        reverses.find(input[low])->second != input[high] ||
        reverses.find(input[high])->second != input[low]) return false;
    low++;
    high--;
  }

  return true;
}

int main() {
  bool isPal, isMirror;
  string input;

  unordered_map<char, char> reverses;
  reverses['A'] = 'A';
  reverses['E'] = '3';
  reverses['H'] = 'H';
  reverses['I'] = 'I';
  reverses['J'] = 'L';
  reverses['L'] = 'J';
  reverses['M'] = 'M';
  reverses['O'] = 'O';
  reverses['S'] = '2';
  reverses['T'] = 'T';
  reverses['U'] = 'U';
  reverses['V'] = 'V';
  reverses['W'] = 'W';
  reverses['X'] = 'X';
  reverses['Y'] = 'Y';
  reverses['Z'] = '5';
  reverses['1'] = '1';
  reverses['2'] = 'S';
  reverses['3'] = 'E';
  reverses['5'] = 'Z';
  reverses['8'] = '8';

  while (cin >> input) {
    isPal = isPalindrome(input);
    isMirror = isMirroredString(input, reverses);

    cout << input << " -- ";

    // Both
    if (isPal && isMirror) cout << "is a mirrored palindrome." << endl;
    // None
    else if (!isPal && !isMirror) cout << "is not a palindrome." << endl;
    // Just Palindrome
    else if (isPal) cout << "is a regular palindrome." << endl;
    // Just mirrored string
    else if (isMirror) cout << "is a mirrored string." << endl;

    cout << endl;
  }

  return 0;
}

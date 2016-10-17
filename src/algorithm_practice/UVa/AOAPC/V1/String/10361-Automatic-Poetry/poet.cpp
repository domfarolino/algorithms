#include <iostream>
#include <vector>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=96&page=show_problem&problem=1302
// Simpler solution: https://github.com/marioyc/Online-Judge-Solutions/blob/master/UVA/Contest%20Volumes/10361%20-%20Automatic%20Poetry.cpp

/**
 * Automatic Poetry
 * More documentation needed
 */

/**
 * An alternate solution would just be to find all of the
 * positions in which the '<' and '>' characters appear and
 * take advantage of string::substr
 */

string sanitizeInput(const string& input) {
  string returnString = "";

  for (int i = 0; i < input.length(); ++i) {
    if (input[i] != '<' && input[i] != '>') returnString += input[i];
  }

  return returnString;
}

int main() {
  int total;
  string input1, input2, sanitizedInput1, tmpString;
  vector<string> segments;

  cin >> total;
  cin.ignore();

  for (int i = 0; i < total; ++i) {
    getline(cin, input1);
    getline(cin, input2);

    // Set sanitizedInput1 equal to input1 without the brackets
    sanitizedInput1 = sanitizeInput(input1);

    // Push all segments to vector of string segments
    tmpString = "";
    int c = 0;
    while (c < input1.length()) {
      if (input1[c] == '<' || input1[c] == '>') {
        segments.push_back(tmpString);
        tmpString = ""; // reset tmpString
      } else if (input1[c] != '<' && input1[c] != '>') {
        tmpString += input1[c];
      }
      c++;
    }

    segments.push_back(tmpString);

    /**
     * Print the sanitizedInput1
     * Find where the `...` starts in input2
     * Insert proper segment arrangement after `...`
     * Print the new input2
     */

    // Print the sanitizedInput1
    cout << sanitizedInput1 << endl;

    // Find where the `...` starts in input2
    // Insert proper segment arrangement after `...`
    input2.erase(input2.length()-3, 3);
    input2 += segments[3] + segments[2] + segments[1] + segments[4];

    // Print the new input2
    cout << input2 << endl;

    segments.clear();
  }

  return 0;
}

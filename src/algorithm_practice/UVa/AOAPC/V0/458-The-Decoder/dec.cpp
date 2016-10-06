#include <iostream>
#include <string>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=399

/**
 * The Decoder
 * Just a basic ASCII character shift.
 */

int main() {
  string input;
  
  while (cin >> input) {
    
    for (int i = 0; i < input.length(); ++i) {
      input[i] = input[i]-7;
    }

    cout << input << endl;
  }
  
  return 0;
}
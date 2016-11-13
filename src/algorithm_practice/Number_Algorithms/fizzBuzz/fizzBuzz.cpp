#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Source: https://leetcode.com/problems/fizz-buzz/

/**
 * Actual Fizz Buzz
 * This code intentionally does not follow any
 * recommended style guide. Deal with it thx.
 */

vector<string> fizzBuzz(int n) {
  vector<string> returnVec(n, "");

  for (int i = 1; i <= n; ++i) {
    if (i % 3 && i % 5) returnVec[i-1] = to_string(i);
    else if (i % 3 || i % 5) {
      (i % 3) ? returnVec[i-1] = "Buzz" : returnVec[i-1] = "Fizz";
    } else if (i % 3 == 0 && i % 5 == 0) returnVec[i-1] = "FizzBuzz";
  }

  return returnVec;
}

int main() {
  int n;
  cin >> n;

  vector<string> fizzBuzzVec = fizzBuzz(n);

  for (int i = 0; i < fizzBuzzVec.size(); ++i) {
    cout << fizzBuzzVec[i] << endl;
  }

  return 0;
}

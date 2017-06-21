#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Source: https://leetcode.com/problems/fizz-buzz/

vector<string> fizzBuzz(int n) {
  vector<string> returnVec(n, "");

  for (int i = 1; i <= n; ++i) {
    if (i % 3 == 0 && i % 5 == 0) returnVec[i - 1] = "FizzBuzz";
    else if (i % 3 == 0) returnVec[i - 1] = "Fizz";
    else if (i % 5 == 0) returnVec[i - 1] = "Buzz";
    else returnVec[i - 1] = to_string(i);
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

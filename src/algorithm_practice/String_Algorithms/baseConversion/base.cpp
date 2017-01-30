#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Source: N/A
// SO: http://stackoverflow.com/questions/41654305/recursive-base-conversion-time-complexity-analysis

/**
 * Given an integer `p` and a destination base `b`, return a string representation
 * of `p` in base `b`. If we were given a regular integer of type `int` or something
 * it is really easy to do this since we want the value of (p % b) at a single bit, and
 * then we'll adjust p = (p / b) before computing the next bit. This makes sense because
 * any single "bit" in a base `b` integer can have `b` values ranging from [0, ..., b-1].
 * Now how do we actually add the bits together in sequence? It depends. Let's first assume
 * want to return a string with the least significant digit at the end. While this is more human
 * readable, it is less ideal to perform operations on. We could do this recursively. Assuming the
 * passed in p > 0 (base case), we return the results of ( recursiveCall(p / b, b) + (p % b) ). Notice
 * that we'll be adding the least significant digit at the end of our answer as we want. Unfortunately we're
 * trading this for both time and space efficiency. For example, the original stack frame creates a new string
 * from the + operator of size n = logb(p) by adding strings of size (n - 1) + (1). The next frame also creates
 * a new string, but this time of size (n - 1) by adding strings of size (n - 2) + (1). This repeats, and we create
 * n strings of decreasing size in each level because of the + operator. The result will be in O(n^2) time because
 * n + (n - 1) + (n - 2) + (n - 3) ... = O(n^2). Regarding space complexity, we'll only have one full string in memory
 * at once. The memory will either be in terms of accumulated characters, or recursive stack frames. For example the first
 * frame has one character O(1) + (n - 1) characters held in recursive frames. This will continue and we'll slowly be adding
 * n instances of single characters together making n*O(1) = O(n);
 * Complexity analysis:
 * Time complexity: O(n^2) (n = logb(p))
 * Space complexity: O(n) (n = logb(p))
 *
 * We could also do this iteratively. We could maintain a single return string, and keep appending (n % b) while adjusting n = (n / b).
 * As a result, we'd end up with the string we want but backwards since the least significant digit would appear at the beginning as it is
 * what we calculate first. This answer assumes that += is O(1) for a single character. See http://stackoverflow.com/a/15082239/3947332. The
 * answer seems to indicate O(1) for single character appends, but the third para makes it slightly unclear.
 * Complexity analysis:
 * Time complexity: O(n) (n = logb(p))
 * Space complexity: O(n) (n = logb(p))
 */

string convertIntToBaseRecursive(int number, int base) {
  // Base case
  if (!number) return "";

  // Adding least significant digit to "the rest" computed recursively
  // Could reverse these operations if we wanted the string backwards.
  if (number % base > 10) return convertIntToBaseRecursive(number / base, base) + char(number % base + 55);
  return convertIntToBaseRecursive(number / base, base) + to_string(number % base);
}

string convertIntToBaseIterative(int number, int base) {
  string retString = "";

  while (number) {
    if (number % base > 10) {
      retString += char(number % base + 55);
    } else {
      retString += to_string(number % base);
    }
    number /= base;
  }

  // Only needed if least significant should be at the end
  reverse(retString.begin(), retString.end());
  return retString;
}

int main() {
  for (int i = 2; i <= 36; ++i) {
    cout << "Base " << i << ":" << endl;
    cout << convertIntToBaseRecursive(2017, i) << endl;
    cout << convertIntToBaseIterative(2017, i) << endl;
    cout << "---" << endl;
  }
  return 0;
}

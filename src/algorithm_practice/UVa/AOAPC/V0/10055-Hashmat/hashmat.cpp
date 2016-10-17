#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=996

/**
 * Essentially we just need to return the difference of two numbers.
 * We also must account for very large numbers.
 */

int main() {
  long n1, n2;

  cout.setf(ios::fixed);
  while (cin >> n1 >> n2) {
    cout << setprecision(0) << abs(n1 - n2) << endl;
  }
  return 0;
}

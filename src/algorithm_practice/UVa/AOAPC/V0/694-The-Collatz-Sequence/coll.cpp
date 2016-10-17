#include <iostream>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=635
// Essentially 3n + 1 problem

/**
 * The Collatz Sequence
 * The Collatz Sequence is a fairly
 * famous sequence of numbers. More about
 * it can be found in the problem above. The
 * coding to solve this problem is fairly straightforward.
 */

int main() {
  long long a, tmpA, limit, numTerms;
  int i = 1;

  cin >> a >> limit;

  while (a > 0 && limit > 0) {
    tmpA = a;
    numTerms = 1;

    while (tmpA != 1 && tmpA <= limit) {
      if (!(tmpA%2)) tmpA /= 2;
      else tmpA = 3*tmpA + 1;

      numTerms++;
    }

    if (tmpA != 1) numTerms--; // Don't count last term if it went past limit

    cout << "Case " << i << ": A = " << a << ", limit = " << limit << ", number of terms = " << numTerms << endl;
    cin >> a >> limit;
    ++i;
  }

  return 0;
}

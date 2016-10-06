#include <iostream>
#include <cmath>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=1241

/**
 * Ecological Premium
 * The code is rather self explanatory,
 * we are just doing a simple calculation
 * given some std input. The key is to make
 * sure your types allow for the proper results
 * given some operation.
 */

int main() {
  int total, farmers;
  long out = 0;
  double sqm;
  int animals, ecoDegree;

  cin >> total;

  for (int i = 0; i < total; ++i) {
    cin >> farmers;

    for (int j = 0; j < farmers; ++j) {
      cin >> sqm >> animals >> ecoDegree;
      out += floor(    (((sqm/animals)*ecoDegree)*animals)+.5    ); // round
    }
    cout << out << endl;
    out = 0;
  }
  
  return 0;
}
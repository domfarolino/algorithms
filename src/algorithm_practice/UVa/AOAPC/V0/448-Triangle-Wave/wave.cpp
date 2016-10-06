#include <iostream>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=429

/**
 * Triangle Wave
 * Pretty neat problem, not a big
 * thinker, mainly a coding exercise.
 * To satisfy the OJ it is important to
 * not print extra new line characters at
 * the end of perhaps the last input. This
 * can be done with a simple conditional at
 * the end of some for loops.
 */

int main() {
  int total, amp, freq;

  cin >> total;

  for (int i = 0; i < total; ++i) {
    cin >> amp >> freq;

    for (int f = 0; f < freq; ++f) {
      
      // First part of triangle
      for (int a = 1; a <= amp; ++a) {

        for (int z = 0; z < a; ++z) {
          cout << a;
        }

        cout << endl;
      
      }

      // Second part of triangle
      for (int a = amp-1; a >= 0; --a) {

        for (int z = 0; z < a; ++z) {
          cout << a;
        }

        if (a) cout << endl;
      
      }

      if (i != total-1 || f != freq-1) cout << endl; // The f != freq-1 part is key
    
    }
  
  }
  
  return 0;
}
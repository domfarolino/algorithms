#include <iostream>

using namespace std;

// Source: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=2233

/**
 * We need two algorithms. One to compute the least common multiple
 * of two given numbers, and the other to compute the greatest common
 * factor (divisor) of two given numbers.
 *
 * When doing this algorithm I started with the LCM. Working out a few examples
 * by hand revealed that the range of the LCM of two numbers m, n where m <= n is [n, m*n].
 * In other words the smallest value the LCM of m and n can take is no smaller than the larger
 * of the two numbers (obvious) and the largest value the LCM of m and n can take is no larger than
 * m*n. It should be clear that we can start at m*n (a guaranteed common multiple) and then see if it
 * is possible to trim that number down a bit. So how do we make some common multiple the least common
 * multiple? A few examples on paper made it clear that trimming m*n down meant getting rid of shared factor
 * produced when multiplying together. For example with the numbers 2 and 16, multiplying gives us 32 however
 * since both 2 and 16 share a common factor (2), 32 will contain the shared factor of 2 twice! With values 6 and
 * 8, 6*8 = 48 which is a common multiple of both 6 and 8 however it is not the least common multiple. We could divide
 * 48/2 and be left with a smaller common multiple. This is because both 6 and 8 share a factor of 2 so we can get rid of
 * one of the two duplicate factors by dividing once by two. Let's take a look at one more example: 4, 22. 4*22 = 88 and like
 * before we could divide 88/2 since both values share a factor of two, however we'd have to divide our result (44) by 2 again
 * to get the least common multiple. This is because 4 and 22 share the factor of 2 twice, so we'd either have to divide 88 by
 */

 int gcd(int a, int b) {
   while (a != b) {
     if (a > b) {
       a -= b;
     } else {
       b -= a;
     }
   }

   return a;
 }

unsigned long lcm(int m, int n) {
  //return m / gcd(m, n) * n;
  // We are guaranteed that m <= n
  unsigned long lcmRet = m * n;

  // First factor we want to check to see if both have in common
  int i = m;

  // lcmRet/i >=n because if the next operation could invalidate
  // lcmRet, we want to retun it now, before it gets invalid.
  while (i && lcmRet/i >= n && lcmRet <= m*n) {
    if (m % i == 0 && n % i == 0) {
      // Alternatively we could check if coming operation will
      // make lcmRet in valid if so return it while still good
      if (lcmRet / i < n) return lcmRet;
      lcmRet /= i;
    }
    --i;
  }

  return lcmRet;
}

int main() {
  int t, m, n;
  cin >> t;

  for (int i = 0; i < t; ++i) {
    cin >> m >> n;
    cout << i + 1 << " ";;

    if (m <= n) {
      cout << lcm(m, n) << " " << gcd(m, n);
    } else{
      cout << lcm(n, m) << " " << gcd(n, m);
    }

    cout << endl;
  }

  return 0;
}

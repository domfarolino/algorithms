#include <iostream>

using namespace std;

// Source: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=2233

/**
 * We need two algorithms. One to compute the least common multiple
 * of two given numbers, and the other to compute the greatest common
 * factor (divisor) of two given numbers.
 *
 * When doing this algorithm I started with the LCM. Working out a few examples by
 * hand revealed that the range of the LCM of two numbers m, n where m <= n is [n, m*n].
 * In other words the smallest value the LCM of m and n can take is no smaller than the larger
 * of the two numbers (obvious) and the largest value the LCM can take is no larger than m*n. It
 * should be clear that we can start at m*n (a guaranteed common multiple) and then see if we can
 * trim it down a bit. So how do we make some common multiple the least common multiple? A few examples
 * on paper made it clear that trimming m*n down meant getting rid of shared factors produced when multiplying
 * m*n. For example with the numbers 2 and 16, 2*16 = 32. However, since 2 and 16 share a common factor 2, 32 will
 * contain the shared factor of 2 twice! We can get rid of the duplicate by dividing by 2 once. The logic is similar
 * to the inclusion-exclusion principle. Another example: 8, 28. 8*28 = 224 and like before we COULD divide 224/2 since
 * both values share a factor of 2, however we'd need to divide by 2 some arbitrary number of times. Instead we can get rid
 * of all duplicate 2 factors by dividing by 4 a single time. This implies that all common factors of m and n will appear in
 * their greatest common divisor, thus we can get rid of all of all common duplicate factors by dividing by the GCD. Therefore
 * LCM = m*n/gcd(m, n).
 *
 * Before moving onto the GCD problem I want to extend the inclusion-exclusion idea with LCM a bit further and show from
 * a different angle how this works with unique prime factorizations. As shown earlier, all common factors of two numbers
 * are found in their GCD, so let's see how that looks with their unique prime factorizations.
 *
 * Prime factorization of 8:  2^3
 * Prime factorization of 48: 2^4 * 3^1
 * When we multiply 8*48 we get 2^4 * 2^3 * 3^1. It is obvious that both 8 and 48 share a factor of 8 and that factor of 8 is duplicated
 * in 2^4 * 2^3 * 3^1. We can remove it by getting rid of 2^3 in our product factorization. This idea can be generalized to show that the
 * LCM is product of the largest power of each prime factor. This makes sense because 2^3 (from 8) is contained in 2^4 (from 48) so why
 * would we need to include the factors of 2 from 8 if they're already contained in 48? It makes sense that we have to take the largest
 * power of each prime too since we need to contain the factors of BOTH numbers, thus we're limited by the larger one. It is nice and the
 * logic is symmetric to what we had earlier. Analyzing each prime individually results in the same duplicate deletion yielded from
 * dividing m*n by the GCD.
 *
 * For the GCD, we're taking advantage of the Euclidian description on Wiki. Yay.
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

int lcm(int m, int n) {
  return m*n/gcd(m, n);
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

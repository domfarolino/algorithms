#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// Source: https://www.hackerrank.com/challenges/between-two-sets

/**
 * Between Two Sets
 * The key to this algorithm is realizing that we
 * need to find the least common multiple of all of
 * the numbers in the first set, and then the greatest
 * common divisor of all the numbers in the second set.
 * This is simply because the smallest number such that
 * every number is a set is a factor of is the least common
 * multiple of the set, and if this number is a factor of all
 * numbers in the second set it will certainly be a factor of
 * said set's greatest common factor/divisor. Thus we compute
 * both set values before (a bit of preprocessing), and then we
 * run through all multiples of the LCM <= GCD and keep track
 * how many multiples of the LCM are factors of the GCD.
 */

int gcd(unsigned int a, int b) {
  while (a != b) {
    if (a > b) {
      a -= b;
    } else {
      b -= a;
    }
  }

  return a;
}

unsigned int lcmOfSet(vector<int>& set) {
  if (set.size() == 0) throw logic_error("The set must have at least one element");

  unsigned int returnLCM = set[0];

  for (int i = 1; i < set.size(); ++i) {
    returnLCM = (returnLCM * set[i]) / (gcd(returnLCM, set[i]));
  }

  return returnLCM;
}

int gcdOfSet(vector<int>& set) {
  if (set.size() == 0) throw logic_error("The set must have at least one element");

  int returnGCD = set[0];

  for (int i = 1; i < set.size(); ++i) {
    returnGCD = gcd(returnGCD, set[i]);
  }

  return returnGCD;
}

int main() {
  int n, m;
  unsigned int setLCM, setGCD;
  cin >> n >> m;
  vector<int> a(n), b(m);

  for (int i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }

  for (int i = 0; i < b.size(); ++i) {
    cin >> b[i];
  }

  setLCM = lcmOfSet(a);
  setGCD = gcdOfSet(b);

  /**
   * This loop checks all multiples of the
   * LCM of the first set <= to the GCD of
   * the second set while keeping track of
   * the number of multiples that are factors
   * of the second
   */
  int i = 1, count = 0;
  while (setLCM*i <= setGCD) {
    if (setGCD % (setLCM*i) == 0) {
      count++;
    }

    i++;
  }

  cout << count << endl;

  return 0;
}

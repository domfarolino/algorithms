#include <iostream>

// Source: Berman's Advanced Algorithms I class, and more.

template <typename T>
T gcd(T a, T b) {
  // Assert: a <= b.

  T r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }

  return a;
}

template <typename T>
T extendedGCD(T a, T b) {
  // Assert: a <= b.

  T r0 = a,
    r1 = b,
    r2;
  T s0 = 1,
    s1 = 0,
    s2;
  T t0 = 0,
    t1 = 1,
    t2;

  // Need to check |r1| because that is the same as "b", which is the "previous"
  // remainder.
  while (r1) {
    // Inch-worm the values of |s|, |t|, |r| forward.
    s2 = s0 - s1*(r0 / r1);
    s0 = s1;
    s1 = s2;

    t2 = t0 - t1*(r0 / r1);
    t0 = t1;
    t1 = t2;

    r2 = r0 % r1;
    r0 = r1;
    r1 = r2;

  }

  // It might seem like the |s1|, |t1|, and |r1| values are the ones we care
  // about, since when the remainder |r2| is 0, we want to return "b" (aka
  // |r1|), but note that we just set |r0| to |r1|, and primed |r1| for the
  // next computation (same with the |s| and |t| variables).
  std::cout << a << "(" << s0 << ") + " << b << "(" << t0 << ") = " << r0 << std::endl;

  // "a", in the normal GCD algorithm.
  return r0;
}

int main() {
  extendedGCD<int>(36, 15);
  std::cout << "-------" << std::endl;
  extendedGCD<int>(26, 15);
  std::cout << "-------" << std::endl;
  extendedGCD<int>(15, 7);
  std::cout << "-------" << std::endl;
  extendedGCD<int>(24, 8);
  return 0;
}

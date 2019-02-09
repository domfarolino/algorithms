# Euclidean and Extended Euclidean Algorithms

Sources:

 - [Lecture 11: Number Theory ...](https://www.youtube.com/watch?v=fq6SXByItUI)
 - [This YouTube video](https://www.youtube.com/watch?v=6KmhCKxFWOs)
 - [The Wikipedia page](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)

The Euclidean algorithm, and its extension, are extremely useful algorithms
for finding the GCD of two numbers, and modular multiplicative inverces
respectively.

## Euclidean (GCD) Algorithm

The standard Euclidean algorithm for finding the GCD of two numbers is
particularly useful to cryptography, as when the GCD of two numbers `a` and `b`
is `1`, the two numbers are said to be co-prime (share no common factors other
than `1`). Furthermore, `b` is said to be a member of the group `Z/aZ`
(Z mod _a_ Z) (assuming a >= b). In other words `b` has a multiplicative inverse
modulo `a` (the next section focuses on finding that inverse).

The Euclidean algorithm can efficiently determine whether two numbers `a` and
`b` are co-prime. It is based on the following observation made by the ancient
Greeks: If a number `d` divides both `a` and `b`, it must divide `a - b`
(remember we're assuming that a >= b for simplicity). The Greeks calculated the
GCD of `a` and `b` by calculating the GCD of `a - b` and `b`, and so on. Euclid
made the observation that if `a - b` is still greater than `b`, we can replace
`a - b` with `a - 2b`, or `a - qb`, and so on, so `b` will overtake `a` sooner,
and the numbers we're working with will be smaller. Since `d` divides `a - bq`,
it must also divide `r`, where `a = bq + r`. This `r` is also known as the
remainder, or the result of `a mod b`. It is true that `r` will always be less
than `b`, and therefore Euclid's algorithm computes the GCD of `a` and `b` by
computing the GCD of `b` and `r`, and so on, until finally `r` is 0. At this
point, the GCD is `a`.

## Extended Euclidean Algorithm

Bézout's Identity states:

> Let a and b be integers with greatest common divisor d. Then, there exist
> integers x and y such that as + bt = d

The Euclidean algorithm can be extended to find the integers `s` and `t` that
satisfy the above equation. The values are particularly interesting when the GCD
is 1, i.e., when the numbers `a` and `b` are co-prime. The value `s` is the
modular multiplicative inverse of `a mod b`, i.e., `a*s = 1 mod b`, and same
can be said for `t`, with regards to `b`. The modular multiplicative inverse
is particularly useful for public key cryptography systems, like RSA.

The extended euclidean algorithm can be performed essentially by "reversing" the
standard Euclidean algorithm. Alternatively, it can be done iteratively by
inchworming initial values of `s` and `t` throughout the GCD computation, such
that they are the correct values that complement `a` and `b` from the beginning.
For more information, see the sources listed at the beginning of this article.

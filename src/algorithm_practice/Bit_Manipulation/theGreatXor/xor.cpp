#include <iostream>
#include <cmath>

// Source: https://www.hackerrank.com/contests/w28/challenges/the-great-xor/submissions

/**
 * Really haven't done anything with bit manip before. Barely knew the definition of
 * XOR but when I saw this problem I knew there'd be a simple pattern I could follow.
 * I whipped out my best friend - the JS console. The first thing I wanted to do is see
 * if this depended on how far away `a` and `x` were away to powers of two. The algorithm
 * for testing was a simple as picking some number, and seeing how many of the preceeding
 * numbers [0..number - 1] `a` when XORd with `x` was greater than x. I ran this algorithm
 * in a brute force way, for all numbers x from 0-15. I wanted to run up to 15 because some
 * very crappy preliminary tests I ran showed significance when `x` was one value below a power
 * of 2. So this encapsulated all numbers between multiple powers of 2 so I knew it would be
 * sufficient to see patterns with. I saw some kinda pattern that was a little odd but I could
 * still tell it depended on how far `x` was from the next largest power of 2, and then the number
 * of `a`s which meet our previous condition was then related to `x`. The final testing code I came
 * up with in the JS console was:

 for (var k = 15; k > 0; --k) {
  count = 0;
  for (var i = 0; i < k; ++i) {
    if ((i^k) > k) count++;
  }
 console.info(`${Math.pow(2, Math.ceil(Math.log2(k))) - k}: ${count}`);
 }

 * This kindly emitted values that showed me the maximum number of `a`s meeting our condition was
 * evenly distributed (run the code yourself and check it out, even mess with the console statement)
 * and prompted me to come up with the solution below.
 */

int main(){
  int q;
  std::cin >> q;
  long x, nearestLog;
  for (int i = 0; i < q; i++) {
    std::cin >> x;
    nearestLog = pow(2, ceil(log2(x)));

    (nearestLog - x == 0) ? std::cout << x - 1 : std::cout << (nearestLog - x - 1);
    std::cout << std::endl;
  }

  return 0;
}

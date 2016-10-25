#include <iostream>
#include <vector>

using namespace std;

// Source: https://www.hackerrank.com/challenges/jumping-on-the-clouds

/**
 * Jumping on the clouds
 * This problem is very simple but I thought it
 * was kind of cool. We need to realize that we obviously
 * start at the beginning of the array and we want to be greedy
 * in that we want to make the most ground with the least number
 * of steps as possible. The question is can we get in any trouble
 * by being greedy? In other words, is it possible that taking two
 * steps when both one and two-steps are available will lead to harm?.
 * The answer is no. If at all you take two steps instead one and run
 * into a dead end, it is not possible to have taken any combination of
 * one-steps in the and avoid the dead end. So we always want to take two
 * steps when we can. This can be proved through contradiction:
 * 0 0 0 1 1
 * Starting at the beginning we want to take two steps. We quickly realize we
 * are stuck and therefore can never reach the end. Since the problem statement
 * says there is always a solution to every given set this must mean we can get
 * to the end by making our first step a single step instead of a two-step. So we
 * try that and realize that any combination of single steps can never put us in a
 * position that can solve the problem,ss therefore we have a contradiction. Through
 * this contradiction we see that it is impossible to reach some position through some
 * combination of two steps that is impossible to reach with some combination of one-steps.
 * Of course it is possible to reach some position through some combination of one-steps that
 * is impossible to reach with two-steps. But does this help at all?
 * Consider the following:
 * 0 0 1 0
 * In this case our first step can only be a one-step because a two-step is not available. The next
 * step can only be a two step because a one-step is not available. This shows that a one-step is only
 * beneficial if a two-step simply is not available. So what if both are available?
 * 0 0 0 1 0
 * In this case our first step can either be a one or a two-step. It is obvious our last step will have to
 * be a two-step, however we can get to that point quicker by taking a two-step instead of a one, when both
 * are available. This shows that taking a two-step when both are available can never hurt us, but only speed
 * us up!. Since this is a pretty simple problem I'll stop writing now.
 */

int main() {
  int n;
  cin >> n;

  vector<int> v(n);

  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }

  int steps = 0, i = 0; // steps will be our printed result, i is the current index
  while (i < v.size()-1) { // don't count any steps after we hit the end
    if (i + 1 < v.size() && i + 2 < v.size()) {
      i += (v[i + 2]) ? 1 : 2; // take as much as we can if i+2 is in the array boundaries
    } else {
      i++; // settle for one-step only when necessary
    }
    steps++;
  }

  cout << steps << endl;
  return 0;
}

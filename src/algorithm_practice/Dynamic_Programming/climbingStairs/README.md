# Climbing Stairs

Sources:

 - https://leetcode.com/problems/climbing-stairs/description/
 - https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/

This is a fantastic problem, as it deals a bit with combinatorics but
in a nice efficient way such that we can build our solution up iteratively. You
are given _n_ stairs. You start from the bottom and have to end up at the top. While
going up the staircase you can either travel 1 or 2 stairs at a time. How many distinct
ways can you get to the top? This sounds overwhelming at first, because it should be pretty
obvious that there are a ton of distinct paths to get to the top of a staircase of a decent
size. Let's start breaking this down by looking at some examples.

## Examples

_n_ = 1. Consider 1 step. There is only 1 distinct way to get to the top, by simply stepping up
to it. For the purposes of this problem, we're assuming we start on some platform _lower_ than
the first step, requiring a single move to get to the first step.

_n_ = 2. There are two distinct way ways to get to the top of two steps.

 - Start => Step1 => Step2
 - Start => Step 2

Here we can see there are two distinct ways to reach step 2, or the top of a 2-step staircase.
Of course to arrive at a step, our final move will either be a single step or a double step, meaning
the answer for step(n), depends on step(n - 1) and step(n - 2). If we can arrive at step _n - 1_, we
know there is only one way we can make it to step _n_ (by taking a single step). If we can arrive at
step _n - 2_, there are two ways:

 - By taking a double step
 - By taking two single steps

We only need to worry about taking a double step, because taking two single steps means the last
step we'll be at before _n_ will be _n - 1_, which step(n - 1) should be responsible for covering.
Crucially, we don't want to double-count the same sequence twice. To be clear, the thing we care about
is how many ways we can:

 - Get to the _n - 1_th step, and take a single step arriving at our destination
 - Get to the _n - 2_nd step, and take a double step arriving at our destination

n = 3:

```
+-----+  +-----+  +-----+
|  1  |  |  2  |  |  3  |
+-----+  +-----+  +-----+
```

While it is true that the above numbers correspond to the "step number", the numbers are actually meant
to show the number of unique step combinations to reach each step in our staircase. The pattern we observed
in the previous example holds here as well. There is one step we can be at in order to arrive at step _3_ with
a double step, and a different step we can arrive at _3_ with a single step. Since we're only making one move
from each of these steps, we just care about adding those subsolutions. And again, while it is true that there
are two ways to arrive at a step _n_ from step _n - 2_, we want to make sure we're not duplicating our counts.

# Solution

Now that we've covered some examples, seen some patterns, and documented some thoughts, we can observe that this
solution follows the fibonacci sequence f(n) = f(n - 1) + f(n - 2), which is pretty cool, and lends itself to a
nice dynamic programming solution. As a problem of this type, and after going through some examples, we now have
some ideas as to how we can implement a solution.

## Top-down approach

Observing that step(n) = step(n - 1) + step(n - 2) until we hit the base case, we can implement a pretty naive
recursive solution that directly follows the recurrence relation above. This results in a tree-recursive algorithm
which is pretty wasteful. It duplicates a ton of work, because in order to calculate step(n - 1), we have to calculate
step(n - 2) and step(n - 3). Then in order to calculate step(n - 2), we duplicate all of this work again. This really makes
step(n) = 2\*step(n - 2) + step(n - 3). Given that multiple of 2, with some math we can see that the time complexity of the
solution is bounded by O(2<sup>n</sup>), which is exponential. O(2<sup>n</sup>) is not the tightest bound we could apply and
therefore doesn't tell the entire story, but it's the exponential trend that we're interested in. Regarding space complexity,
we have to be sure to count our stack frames, which will be equal to the height of the recursion tree when recursing.

### Complexity analysis

 - Time complexity: O(2<sup>n</sup>)
 - Space complexity: O(n)

Notice the massive amount of
[overlapping subproblems](https://www.geeksforgeeks.org/overlapping-subproblems-property-in-dynamic-programming-dp-1/) in our naive
solution. This duplicated work often provides a great opportunity to apply the dynamic programming technique "memoization", to save
and reuse previously-computed work, so that we only do each calculation once. To implement this we could keep some global hash map
data structure off to the side that stores {x: step(x)}. We'll populate this map on each calculation, and before we attempt to calculate
the answer to another subproblem _x_, we'll first consult our hash map to see if we've already done this work, and can lookup the answer
in O(1) time. This means we'll do O(n) calculations once, and reuse everything else. Verify this by drawing a tree corresponding to the
recursive calls, to see that we'll only be doing O(n) real calculations and recursive calls. This greatly reduces our time complexity,
at the cost of extra space, however the amount of space will be asymptotically equivalent to the amount of space we used in the previous
solution (the stack frames)!

### Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(n)

## Bottom-up approach

A lot of dynamic programming problems can be solved with a top-down or a bottom-up approach. In the last section we looked at the top-down
solution which we were able to optimize using memoization. We can also build up a table of pre-computed answers that other calculations
depend on from the bottom-up. For example, we know the base case, and even the first few numbers, so if we were to have an array of subproblem
answers, it might start like this: [1, 2]. Then to add the solution to step(3) to the array, that step (4+) will depend on, we can simply add
the result of the last two values, giving: [1, 2, 3]. We can keep iteratively doing this, ultimately ending up with the array:
[1, 2, 3, 5, 7, ..., step(n - 1), step(n)], at which point we can finally return the last value in the array.

This is linear in time and space, given the storage requirement of the array. We can optimize the space further however, by making the
realization that whenever we're computing step(n), we _only_ need the values of step(n - 1) and step(n - 2), the last two values in the
array, and nothing else. In fact, from this point forward we'll never touch the earlier values in the array ever again, and on future
iterations, likewise we'll never touch the current values we care about. While these earlier values were helpful to get us where we need,
it would be great if we could just hold onto the last two values, and wipe all earlier values out. For this to happen, we'd need variables
to store step(n - 1), step(n - 2), and step(n), and we'll have to snake these values along as we go. With a temporary variable, this could
work quite well, and brings us down to O(1) space, which is fantastic! Looking at this a little further, we can really get away with only
two variables + a temporary one, but that's a minor optimization.

### Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(1)

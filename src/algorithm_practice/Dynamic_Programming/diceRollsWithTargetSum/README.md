# Number of Dice Rolls With Target Sum

Source:

 - https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description/

The problem description is as follows:

> You have d dice, and each die has f faces numbered 1, 2, ..., f.
> Return the number of possible ways (out of f<sup>d</sup> total ways)
> modulo 10^9 + 7 to roll the dice so the sum of the face up numbers equals
> target.

# Top-down DFS + dynamic programming

This is a really interesting problem IMO, and I like how it generalizes, with
dice with an arbitrary number of faces. I went about approaching this as a
tree-recursive backtracking problem, where we break a problem into many subproblems
that we try and solve. Naturally this lends itself to the top-down dynamic programming
technique "memoization", to avoid solving the same subproblems multiple times.

I looked at the problem like this: I break the problem of determining how many rolls are
possible with `d` dice to roll target `t` by focusing on one die, which when rolled, can
take on any value in the range `[1, min(f, t)]`. This is because we need not consider
face values greater than `t`, because we'll never be able to roll `t` with them. We'll
simulate rolling each of `n in [1, min(f, t)]` values for one die, and recurse to the
subproblem of rolling `target - n` with the remaining `d - 1` dice. We can continue breaking
the problem into subproblems in a DFS-manner until we get to the trivial case where `d = 1`.
This gives us a tree like so:

![tree](tree.png)

When we get to the base case `d = 1`, we know whether or not we can roll this stack
frame's `target` with a single die, and can return `1` or `0`. As we unwind our
recursion upwards, we should save our results in a map `{<d, target>: possibilities}`.
For each node in the tree, we'll sum together the results of the subproblems, save this
result in the map, and return it. We'll also consult this map before we recurse to check
for our previous work; it is the "memo" in memoization.

Clearly the total tree can be quite large, since we have a branching factor of `f` and
a depth of `d` nodes and `d - 1` edges. The overall size of this tree will be
_O(f<sup>d</sup>)_ but our memoization prevents us from traversing the entirety of it.

## Complexity analysis

 - Time complexity: As mentioned, the tree size and full traversal would be _O(f<sup>d</sup>)_,
   but with memoization, we don't have to pay that full price. Instead, we compute and store
   at most _O(d\*t)_ entries, and for each subproblem (node in the tree), we sum together
   _O(min(f, t))_ subproblem sums. This gives us a complexity of _O(d\*min(f, t)\*t)_. You could be
   less descriptive by realizing _f = O(t)_, yeilding a complexity of _O(d\*t<sup>2</sup>)_.
 - Space complexity: Without memoization, the space would be implicit with recursive stack frames
   being _O(d)_ deep. With memoization, the map can store _O(d\*t)_ entries.

# Bottom-up dynamic programming

TODO(domfarolino): This problem also has an elegant bottom-up dynamic programming solution that
can be derived from the top-down one above. I should implement and describe it here.

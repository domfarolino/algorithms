# Minimum Loss

Source:
 - https://www.hackerrank.com/challenges/minimum-loss/problem

The reason I like this problem is because it requires you know how to a tricky
maneuver with an interesting data structure. The approach I had for this problem
was that we could maintain, in an abstract sense, a "sorted array" that we can
incrementally add each house value to as we go along. What we're interested in is
the next-largest house value after adding a given one to the array. Now in practice,
maintaining a real array is expensive, because inserts are O(n), but we can simulate
one with a binary search tree, which is what std::set is backed by. As long as the tree
is balanced, we can guarantee O(log(n)) inserts. Now to find the next-largest value (should
one exist), we can simply take the iterator that points to the newly-inserted element, and
increment it. This is equivalent to finding the in-order successor in the binary search tree,
if one exists.

The iterator increment is also O(log(n)), which allows us to keep an O(n\*log(n)) budget for the
entire algorithm.

## Complexity analysis
 - Time complexity: O(n\*log(n))
 - Space complexity: O(n)

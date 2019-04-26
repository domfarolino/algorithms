# Initial to Target (ABBA)

Source:
 - [Topcoder](https://arena.topcoder.com/#/u/practiceCode/16527/48825/13918/2/326683)

This is a pretty interesting problem; the input is two strings, `initial` and `target`
consisting of only 'A's and 'B's. The goal is to return whether or not you can create
the `target` string from `initial`, by only performing one of two operations on the
`initial` string at any given time:

 1. You can add an 'A' to the end of the string
 2. You can reverse the string and add 'B' to the end of it

### Examples

In: "A", "AB"

Out: true; by rule (2) you can reverse the string, producing "A", and add "B" to the end

----

In: "AB", "BABA"

Out: true; by rule (2) you can produce "BAB", and by rule (1) you can produce "BABA"

----

## Naive Search Approach

The naive approach to this solution (not implemented here) is to basically from the
`initial` string, generate all possible strings as long as `target`, and check to see
if any of them equal target. This is of course very expensive, but we can do so in a
BFS fashion. First, consider the binary tree that can be made from `initial`:

In: "AB", "BABA"

![ab-tree](./ab-tree.jpeg)

With this, a natural jump would be to treat strings as nodes, and perform a
breadth-first-search starting from `initial`. We'd stop evolving a given string
in the BFS queue when its length equals that of `target`. At this point, we'd
check to see if the string equals `target`. If it does, we're set. If not, we
discard it and move to the next. If we've exhausted all of the strings without
finding one equal to `target`, we know we can return false or something indicating
that `init` cannot be evolved into `target`.

This is a really simple and naive algorithm, ignoring a lot of potential places of
optimization.

## Complexity analysis

Since we're constructing a perfect binary tree, we know that the complexity of this
algorithm is going to be bounded by the number of nodes in the tree. The number of
levels in the tree is directly proportional to length difference of `target` and
`initial`, which we'll call `k` (that is, `k = target.size() - init.size()`.
Specifically, there are `k` levels in the tree we can produce, which means:

 - The number of leaf nodes will be 2^k; [proof](https://blog.domfarolino.com/Binary-Tree-Inductive-Proofs/#perfect-binary-tree-proof-3)
 - The number of nodes in the tree wil be 2^(k + 1) - 1; [proof](https://blog.domfarolino.com/Binary-Tree-Inductive-Proofs/#perfect-binary-tree-proof-2)

The number of leaf nodes is the amount of strings that we'll have to store in our
BFS queue at any given time, which is a clue to our space complexity (we'll have to
multiply this number by the string length), however the total number of nodes in the
tree is what we'll have to iterate through to produce the leaves we're interested in.
Therefore:

 - Time complexity: O(2^(k + 1))
 - Space complexity: O(m\*2^k); where `m = target.size()`

## Work-backwards Optimization

## Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(1)

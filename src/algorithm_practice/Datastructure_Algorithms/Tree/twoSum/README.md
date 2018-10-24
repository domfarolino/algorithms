# Two Sum BST

 - Source: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/

Interesting problem!

Consider the following tree:

```
    5
  /   \
 4     6
```

The following twoSum queries should return true:

 - twoSum(tree, 9)
 - twoSum(tree, 10)
 - twoSum(tree, 11)

...and anything else will return false. We can make the assumption that the input
binary search tree does not contain duplicate values, but may not be balanced as well.
It essentially gets broken down into the following fundamental problems:

1. Traversing through an entire binary (search) tree in a DFS fashion: O(n)
1. Finding a node with a given value in a binary search tree: O(log(n)) time if tree is balanced, O(n) otherwise

These are not difficult problems, so the key to this solution is just tying them together
correctly. We also have to be careful about duplicates. The above query returns true for the sum
10, only because the nodes 4 + 6 exist; in other words, we have to be careful to not count the same
node (5) twice. The idea for this problem is:

 - For each node in the binary search tree:
   - Search the entire tree (not just the tree starting at the current node) for the node's complement value (`target - currNodeValue`)
   - If we find the complement node, and it is not the current node we're looking at (so we don't consider the same node twice\*), return true
   - Otherwise, recurse on the current node's left and right trees, returning true if at least one of the subproblems returned true.

\* Alternatively, we could check the complement value that we're looking for, and if it is equal to the current node's value, don't even search
for it, since we'd only find the same node twice.

This seems to handle everything quite nicely. Of course the outer function we'll be dealing with will be recursive, and since we'll be calling
the `find()` algorithm at each node, we'll need to maintain an everlasting reference to the actual root of the tree throughout each stack frame
in addition to the normal "currentRoot" reference.

# Complexity analysis:

 - Time complexity: O(n<sup>2</sup>) (could be O(nlog(n)) if tree was guaranteed to be balanced)
 - Space complexity: O(n)

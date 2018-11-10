# Column-wise Row-wise

Source:

 - https://careercup.com/question?id=5709428993556480

The goal of this problem is to take in a binary tree (not search) and print
out all the nodes of the tree in order of appearance from left to right and
top to bottom. Consider the following tree:

```
      6
    /   \
   9     4
  / \     \
 5   1    3
  \      /
   0    7
```

We'd want to print the nodes out in the following order: `5 9 0 6 1 4 7 3`. Clearly
we care about the column number that each node is in. We want to print each column out
in increasing row order. My thoughts were that we want to bucket the nodes by column
number, and add nodes to each bucket in row order. Since we don't know the width of the
tree, we'll start with the root node as the centerline and consider this as column 0. Every
time we traverse left or right we'll decrease or increase this column number as necessary so
we know which bucket to throw our node in. As long as we throw our node in the right bucket before
recursing, we'll get both the column- and row- ordering that we want. This makes for a nice
**DFS preorder algorithm**. Then for each node, we'll push it to the end of the node list for
that column, and recurse on said node's left and right subtrees respectively.

We can use an unordered map to act as the implementation of our hash map, to store
`{bucket/columnNo: list<node>}`. However since we want to print the contents of each
column in column order, we'll want our keys to be sorted, so we can use a regular ordered
map.

 1. Inserting a new node to an existing column will be O(log(n)) (actually I'm surprised this isn't
    O(1), aka surprised the implementation does not keep a separate hashed unordered list of the keys
    for O(1) lookup of _existing_ keys).
 2. Inserting a new node to a new column will also be O(log(n)), and we'll be doing this O(n) times.

# Complexity analysis

 - Time complexity: O(nlog(n))
 - Space complexity: O(n)

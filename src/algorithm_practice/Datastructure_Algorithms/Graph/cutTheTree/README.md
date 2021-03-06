# Cut the Tree

Source:
 - https://www.hackerrank.com/challenges/cut-the-tree/problem

This is a pretty straightforward tree problem; it is mostly an implementation challenge, which
still isn't too difficult. We are given a list of nodes and edges for a graph that is guaranteed
to make an undirected tree. A lot of times when we think "tree" we think Directed Acylclic Graph
(DAG) but a [tree's edges can also be undirected](https://en.wikipedia.org/wiki/Tree_(graph_theory)),
meaning from an implementation standpoint, we must make sure we have some "visited" mechanism to
ensure we don't fall into a cycle while traversing the tree.

Ultimately, we can represent our tree as a graph in whatever way we want. From here, we'd like to
examine each edge and determine the best to cut, given the problem constraint. We can examine each
edge by traversing the entire tree, and considering the subtree rooted at a given node. For each
node, we'll want two things:

 - The sum of the subtree rooted at the current node (_`a`_)
 - The sum of the entire tree (_`b`_)

Then we can simply compute the difference between the two trees (`a - b`, and `b`). We'll compute the
absolute value of `(a - b) - b` for each node and take the minimum of all computations. When we visit
each node though, computing `a` and `b` from scratch each time lends itself to a trivial O(n<sup>2</sup>)
solution. We can compute `a` upfront, eliminating that O(n) cost right away, but computing `b` each time
is still O(n) itself, and keeps our overall complexity O(n<sup>2</sup>).

We can actually preprocess the entire tree upfront too, computing each subtree sum in a DFS-manner for a
one-time O(n) cost. We can store that information in each tree node (even overwriting the node's original
value if we want), so that we have `a` and `b` pre-computed for us at every node. Now, we simply perform a
single DFS traversal of the tree, and for each node do our O(1) math operations, and return the minimum value.

## Complexity analysis
Let "n" be the number of nodes in our tree/graph.

 - Time complexity: O(n)
   - Typically when we implement a graph (or in this case, a graph that happens to be a tree), both the
     number of nodes and edges play a roll into how many operations our algorithm will complete. Since our
     graph is a tree, we know the number of edges is bounded by the number of nodes, so a traversal on _n_
     nodes is O(n).
 - Space complexity: O(n); for the reasons listed above

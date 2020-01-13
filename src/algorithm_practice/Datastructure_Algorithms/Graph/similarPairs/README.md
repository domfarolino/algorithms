# Similar Pairs

Like the problem [cutTheTree/](../cutTheTree), our tree is given to us as an undirected graph,
which is guaranteed to for a tree. An optimal solution to this problem is pretty tricky, however
we can easily conceive of a naive one. For all nodes, we can perform a pairwise comparison between
a given node and all of its descendants. A full pairwise comparison will take O(n) time, since we're
bounded by the number of nodes and edges in our graph, which are both O(n). Doing this O(n) times of
course gives us a naive quadratic solution.

Thinking deeper at the problem in hopes of finding an optimization, let's take a look at some possible
room for improvement. The source of inefficiency in our naive solution comes from traversing almost the
entire tree, for every single node. This is a common thing though; if were to compute each node's subtree
sum, we can do so in a similar quadratic manner, or we can compute our result and recurse, re-using
previously-computed results as our recursion unwinds. It would be great if we could implement the same type
of optimization here. That is, for a given node, recurse on its children, solving the same problem, and reuse
that result for its parent, instead of have to re-traverse everything. Assuming node _x_ were a parent of
node _y_, that would require us being able to determine how many nodes under _x_ are "similar" to it, based on
how many nodes under _y_ are similar to _it_.

## Complexity analysis
 - Time complexity: O(1)
 - Space complexity: O(1)

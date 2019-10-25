# Topological Sort

Topological sort is a classic concept and graph algorithm that any computer
scientist should be familiar with. A dependency graph can be used to represent
dependency relationships of things such as tasks, prerequisites, etc. Generally
if an item "A" depends on "B", there we be a directed edge in the graph from "A"
to "B". This models the fact that in order to "resolve" or "complete" "B", "A"
must be done first.

A common problem to solve in computer science is:

> Given a dependency graph representing say, tasks that depend on each other,
determine a linear ordering in which the tasks can be completed.

If the input graph is a DAG (directed acyclic graph), then there will be an answer
(a topological ordering is possible to produce). As soon as the input graph has a cycle
however, no topological ordering exists. This is because given a cycle of tasks in our
input graph, there is no task within that cycle that can be completed before the others
in the same cycle; therefore we cannot actually resolve a topological ordering.

## Algorithm

Topological sorting (and implicitly, the detection of a cyclic graph) can be done in
a very simple DFS manner. We do a DFT (depth-first-traversal), which is a DFS from every
node in the graph. From each node, we access our implementation of the graph (typically
an adjacency list or matrix) to find the current node's dependencies (neighbors). We mark
the current node as "temporarily visited", then recurse on all of the node's dependencies.

While recursing, if we ever recurse back to a node that is already marked "temporarily visited",
we've found a cycle in the graph and can immediately stop. Otherwise, once we're finished
recursing, we know that we've visited all of the given node's transitive dependencies in the
correct order, and it is now finally time to "visit" our given node, marking it
"permanently visited" and adding it to the end of some final return array.

Note that because we "permanently" visit a node after we recurse on all of its dependencies,
it is the last node we "visit" out of all of its (transitive) dependencies, which is the
intention. Furthermore, no matter what node we start a topological sort on, the first node
to appear in the final linear ordering of nodes will be one that has no dependencies. Such a
node is often called a "sink" node, and is guaranteed to exist in a non-empty DAG.

## Complexity analysis

 - Time complexity: _O(V + E)_; where _V_ is the number of vertices/nodes in the graph,
   and _E_ is the number of edges
 - Space complexity: _O(V)_; this is because the maximum recursion depth could be _O(V)_
   nodes deep, and we also maintain a visited set and return list, both holding _O(V)_
   nodes

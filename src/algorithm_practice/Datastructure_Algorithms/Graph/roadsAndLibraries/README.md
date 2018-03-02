Source: https://www.hackerrank.com/challenges/torque-and-development/

TODO(domfarolino): revise this post.

This is a pretty interesting graph problem. It vexed me for a bit until I made some cruicial realizations.

# Divide the problem into connected components

When starting with this problem I fumbled around quite a bit. Eventually I came to some good realizations:

 - We'll need at least one library per connected component
 - In each component, there are two extremes:
   - Every city in a connected component has a library
   - Only one city in a connected component has a library

My next thought was that the naive solution would be to find all possible combinations of library/road
allocations in between the extremes, which seems combinatorially explosive. For example, what if there
were not the extreme `n` libraries and `0` roads in a component, but instead `n - 1` libraries and `1`
road, or `n - 2` libraries and `2` roads. How many different ways can we
[*choose*](https://en.wikipedia.org/wiki/Binomial_coefficient) how to allocate which cities have libraries
and which cities to connect, and more importantly, does the choosing of these actually affect the cost?
Determining the number of possible choices we can make when allocating libraries to cities is actually pretty
easy (it's just the summation of binomial coefficients, [see here](https://math.stackexchange.com/questions/519832/)),
it would just be combinatorially explosive to go through each one; was it necessary?

When looking at an example graph with five (once-) connected cities I realized that the allocation of libraries
doesn't matter at all and won't affect the cost. (I was considering the idea that perhaps the degree of each city
might have an affect on, or indicate priority of library assignment). The allocation makes no difference as long
as we don't waste a road connecting two library-bearing cities, because why would we do that?

[Enter a tangent]...

The whole reason this accidentally-connecting-two-library-bearing-cities issue came up is because I was examining a
quite feasible 5-city graph with a cycle trying to allocate `3` libraries and `2` roads. I wondered if I could choose
a "bad" allocation of libraries and roads, namely one that doesn't actually connect each city in the component. This is
certainly possible in a graph with cycles when only dealing with `numberOfCities` resources (`3` libraries and `2` roads).

I was then worried about making sure my implementation would not accidentally theoretically waste a road on two
library-bearing cities, and then I realized well yeah, if the allocation doesn't matter, we just have to know that
some working allocation exists, and that will be the minimum total cost for such choices of the number of libraries
and roads for that connected component.

# A connected component is at least a tree

The "choice" of which roads to build dissolves when you realize that the connected component by definition is at least a
tree, and thus always has valid allocations of libraries and roads in the form of:

`N - K` libraries + `K` roads, `∀ K < N` (remember, we need at least one library).

This means each connected component had `N` possible solutions, and for each of the values of `K`, we needed to choose the
minumum one. Going through some examples I realized the best answer always seemed to be one of the extreme allocations, namely
an allocation with all `N` libraries or only `1` library. I tried to find an example where one of the middleground less
extreme allocations could be more optimal, but I came to the conclusion that that will never be the case, because we greedily
want to choose to employ as many of the cheapest resource (either libraries or roads) as possible. In other words, if roads were
cheaper to build then libraries, and there exist the possible roads to repair to connect the entire component (the definition!),
then we'd want to only build `1` library, and as many remaining roads as we'd need. We could build two libraries, and one less
road, but that would give us the same connected result but with a higher cost, unnecessarily.

# Implementation design

When thinking about the implementation, I knew the number of connected components was relevant to this problem. I also knew
we could get an entire connected component (but more importantly its size) using a trivial-to-implement BFS algorithm. I figured
I'd use an adjecency list to store the graph, since I wasn't going to perform any operations that a matrix would be more suited
for. The necessary steps were something like this:

 - Build the graph's adjacency list
 - For each connected component
   - Get the size of the component
   - Minimal cost of connecting this component was `min(a, b)` where:
     - `a = numCities * costLib`
     - `b = costLib + (numCities - 1) * costRoad`
   - With the minimal cost of the component in hand, add the value to the running some, and perform the same operation for the next component.

Moving from component-to-component is as easy as just using BFS with some sort of global visitation store.
We can try to find a connected component from each given city. The first time we run BFS, we'll mark *all* nodes in
the discovered component as visited. Then in the next given city, we'll try to find another connected component *if*
the city has not already been visited (does not exist as a part of an already-discovered connected component). We keep
a running sum, adding to it the minimum cost required to connect a once-connected component, and eventually return the
final value.

Time complexity: O(n) (by marking nodes as visited, we're repeating ourselves)
Space complexity: O(n)

*It should be noted that the complexity of this algorithm could easily by O(n^2) (due to edge processing in the complete
graph of K~n~), however the problem description on Hackerrank specifically limits the number of edges to `n`*

# Roads and Libraries

Source: https://www.hackerrank.com/challenges/torque-and-development/

This is a pretty interesting graph problem. It vexed me for a bit until I made some cruicial realizations.

# Divide the problem into connected components

When starting with this problem I fumbled around quite a bit, but eventually I came to some realizations revolving
around focusing on each connected component in the given graph:

 - We'll need at least one library per connected component in the graph
 - In each connected component, there are two extremes:
   - Every city in a connected component has a library
   - Only one city in a connected component has a library

My next thought was that the naïve solution would be to find all possible combinations of allocated libraries
and built roads between the aforementioned extremes, which seems combinatorially explosive. For example, what
if there were not the extreme `n` libraries and `0` roads in a component, but instead `n - 1` libraries and `1`
road, or maybe `n - 2` libraries and `2` roads. It is obvious to determine how many different ways we can
[*choose*](https://en.wikipedia.org/wiki/Binomial_coefficient) to allocate `n - k` libraries amongst `n` cities
in a component. But how many different ways can we decide what roads to build given a particular allocation? Do
the different choices of which roads to build for some given library allocation actually affect the cost?

When looking at an example graph with five (once-) connected cities, I realized that the allocation of libraries
doesn't matter at all and won't affect the cost. (I had considered the idea that perhaps the degree of each city
might have an affect on, or indicate priority of library assignment). Which cities we choose to build libraries
in is irrelevant as long as we don't waste a road connecting two library-bearing cities when we could use it to
connect a non-library-bearing city to a library-bearing one.

> Warning, entering a tangent:

![entering a tagent](https://apps.azdot.gov/files/traffic/moas/thumbgif/w/w01-010.gif)

The whole reason this accidentally-connecting-two-library-bearing-cities issue came up is because I was examining a
quite feasible 5-city graph with a cycle, trying to allocate `3` libraries and `2` roads. I wondered what would happen
if I chose to waste the building of a road on connecting two cities that both bore libraries, instead of building a road
from a city that was not connected to a library to a city in the same component that was. This "bad allocation" can happen
because of this cycle (effectively wasting a road on a group of cities that don't need another built).

I was wondering how I could ensure my implementation would not accidentally do this, but then I realized it wouldn't be
necessary. *Some* proper allocation of built roads exists, and as long as I know it exists, I don't have to worry about
accidentally choosing a "bad allocation", because I'll be using the same number of roads either way! And I know that by
using that number of roads, it *is* possible to connect all cities, therefore the exact layout is meaningless.

# A connected component is at least a tree

The reason there is definitely *a* working allocation of roads to build is true is because we can ignore cycles that would
otherwise form a "bad allocation", because the connected component contains *at least* the roads necessary to connect all
cities without roads that form cycles. In other words, the connected component is at least a tree, so mathematically *some*
non-wasteful layout of roads exists.

A group of connectable cities can therefore have all of its cities connected to libraries in `N` different ways, where `N`
is the number of cities in the group:

`N - K` libraries + `K` roads, `∀ K < N` (remember, we need at least one library).

This means each connected component has `N` possible solutions, and for each of the values of `K` (ranging from `0` to `N - 1`),
we need to choose the most cost-efficient one. Going through some examples I realized the best answer always seemed to be one of
the extremes, namely a layout containing all `N` libraries and `0` roads, or only `1` library and `N - 1` roads. Trying to find
an example in which one of the middleground distributions was more optimal, I eventually came to the conclusino that this will never
be the case, because we greedily want to choose to employ as many of the cheapest resource (libraries or roads) as possible!

In other words, if roads were cheaper to build then libraries, and there exist the possible roads to repair to connect the entire
component (the definition!), then we'd want to only build `1` library and as many remaining roads as we'd need. We could build two
libraries, and one less road, but that would give us the same connected result but with a higher cost, unnecessarily.

# Implementation design

When thinking about the implementation, I knew the number of connected components was relevant to this problem. I also knew
we could get an entire connected component (but more importantly, its size) using good ole BFS (DFS suffices too). I figured
I'd use an adjecency list to store the graph, since I wasn't going to perform any operations that a matrix would be more suited
for. The necessary steps were something like this:

 - Build the graph's adjacency list
 - For each connected component:
   - Get the size of the component
   - Compute the minimal cost of connecting this component (rebuilding existing roads), which is `min(a, b)` where:
     - `a = componentSize * costLib`
     - `b = costLib + (componentSize - 1) * costRoad`
   - With the minimal cost of the component in hand, add the value to a running sum, and perform the same operation for the next component.

Moving from component-to-component is as easy as just using BFS with some sort of global visitation data structure.
We can try to find a connected component from each given city. The first time we run BFS, we'll mark *all* nodes in
the discovered component as visited. Then in the next given city, we'll try to find another connected component *if*
the city has not already been visited (does not exist as a part of an already-discovered connected component). Eventually
we'll return the value of a running sum we've kept (as mentioned above).

Time complexity: O(n)
Space complexity: O(n)

*It should be noted that the complexity of this algorithm could easily by O(n^2) (due to edge processing in the complete
graph of K~n~), however the problem description on Hackerrank specifically limits the number of edges to `n`*

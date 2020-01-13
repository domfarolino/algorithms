# Count Luck

Source:
 - https://www.hackerrank.com/challenges/count-luck/problem

I enjoy grid-based graph problems, which is essentially what this is. There is only one unique path
from M => \* which is nice, and in that case, makes me lean towards a BFS approach. In general, I
prefer BFS for grid-based graph problems; I think it is easier to reason about the set of visited nodes,
the ways to extend our paths from a given node, and to not recursively bottom-out.

Basically for this problem, we're just interested in knowing how many "decisions" the wand had to make
in the face of ambiguity. That is, on the path that finally ended up at the finishing node, how many forks
were there on the way. When doing grid-based graph problems with BFS, I generally maintain a queue of
`std::pair<int, int>`s or some equivalent, which represents a location in the grid, as well as a visited
matrix. In this case, whenever we push moves to our queue, that move extends an established path, and each
path should have its "fork count" or "number of decisions made". Therefore, for this algorithm I opted to
maintain a queue of `Location`s, which was a custom abstraction over a grid point, which contains the number
of decisions made so far on a given path (without keeping track of the path itself).

Whenever we analyze a move/location it has `d` decisions made so far on the path ending in that move. If we
determine that from said location, we will push more than one location to our queue (i.e., there is ambiguity),
we must mark these these locations having `d + 1` moves, indicating a decision has been made. Therefore the move
that finally finds our finishing spot in the grid has kept track of the number of decisions made so far, and we can
compare it to the given `k` that "Ron" guesses to see if his guess is right.

## Complexity analysis
 - Time complexity: O(n\*m)
 - Space complexity: O(\*m); for the visited set

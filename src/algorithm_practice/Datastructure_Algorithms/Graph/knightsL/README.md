# KnightL on a Chessboard

Source:
 - https://www.hackerrank.com/challenges/knightl-on-chessboard

This is an interesting search problem! It essentially requires us generalizing a
"knight" in Chess (and generalizing the board as well), and determining if it is
possible for a knight to make it to a given square on a grid. Not only do we have
to determine if the knight _can_ make it though, but we also have to determine in
the minimum number of moves. We're searching over a grid, so this implies BFS, and
since we need to know the "hop length" from start to end position, we can use a
classic modification of BFS that lets us keep track of how many levels we've expanded
our search at any given time.

This modification requires us to keep track of how many nodes are at a given level in
the search tree, so that we can expand to the next level all at once, and increment a
level counter. Once we have that in place, we add logic in our BFS loop to correctly
generate 8 new search nodes from a given node, and continue searching like usual. We
either eventually exhaust the queue, in which case the knight cannot make it to the
desired spot, or we find that the knight can make it to the desired spot, and immediately
return the level count at the time.

## Complexity analysis
 - Time complexity: O((n - 1)<sup>4</sup>), or O(1)
   - My logic is that each of the O((n - 1)<sup>2</sup>) searches takes
     O((n - 1)<sup>2</sup>) time, we simply multiply the two. Since Hackerrank gives a
     constant upper bound on `n`, we could also argue O(1) though
 - Space complexity: O((n - 1)<sup>2</sup>), or O(1);
   - Our "visited" and output grids are both this size, but per the reasoning above,
     we could also argue O(1)

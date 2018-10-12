# Surrounded Regions

This is a cool problem! The key question here is "What makes an entry in the grid one
that needs changed to an 'X'"?. An entry in the grid needs changed to an 'X' not only
if it is entirely surrounded by 'X's, but if the transitive closure of neighboring 'O's
(fancy way for saying "all Os that are reachable from a given O") are collectively surrounded
by 'X's.

My first attempt at this was to basically go through every single entry in the grid, and if it
was an 'O', run a DFS collecting all 'O' nodes that touch the initial 'O'. The DFS should not only
populate a "visited" set with all of these nodes, but should return true or false indicating whether
the enture group of nodes ever hit a border. If they never did, we would take all of the nodes we visited
during that walk, and turn them all into 'X's on the board. If they did ever touch a border, we don't want
to do anything with them, but we should still make sure they appear in some global visited set, so that we
don't run into them again. This complicates things, because we'd need two sets:

  1. One global visited set, that consists of every node we've ever visited
  2. A temporary visited set, used to store the nodes we visited from a single
     DFS. We need this in case the DFS indicates to the caller that the nodes never
     touched a border, and we can change _just these_ nodes to 'X's.

This worked, but was a little unnecessarily complex, implementation-wise. After reading up some in the discussion
board for this problem as well as talking to someone that had solved the problem, it turns out a more optimal solution
can be found by looking at the problem the other way. Instead of trying to find all groups of nodes internally whose transitive
neighbors don't touch a border, it would be easier to iterate through all of the border rows and columns, finding outside-'O's,
and running a DFS from them, maintaining a single global set of visited "don't change these!" nodes. This is a lot cleaner.
Both solutions have the same time and space complexity.

Anyways, this solution is a lot cleaner IMO, and can be come to by continuing to ask "What conditions must be met for us to
change a node's value?". And we've come full circle!

# Complexity analysis

 - Time complexity: O(n\*m), where n = # rows, m = # cols
 - Space complexity: O(n\*m)

In the worst case, with a grid entirely composed of 'O's, the DFS we run from the first border 'O' will consume all nodes in
the entire graph. This gives us a time and space complexity linear to the number of nodes in the entire grid, aka O(n\*m).

# Follow-up thoughts

I believe another solution exists, where we can iterate through each outer row and outer column, turning all 'O's into some
sentinal mark, such as 'T'. Then for each inner row we'd look at the neighboring outer row, and if in the same column position,
there was a 'T', we'd change the node at the current position we were looking at to 'T', and spread that 'T' to all of our adjacent
'O's in the same row. We'd need to do this coming from the top row and bottom row, as well as the columns. For example, given the following
matrix:

```
X X X O X X X
X X O O O X X
X X O O X X X
X X X X O O X
X X X X O X X
```

...we'd first look at the outer rows and columns, changing 'O's to 'T's:

```
X X X T X X X < top
X X O O O X X
X X O O X O X
X X X X O O X
X X X X T X X < bottom
```

...then we'd look inward a single row from the top and bottom, and for each value in that row,
we'll see if the value at the neighboring row in the same column is a 'T'. If it is, we'll want
to change the value we're looking at to 'T', as well as all neighbors in the same row:

```
X X X T X X X
X X T T T X X < top
X X O O X O X
X X X X T T X < bottom
X X X X T X X
```

...we'll then keep going until `top` and `bottom` are at the opposite ends they started. We'll repeat the
process for the outer columns too. When all is finished, we know that every remaining 'O' in the board never
had a neighbor 'O' that touched a border, and thus should be changed to an 'X'. Every 'T' in the board was in
the exact opposite boat, and should then be left as an 'O'.

This solution gives us O(1) space complexity, which is an improvement, however is much more arduous and complicated
to implement.

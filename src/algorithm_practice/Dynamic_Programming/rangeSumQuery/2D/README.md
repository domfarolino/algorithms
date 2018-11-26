# Range Sum Query 2D - Immutable

Source:

 - https://leetcode.com/problems/range-sum-query-2d-immutable/description/

This problem is an interesting modification of the more standard linear range
sum query algorithm in the parent directory. Find the sum of some submatrix
given some "master" matrix that we'll be querying. The queries will consist of
the row and column number of the top-left-most point of the submatrix, as well
as the row and column number of the bottom-right-most point of the submatrix. You
can assume that the given coordinates associated with all queries are in-bounds.
It is important to look for efficient solutions, as we may be performing a lot of
queries on our matrix.

There are several ways to do this, each varying in efficiency and implementation complexity.

# Naive

The naive solution is pretty trivial, and basically just consists of visiting all
elements within the range of the submatrix, and keeping some "global" sum that
eventually gets returned.

## Complexity analysis

 - Time complexity: O(n<sup>2</sup>)
 - Space complexity: O(1)

# Extending linear range sum query

It is probably obvious that any solution faster than the naive solution will
employ some amount of preprocessing/dynamic programming. One solution that trivially
extends the linear range sum query problem is to simply and literally extend the single
dimension solution to each row of the matrix in this problem. We can actually do this in-place,
transforming the input matrix into one such that each element in each row is the sum of all elements
in the row up to that point. In short the following input matrix:

```
1 2 3 4
4 4 0 0
5 2 5 7
3 6 7 3
```

...would become:

```
1 3 6 10
4 8 8 8
5 7 12 19
3 9 16 19
```

From here, given the variables (row1, col1) and (row2, col2) representing the query, we can maintain
two variables `verticalSums` and `verticalSubtractions`, where `verticalSums` would be equal to the
sum of all values `matrix[r][col2]`, for all r in between and including row1 and row2. If col1, the
left-most column in the query, is > 0, we'll do something similar to compute `verticalSubtractions`,
however instead of using col2 as the column for our summation to query each row's sum, we'll use
col1 - 1, to subtract the elements we never "meant" to include in our first O(row2 - row1) pass.
Note we're essentially just performing the O(1) linear range sum query O(row2 - row1) times, after
taking a O(n<sup>2</sup>) hit up front transforming our input matrix.

## Complexity analysis

 - Time complexity: Amortized O(n)
 - Space complexity: O(1) (because we can overwrite values in our input matrix)

# Pure dynamic programming

My first thought when looking at this problem was that we can probably get an O(1) solution using dynamic
programming, and the preprocessing we'd probably want to perform here would be to maintain an off-the-side
matrix such that each value would be the sum of the submatrix consisting of every value above and to the left
of it. Then to get the sum of the submatrix, we can use the value dp[row2][col2], which is the sum of the
all-inclusive submatrix, and subtract "extra" values necessary to get only the sum of the submatrix we're
interested in. This very much extends the intuition of the single-dimension range sum query problem, by
applying it in two dimensions. From there, there are two tasks:

 - Figuring out how to build this master sum matrix
 - Figuring out how to use it to get our answer once we have it at our disposal

Let's look at building it. Consider the following input matrix:

```
1 2
3 4
```

We know our dynamic programming matrix will look something like this initially:

```
1 3
4 x
```

Building all of the outer rows and colums is trivial, but we run into the "meat" of the preprocessing
when extending diagonals. Obviously we have to use the surrounding values in some way. If we simply set
`dp[i][j] = dp[i - 1][j] + dp[i][j - 1]`, it is clear that we've double-counting the entire submatrix sum
sum `dp[i - 1][j - 1]`.  So we can simply subtract that sum to make up for double-counting it. Finally,
we'll need to include the actual matrix value at `[i][j]`:

```
1 3
4 10
```

Now with a matrix like this, we can realize the sum of the submatrix represented by the query (row1, col1) and
(row2, col2) will be the addition and subtraction of a few numbers. The largest all-inclusive sum will be `dp[row2][col2]`,
however we have to figure out what to subtract from this sum, since it may contain the sum of numbers we're not interested
in. To account for everything else that appears outside of it, we'll need to subtract the following submatrices
that were "accidentally" included in our larger all-inclusive sum:

 - The submatrix consisting of all elements to the left of our relevant submatrix (dp[row2 - 1][col1 - 1])
 - The submatrix consisting of all elements above our relevant submatrix (dp[row1 - 1][col2 - 1])

However since these subtracted submatrices overlap, subtracting them from our all-inclusive sum will double-subtract their
overlapped portion elements (dp[row1 - 1][col1 - 1]). To make up for this, we can simply add dp[row1 - 1][col1 - 1] back,
and that's it! With this preprocessing, each query can be carried out in O(1) time.

## Complexity analysis

 - Time complexity: Amortized O(1)
 - Space complexity: O(n<sup>2</sup>)

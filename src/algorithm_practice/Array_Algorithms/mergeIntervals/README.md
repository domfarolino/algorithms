# Merge Intervals

Source:

 - https://leetcode.com/problems/merge-intervals/description/

I thought this was a pretty cool problem. Basically we're given a list of
intervals (represented by vectors with two integers) not sorted in any way,
and we are tasked with coalescing all overlapping intervals, and returning
a list of non-overlapping intervals.

For example, when merging intervals [1, 4] and [3, 6], we produce one interval
[1, 6] consisting of the entire segment that both intervals covered.

The idea I had for this was to roughly:

 1. First sort the intervals by first number
 1. Start an index variable at the beginning of the list (`i = 0`)
 1. Start `j` at `i + 1`, and increment it while `intervals[j]` overlaps with the span of `intervals[i]`
    1. If they overlap, update our "span" to account for merging the two.
    1. The "span"'s first number should be `intervals[i][0]`, and the second number should be
       `std::max(intervals[i][1], intervals[j][1])` to account for the span possibly increasing.
 1. Record the "span" interval we just grew from incrementing
 1. Start over at `i = j`

It should be fairly intuitive that this works. Even if we're given a list of non-overlapping
intervals from the beginning, our `j` will not run forward any further than `i`, and each span
we record will just be equal to all of the non-overlapping intervals we were given. It is critical
that the algorithm updates its span when it comes across two overlapping intervals. We can see this
in action like so:

```
input: [[1, 5], [2, 8], [6, 9]]

1.)
starting span = [1, 5]

   i
[[1, 5], [2, 8], [6, 9]]

----------------------------

2.)
    i      j
[[1, 5], [2, 8], [6, 9]]

"span" and intervals[j] overlap. Update span

span = [1, 8]
j++

3.)
    i               j
[[1, 5], [2, 8], [6, 9]]

"span" and intervals[j] overlap. Update span

span = [1, 9]
j++

4.)

    i                      j
[[1, 5], [2, 8], [6, 9]]

We cannot run |j| and further (step 4 in the above algorithms steps). Record "span"
to our output ...

output = [[1, 9]]

..., and start i = j.

5.)

Return output (because |i| is already out-of-bounds
```

Some interesting test cases to consider are:

 - No intervals
 - One interval
 - All non-overlapping intervals
 - All neighboring intervals
    - Such as [[1, 2], [2, 3], [3, 4]]
 - Overlapping smaller intervals
    - Such as [[1, 9], [2, 8], [3, 4]]
    - This sort of test can verify that when two intervals are
      merged, we never make the resulting span smaller

# Complexity analysis

 - Time complexity: O(nlog(n))
 - Space complexity: O(n)
    - This is due to both the auxiliary space of sorting, as well
      as the output consisting of at most `n` elements (consider the
      input intervals already non-overlapping)

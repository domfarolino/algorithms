# Range Sum Query - Immutable

Source:

 - https://leetcode.com/problems/range-sum-query-immutable/description/

"Given an integer array nums, find the sum of the elements between indices
i and j (i ≤ j), inclusive." The problem is pretty simple. Given an array,
for each (i, j) query we can do some bounds checking (or assume the indices
are valid), and in O(n) we can get an answer by just linearly summing up the
values in between and including elements at the given boundaries.

A good question here would be to ask how many times we will be running queries
on the same input array. If the idea is that we may run a lot of queries, then
we might ask ourselves if doing some preprocessing on the input array can help
us perform these queries faster. We can make the realization that the sum of the
array [i, j] is really the sum of the array [0, j] - [0, i - 1]. If we can somehow
get O(1) access to the sums of [0, j] and [0, i - 1], then we can return our answer in
O(1) time. The key here is that we can build, in one up-front O(n) cost, an array that
sits alongside our input array that gives us these sums in O(1) time. The array will be
such that left[i] = sum of elements [0, i] from our input array. This is as simple as just
adding up all of the elements in our array and saving the result at each index.

 - In:    [-2,  0,  3, -5,  2, -1]
 - Left:  [-2, -2,  1, -4, -2, -3]

The `left` array above is the array we'll build alongside our input array. After
doing some examples, it should be clear that our answer is left[j] - left[i - 1],
however with this it is possible to index out-of-bounds when `i` is 0. In this case,
the second sum should be 0, since we're subtracting the sum of the array consisting of
no elements from the input array. What we can do here is pad our `left` array with a single
left-most 0, so that we don't index out of bounds, and just use an offset of 1 when initializing
and querying this array.

 - In:       [-2,  0,  3, -5,  2, -1]
 - Left:  [0, -2, -2,  1, -4, -2, -3]

Now given a query (i, j) we can look at left[j + 1] and left[i], knowing that left[i]
will always be in bounds, and left[j + 1] will be in bounds because the length of the
`left` array is one longer than the input array, so left[j + 1] represents the sum of
elements [0, j] in the input array. Good, we're all set!

# Importance of this technique

This is a common technique used when dealing with subarray sums, and also a similar
one is used when trying to find the min or max element in some subarray whose left or
right boundary is the left or right boundary of the larger array. Recognizing when to
use this style of array preprocessing for fast lookups is helpful!

# Complexity analysis

 - Time complexity: Amortized O(1) (up-front O(n) cost but O(1) for each query)
 - Space complexity: O(n)

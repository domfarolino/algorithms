# Permutations

 - Source: Classic CS problem
 - Source: https://leetcode.com/problems/permutations/description/

Generating all permutations of `n` distinct items is a classic problem in
computer science. I found that there are serveral ways of thinking about
this problem, each of which is documented below, and implemented in
`permutations.cpp`.

## Approach 1: Direct Recursion

I'm calling this approach the "direct recursion" approach, because at each
stack frame, we're making a single recursive call. The algorithm is pretty
straightforward, given `n` items, we want to recursively obtain the
permutations of `n - 1` items, and then sprinkle our `n`th item throughout
each of the `n - 1`! permutations of the `n - 1` items, creating the `n`!
permutations we need to return. For example:

 - Input: [1, 2, 3, 4]

In this case, we'd want to focus on 1, and obtain the permutations of items
2 through 4, inclusive. Let's assume we have all of these sub-permutations:

 - [2, 3, 4]
 - [2, 4, 3]
 - [3, 2, 4]
 - [3, 4, 2]
 - [4, 2, 3]
 - [4, 3, 2]

Alright, our recursive call has returned all of the permutations of `n - 1`
items. Now to "sprinkle" the `n`th number, 1, in to each one of them. Note
that there are `n` places we can insert an element into a list of `n - 1`
items. We'll need to do that for each of the permutations, thus multiplying
the total number of sub-permutations (`(n - 1)!` of them) by `n`, producing
`n!` total permutations. Then we're done!

### Complexity analysis

 - Time complexity: Related to O(n!)\*
 - Space complexity: O(n!)

\* I am only mentioning that the complexity is "related" to O(n!), because due to
some implementation details of the first two algorithms provided in `permutations.cpp`,
(a lot of front-insertions and copying) the time complexity greater than O(n!).

## Approach 2: Pretty Ordering

The approach above comes to me naturally, because it most-closely follows
the recursive nature of the factorial, in my opinion, as it generates all
permutations of `n - 1` elements, and extends them to create the permutations
of `n` elements. That approach does not produce the permutations in an ordered
fashion, like:

 - [1, 2, 3]
 - [1, 3, 2]
 - [2, 1, 3]
 - [2, 3, 1]
 - [3, 1, 2]
 - [3, 2, 1]

There is however, another method of generating all permutations of items that
does produce the permutations in order. It too might be considered a fairly
obvious method from looking at the above ordering. We want the first set of
permutations to start with 1, and then the next set to start with 2, and so
on; what we'll do then, is:

 - First hold onto ("fix") 1
 - Generate all permutations of [2, 3] (i.e., all items except for "1")
 - Append 1 to all of these sub-permutations
 - Next hold onto 2
 - Generate all permutations of [1, 3] (i.e., all items except for "2")
 - ...Rinse & repeat

In this case, we're not sprinkling our `n`th number into a ton of different
places, but instead we're only appending our number to previous permutations.
The consequence of less "inserts" at a given time, is that we're now making
as many recursive calls as there are elements in a given list, at each level
of recursion. Ultimately, this algorithm yields "prettier" results, at the
cost of generating `n - 1` permutations `n` times. Leetcode also claims that
this version is a bit slower in aggregate, which I think makes sense.

### Complexity analysis

Same as above

## Approach 3: Efficient swapping

This is a pretty nice algorithm I think, though some parts are a tad non-obvious.
This is a backtracking approach that essentially is:

 - Swap the first item with the next item
 - Recurse on a sublist
 - Undo the swap
 - Swap the first item with the next-later-appearing item
 - Recurse on a sublist
 - Rinse & repeat

(The steps above are quite simplified compared to the actual implementation).
When our recursion finally bottoms out (i.e., the sublist passed in is of length
1), we want to store the entire state of the `n` elements, accumulated swaps and
all, in our list of permutations. When our recursion unwinds, we'll undo the swaps
(backtrack) and further-recurse when necessary. This is probably not terribly clear,
so I encourage you to check out the implementation, and trace out a simple example
on paper to convince yourself that it works.

More info on this algorithm can be found
[here](https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/).

**Some notes**: The resulting permutations are not ordered. By constantly modifying
our input list and saving "snapshots" of it when we hit the base case, we minimize
the number of copies of the input we make, unlike the implementations of the other
two approaches. As a result, this approach is faster, uses less memory (says
Leetcode's solution analysis), and the complexity analysis is straightforward.

### Complexity analysis

 - Time complexity: O(n\*n!)
 - Space complexity: O(n!)

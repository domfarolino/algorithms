# Interleave Ordered Lists

This problem is, given two lists _a_ and _b_ of size _n_ and _m_ respectively,
return all possible ways to combine the lists while maintaining each's relative
ordering. The problem and this post are inspired by:

 - https://math.stackexchange.com/questions/2965187/how-many-different-tournament-orderings-are-there
 - https://math.stackexchange.com/questions/382174/ways-of-merging-two-incomparable-sorted-lists-of-elements-keeping-their-relative

If the lists were [1, 2, 3], [7, 8, 9], of course the combined list that results in combining
the two sublists could be [1, 2, 3, 7, 8, 9] as well as [7, 8, 9, 1, 2, 3], but that's not
the whole story. We need to account for all of the ways to interleave/intertwine the two
lists together, still maintaining the relative order in each list. For example, the following
orderings are valid, and need to be captured:

 - [1, 7, 2, 8, 3, 9]
 - [1, 2, 7, 3, 8, 9]

It's certainly a combinatorics problem. At first I thought of asking "How many possible items can we put in
the first spot? Second spot?" and so on... This got complicated. It is true that the first spot has two allowed
elements (the first element from each list), and so on maybe for a while, but some combinations result in certain
later positions having either 1 or 2 possible element depending on the previous ones. For example, if we're half way
through populating our combined list, and have been alternating between our two input lists as sources to populate each
consecutive spot in the combined list, the next spot after the half way point will have 2 possible elements to sit there.
However, if we _have not_ been alternating between the two lists when pulling elements to populate the combined list, and
have been pulling exclusively from one list, after we exhaust that list, each following spot in the combined list will only
have 1 possible element to sit there (all of the ones from the unexhausted list). This made it tricky to think about.

# _N_ choose _K_

It helps a lot to think of it as an _N choose K_ problem. If we make the realization that given some possible arrangement of
first-list items occupying slots in the combined list, there is _only 1_ possible way the second list can be layed out in the combined
list, our problem is greatly simplified. It essentially becomes the problem of "How many different ways can I place _n_ elements
(the elements of the first list) into _n + m_ slots of the combined list. The number of ways this can be done is, of course,
_(n + m) choose n_, or equivalently, _(n + m) choose m_ (see the second resource link above). Brilliant! So, now that we have the
math down, how can we actually iterate through all of these possible arrangements? How can we see all of the ways we can actually
lay _n_ items down in _n + m_ slots?

I thought of this as a triple nested for loop, in cases where _n = 3_. Say the combined list is of size 6. We can have 3 index pointers
`i`, `j`, and `k` iterate through all possible positions that the first list's elements could occupy in the combined list:

 - [i, j, k, \_, \_, \_]
 - [i, j, \_, k, \_, \_]
 - ...
 - [i, j, \_, \_, \_, k]
 - [i, \_, j, k, \_, \_]
 - [i, \_, j, \_, k, \_]
 - ...and so on
 - [\_, \_, \_, i, j, k]

This is simple when we know _n_ off the bat, as we can just have a bunch of for loops, and each iteration of the inner-most loop
would correspond to a different arrangement of the _n_ elements layed out over the _n + m_ elements. So how can we do this for some
arbitrary _n_? Well since we can't obviously write as many for loops as there are potential _n_'s, it seems we'll probably have to
simulate these for loops with recursion.

Again, what we care about is producing a list of all _n_ possible index pointer layouts, each index corresponding to a position
in the combined list that will be populated by an element from list _a_. The other elements (the "holes" in the arrays from the above
list) will be populated by list _b_, in their relative order. We can maintain a list of _n_ index counters, and write a recursive
function that focuses on a certain one of the _n_ indices, and increments it to the max value. When it hits its max value, it resets
to its original value + 1, and continues, just like a for loop works. That's probably a little confusing, so assume we are maintaining
a list of 3 indices (representing list _a_ of size 3), and we need to generate all possible index layouts that can fit in the combined array
of size 6 (_n + m_):

```
 +--->Max index value = 3
 |
 |  +--->Max index value = 4
 |  |
 |  |  +--->Max index value = 5
 |  |  |
[0, 1, 2] <== initial state
```

We'd want to recurse all the way to the end of this list, and increment the value until it hits the max value. Every single state of the
array in between value increments is a **valid mapping**. Once we're done incrementing, we can return, and now the stack frame we're at
is focusing in on the second-to-last index pointer. At this point we've gone through all mappings [0, 1, 2], [0, 1, 3], [0, 1, 4], and
[0, 1, 5], and we're looking at the second element (`1`) in the array. Now we want to increment this second-to-last element we're focusing
on, and continue recursing down to the last element, to go through all [0, 2, 3], [0, 2, 4], [0, 2, 5]. Once done, we'll increment the
second-to-last element value again until we reach _its_ max value, in which case we return to the first element, increment it, and continue
recursing. This process is like backtracking, and will continue until all index values are at their maximum. The main thing we have to do is
make sure when we first start recursing on some index, said index value is set to the previous index + 1. This is a crucial invariant, and is
just like how for loops work.

Sure, that lets us generate all **valid mappings** of indices that elements from list _a_ can populate in the combined list, but now we need
to be able to take some index mapping and the two lists _a_ and _b_, and return the combined list that consists of list _a_ elements at the
indicies denoted by the elements in the **valid mapping**, and list _b_ elements in the other positions. This is simple enough, and there are
several ways to carry this out. See the `combineLists` function in `interleave.cpp` in this directory.

Assuming this sounds complicated, take a look at the entire implementation of this solution in `interleave.cpp` :)

# Complexity Analysis

 - Time complexity: O((n + m) choose n), where _n_ and _m_ are
 - Space complexity: O((n + m) choose n)

# Generate Reduced Catalan Parentheses Orderings

This problem is a modified version of Leetcode's
[Optimal Division](https://leetcode.com/problems/optimal-division/description/) problem, whose solution is inspired by the
[Catalan Sequence](../catalanSequence) algorithm in this repository. After going through some examples, it was apparent that
the Leetcode problem was a modified version of the Catalan Parentheses Orderings problem; in fact it is essentially the same
however all left-most parentheses should be removed, as they are considered "redundant" (note by "reduced" in the title of this
page, I mean "not containing redundant parentheses", not reduced as in a/b/c could be reduced to = (ac)/b). When trying to solve
this, since it seemed like a specific problem than the Catalan orderings so I wanted to do that first, and simply modify the solution
to come up with this, and that's what I did. I recommend reading the [catalan orderings](../catalanSequence) post first.

Essentially the algorithm and analysis is the same, the only difference is that instead of adding parentheses around all of the
left groupings combined with the right, that is, "(" + *Groupings(k)*x*Groupings(n - k)* + ")", we need to just add parentheses
around the right groupings, as well as a division sign (specific to the Leetcode problem), like
*Groupings(k)* + "/(" *Groupings(n - k)* + "). An edge case here is to make sure we don't add parentheses around a right grouping
that is a single element.

# Complexity Analysis
 - Time complexity: O(Cat(n))
 - Space complexity: O(Cat(n))

# Follow-up thoughts

While this problem has a really nice solution, a formula, a wiki page, and awesome literature about it like this,
the solution (and solutions like it for that matter) aren't always easy to come up with. My first go at this before
coming up with a working solution brought me to an algorithm that for each term, considered every subsequence starting
at that term. For example, with the terms [1, 2, 3 4], I'd consider the following subsequences:

 - [(1, 2), 3, 4]
 - [(1, 2, 3), 4]
 - [1, (2, 3), 4]

...then I'd recurse inward on that subsequence, connecting all of the groupings of that subsequence with a prefix
and suffix that consisted of the surrounding terms. Where this algorithm was lacking though, was that it only recursed
inwards, meaning that it would ignore possible groupings

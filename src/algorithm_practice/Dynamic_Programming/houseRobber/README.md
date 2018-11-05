# House Robber

Source:

 - https://leetcode.com/problems/house-robber/description/

This problem is very similar to the [climbing stairs](../climbingStairs) and
[min cost climbng stairs](../climbingStairs/minCostClimbingStairs) problems. The
reason this problem is a little bit tricky is just like why the min cost climbing
stairs problem is tricky, in that we can't always be greedy when robbing houses.
Instead of choosing to rob a house purely on the amount of its own loot, we have to
choose the most beneficial _path_ of houses to rob, which may include houses with
a lower amount of loot than their neighbors.

# Naive solution

We could generate all 2<sup>n</sup> possible combinations of houses to rob, and see
which ones provide the biggest amount of loot. Of course some of the 2<sup>n</sup>
combinations will not be valid (they may imply "robbing" two houses in a row), so we'll
need to only consider combinations/paths that don't rob consecutive houses as candidate
paths, while we search for the max path.

## Complexity analysis

 - Time complexity: O(2<sup>n</sup>)
 - Space complexity: O(2<sup>n</sup>) if we store all possible paths, O(n) if we store one at a time

# Dynamic programming

This seems very much like a back tracking problem where we need to look at each
possible path from the end. We know we'll get to the very last house and either rob
it, or we won't rob it because it was more beneficial to rob the house before it and
leave the last one alone. A simple example can be constructed to show that always choosing
the most bountiful house to rob does not always work.

<details>
  <summary>Greedy doesn't always pay off</summary>
Consider the houses: [8, 20, 1000]. In this case, we can start by robbing either 8 or 20.
20 is obviously larger, however if we choose it solely on that merit, we cannot rob 1000
or 8, and robbing both of those would be much more ideal. Same goes for the end houses:
[400, 20, 10]. If we're looking backwards, we might say "Oh we definitely want to end by
robbing house 20, so let's build our path backwards on that premise, and not rob
400", when in fact it would be more advantageous to rob 10 in the end, so that we're able
to rob the bountiful 400 house.
</details>

<br>

So what determines whether or not we can rob a house? Well, we're better off robbing a house if
we're _not_ better off robbing the immediately previous house. In other words, if robbing the
immediately previous house is _super super_ good, we'll choose to _not_ rob its neighbor.
We also have to look at the other possibility: robbing the current house is more beneficial than
robbing the previous. In other words, adding the current house's loot value to the max loot path
ending at the _previous previous_ house is more beneficial than just taking the previous's max path
loot value and not robbing the current house. That sounds very confusing, but let's look at some examples
to see:

Two houses:

 - In: [8, 10]
 - Out: 10

That was a simple example, let's try three houses, with the third house having two different values
that may influence our answer as we talked about:

 - In: [8, 10, 1]
 - Out: 10

10 is the answer here, because if we take 1, the best previous loot path we could get would be 8.
1 + 8 is less than 10, so we're better off just taking 10.

...and now for the third house to make choosing the first house more appealing:

 - In: [8, 10, 9]
 - Out: 17

17 is the answer, because when it comes to considering the house with 9 loot, we know we can also
take the house with 8. Otherwise we can take 10 and skip 9. Since 8 + 7 > 10, we take it. Now we
can think what it would be like to generalize this solution:

 - In: [..., ......., 8, 10, 9]
 - Out: max(9 + maxLoot(8), maxLoot(10))

In our previous example with 3 houses, when we "looked backwards", we looked at the previous house
loot values. With a ton of houses in the array though, we can't just consider the previous house
_values_, but instead we need to consider the previous end path values up to that point. We're taking
earlier and smaller subsolutions, and extending them by adding another house to the end, and making the
best decision. This gives us the following recurrence relation:

```maxLoot(n) = max(maxLoot(n - 2) + currentLoot, maxLoot(n - 1))```

## Top-down approach

Now we just need the answers to the subproblems `maxLoot(n - 2)` and `maxLoot(n - 1)`. Implementing this
naively gives us a very wasteful solution, similar to the naive fibonacci, because we're computing subsolutions
over and over again. After we solve a subproblem, we can save the answer for O(1) future look-up, since it'll
be needed again. Just like with the [climbing stairs](../climbingStairs) problem, we can see that we'll be building
up our memoized subproblem solutions from the bottom up, in order,, indicating that we can also implement a
bottom-up approach.

## Bottom-up approach

As with many dynamic programming problems, bottom-up approaches are relatively clean and useful. In this case, we can
create an array the same size as our input list, and each entry memo[i] will contain the max loot path from houses [0, i].
We'll build this array up iteratively with the logic we previously uncovered, and the final value will be the one we want
to return. In fact, we can actually use our input array as the memo, and overwrite the house loot values in it with the
max loot path values ending at a given house. Watch out for edge cases.

## Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(1) (since we're modifying the original array, and not using any more space on top of that)

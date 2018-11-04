# Min Cost Climbing Stairs

Source:

 - https://leetcode.com/problems/min-cost-climbing-stairs/description/

This problem is quite quite similar indeed to the normal climbing stairs problem.
In this case, we are interested in the path to the end of the staircase that provides
the least "cost" possible. We can start from either of the first two steps (at index 0
and 1 respectively), and our goal is to end just after the array, so the final step can
either be the last or second to last step in the input array. We should be able to guarantee
that our steps vector has at least two steps in it. This would be a good assumption to clarify.

The solution is extremely similar to the vanilla version of climbing stairs as previously
mentioned. Also as mentioned, the last step we'll be hitting will either be the last or
second to last step. Therefore, the final answer is `min(minCost(n - 1), minCost(n - 2))`.
We can use this to build a nice recurrence relation that can act as the basis to our solution.
The min cost to get at some step `n` is `minCost(n) = min(minCost(n - 1), minCost(n - 2)) + cost[n]`.
It is really important that we add that last bit `+ cost[n]`, so we can actually accumulate cost as
we go. We need to accumulate the cost as we go because our algorithm should not be greedy and just
try and choose the cheapest predecessor step when looking backwards, as that may not always work out.
Instead we have to choose the cheapest predecessor _path_, and continue.

A simple proof of concept that choosing the cheapest predecessor steps do not always work can be
seen here: [0, 12, 6, 5]

The final two steps in the staircase have a costs 6 and 5 respectively. In this case, we're better
off ending in step 6 than 5 to make our final leap off to the end of the array, even though 6 is
technically more expensive step than 5. This is because the cheapest _path_ ending with 6 is cheaper
than the cheapest _path_ ending with 5. A solution to check out all possible paths to give a fair and
exhaustive evaluation feels a lot like backtracking, and is the same as our tree-recursive naive solution.
We'll recurse all the way to the base case, which is one of the first two steps whose path costs are their
values, since they have no predecessor steps. We'll then start building our solution up from the bottom.

This top-down tree-recursive solution duplicates a ton of work by examining all paths though. We can make
the realization that once we unwind from recursion, we'll be calculating each subproblem answer on the way
up, and no matter what future paths may use this sub-step as a part of their own paths, the min path cost
from said sub-step will always be the same, so once we compute it, we'd be better off saving it to the side
for future use, for memoization.

```
                  _____ minCost(4) _____
                /                        \
            minCost(3)                minCost(2)
          /           \             /           \
      minCost(2)  minCost(1)    minCost(0)     minCost(1)
       /      \
minCost(1)   minCost(0)
```

With the above tree, we can realize that on the way back up from recursing down to the base case, we compute all
subproblem answers in order, and save them for re-use. Every time we come up from a left-subtree and attempt to go
down the right sub-tree, the answer to the right sub-tree will be in our memo. While memoization helps a lot here,
we can just skip the middle man (recursion) and implement a nice bottom-up solution that calculates the min cost path
from each step as we iterate through the input array.

Additionally, we can use the very same array that we've been given to store the max cost paths for each step instead
of just the step costs themselves. Modifying the input array like this is safe, since once we compute the min path cost
from a step, we'll never need its individual cost again, or the individual cost of any predecessor steps. We'll want to
do this with steps beyond index 0 and 1, and when we finally get to the end, we'll want to return the min(arr[n - 1],
arr[n - 2]), will be the min cost path that results in us getting to the top of the staircase.

# Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(1) (since we're re-using the given array, though ultimately I'd say it
                           depends on how you count the input array in terms of storage)

# Max Path

This a modification of the [house robber](..) problem, where we not
only want to find the maximum amount of loot we can steal, but we also want to
return the list of houses in the order to rob, that provides said maximum amount
of loot.

Really this can be done by just extending our solution to [house robber](..). Like
the typical bottom-up dynamic programming solution, we can maintain our loots array
that we modify as we move forward to maintain our max loot value, but we'll also want
to maintain a `first` and `second` vector of loots that describe the path of loots to
take at the subproblems n - 2 and n - 1 respectively. For example, consider the following
loots:

```
[8, 10, 9]
        ^
        |

first = [8]
second = [10]
```

Any problem with less than 3 loots is trivial, so this is the general case. We can start
with `first` and `second` already filled out as they are trivial and initial base case. The
idea is that when we get to the end, `loots[loots.size() - 1]` will contain the maximum
amount of loot we can rob, and `second` will contain the path to get us this amount of loot.
So when we consider our third value `9` here what do we do? We know there are two case; one
of the following will be more beneficial:

1. Just drag along loots[i - 1] and not add the current value (9 here) to it
1. Take loots[i - 2] and add the current value (9 here) to it

In our example, the first option is the best since 17 > 10. Here we'll want to the following state:

```
[8, 10, 9]
 f  s    ^
         | (done)

first = [10]
second = [8, 9]
```

...indicating that we'll want to add our current value `loots[i]` to whatever path makes the most
sense, and if this path is `first`, we'll want to swap `first` and `second`, because `first` is
the new (latest) `second`. How about if the second option in our list is the most beneficial? Consider
the problem:

```
[8, 22, 9, 1]
 f  s   ^
        |

first = [8]
second = [10]
```

Here it makes more sense to drag along `second` without adding anything to it since it is
so strong on its own, putting us in this desired state:

```
[8, 22, 9, 1]
    f   s  ^
           |

first = [22]
second = [22]
```

...you may notice that these operations we perform on the `first` and `second` path lists directly
correspond with the operations we'd perform in the normal case of `houseRobber`. When it is more
advantageous to add the current value to the subproblem n - 2, that becomes our new n - 1, and our
n - 1 becomes our new n - 2. Otherwise if we want to drag along n - 1, we set our n - 2 equal to it,
and prepare to update our n - 1 the next iteration. This is also just like how we would iteratively
and with O(1) space compute fibonacci numbers.

# Complexity analysis

 - Time complexity: O(n) (or O(n<sup>2</sup>) when you consider all of the assignments/copies made)
 - Space complexity: O(n)

# Best Time to Buy and Sell Stock

This is an interesting problem because on the surface it might feel like we want
to find the lowest low and the highest high, and of course do the math from there.
That won't always work of course, and fails in the case where the lowest low appears
_after_ the highest high. So a solution general enough to work on any array and powerful
enough to meet the necessary conditions. So really we want to find the lowest low before
the highest high. We can of course do this naively, by checking each unique pair of numbers
in the array, but we should be able to do this in linear time, with no extra space.

## Assumptions

We can assume the array given has at least a single element, and may contain positive or
negative integers (though it wouldn't make much sense for a stock price to be _negative_, but
it is the theory we're really interested in). Of course the array is not sorted in any way. If
there are no buy/sell moves to make, return 0, which is the equivalent of not performing any
transaction.

## Examples

Perfectly increasing array:

 - In: [0, 1, 2, 3, 4, 5, 6, 7]
 - Out: 7

In this case, we want to buy on the first day and sell on the last.

Perfectly decreasing array:

 - In: []
 - Out: 0

Given this timeline, there are no advantageous moves to make, so we make none,
yielding a profit of 0.

Other:

 - In: [4, 5, 8, 1, -2, 4, 5]
 - Out: 7

The lowest low comes after the highest high, but the largest range in this case
is between the lowest low and the highest high _after_ said low, = 7.

Interesting:

 - In: [4, 5, 10, 1, 9, -2, 4]
 - Out: 8

In this case, let's look at two ranges:

 - The lowest low, and the highest high _after_ said low [-2, 5] = 7
 - The highest high, and the lowest low _before_ said high [4, 8] = 4

However, we can see that the largest chronological range is [1, 9] = 8. That said,
we'll need a solution that doesn't just revolve around the lowest low and the highest
high.

# Linear solution

Let's attempt a solution that maintains two pointers into the array, and inchworms through
the array, moving one forward until some condition is met, and then the other. This is a common
paradigm for linear, single-pass solutions, and in this case, lets us observe all relevant ranges.
Let's start with the first price value, and set that to our current _low_ pointer. We'll consider
the next value in the array as a potential _high_ candidate. If the value at _high_ is higher than
that at _low_, that'll be our new _high_ pointer, and we'll want to take a snapshot of the current
range and save it off to the side.

If the value at _high_ is lower than that at _low_, this range is useless to us, and furthermore, we should
set our _low_ pointer to this index. We know that is a good move, because any range between _low_ and some future
_high_ can only be maximized if the value at _low_ can be made any lower. From this point, we only want to consider
forward ranges, so we'll also need to set _high_ = _low_, and restart from this point, moving forward. We'll keep
moving _high_ forward, updating our maximum range "snapshot" when applicable. We'll want to update our _low_ and
_high_ pointers when we meet a value lower than the current _low_. If we follow these two rules when updating our
pointers, we'll inchworm through the array, observing relevant ranges. Nice!

This solution has a bit of a dynamic programming ring to it, because for each range we observe, we look
to _extend_ the range to include the next value, building our results (current max profit) off of earlier
ones while we can, until we have to "reset".

# Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(1)

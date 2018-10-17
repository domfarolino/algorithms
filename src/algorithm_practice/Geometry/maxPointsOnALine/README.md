# Max Points on a Line

Sources for this problem:
 - https://leetcode.com/problems/max-points-on-a-line/description/
 - https://www.geeksforgeeks.org/count-maximum-points-on-same-line/

Interesting problem. Given n points, return the max number of points that are
on the same line. The general case of this problem is relatively easy, but there
are a lot of tricky edge cases. Let's start though, by looking into the general case.
What makes two points on the same line? Well, two points are always on the same line,
because a line can always be drawn between two points, connecting them. So what makes
three, or a group of points on the same line? For multiple points to be on the same line,
the lines between all points must have the same slope. Ok so now we're getting somewhere. So
given [(1, 1), (2, 2), (3, 3)], the line in between [(1, 1),  (2, 2)] has a slope of 1, and the
line in between [(1, 1), (3, 3)] also has a slope of 1, so these points must all be on the same line.
We can safely say that an arbitrary point is on the same line that connects two other points, _l1_, if
the line connecting the point to any of the other points, _l2_, has the same slope as _l1_. A mouthful huh.

So the idea I had when solving this one was to basically take a point, hold onto it, considering it anchored,
and compute the slope of the line between our anchored point and all other points. If we ever see the same slope
twice for for example, we know there are 2 + 1 (have to count the anchored point) on the same line. Similarly if
there are n occurrences of the same slope, there are n + 1 points are on the same line. Looks like we'll need to
track how many times a given slope is encountered. This binning-by-occurrence problem sounds like a perfect job for
a map :) We know that computing slope is relatively simple, and can be done with: (y2 - y1) / (x2 - x1). You may observe
that it is possible to divide by 0 with that current scheme. Dividing by 0 would mean two points have no x-axis difference,
which seems like a special-case, so let's check out some edge cases:

 - In: [(4, 5)]
 - Out: 1

 - In: []
 - Out: 0

 - In: [(1, 1), (1, 1), (1, 1)]
 - Out: 3

 - In: [(1, 1), (1, 0), (1, 1)]
 - Out: 3

 - In: [(1, 1), (0, 1), (1, 1)]
 - Out: 3

Going through some examples it is clear that we have to watch out for the following edge-points:

 1. Same points
 2. Points with no x-axis diff from the anchor point
 3. Points with no y-axis diff from the anchor point

Points from category (2) should be binned as having line slope ∞ (can be something like INT\_MAX maybe). Points
from category (3) should be binned as having line slope 0. Points from category (1) are very special cases, as they
technically meet the conditions of category (2) and (3) points but as such, should not be limited to just either of those.
They are essentially gimme-points, which can add +1 to the max number of points on a given line. In other words, when we come
across a same-point, we don't want to count it immmediately as a point from category (2), (3), or any other random point with
some slope. Instead, we should keep this number of points off to the side, and simply add 1 to the max number of points sharing
the same line for a given anchor. Speaking of max number of points sharing the same slope, it is true that our map will keep the
number of occurrences for each slope, but we can save ourselves from iterating through all map entries after we are finished looking
at an anchor point to find the highest valued key, by just keeping some curr-max-slope variable off to the side, and whenever we increment
a slope value in the map, check to see if it has overtaken the previous curr-max-slope. We'll maintain this variable as well as the map, and
reset both, for each anchor point. This is a cool trick that's often used in max-occurrence-counting-esque problems.

We'll want to consider all n - 1 points as anchor points, and the remaining points as points we'll calculate slope with,
in relation to the anchor. We'll also want some sort of global max-points-on-the-same-line variable. It's important that
we know to +1 our max-points-on-the-same-line variable, to account for the anchor point appearing on its own line.

Concerns: When dealing with `double` types, which we'll need to represent our computed slope, it is possible that we'll run
into precision issues. This sort of thing should be addressed with an interviwer.

# Complexity analysis

 - Time complexity: O(n<sup>2</sup>)
 - Space complexity: O(n)

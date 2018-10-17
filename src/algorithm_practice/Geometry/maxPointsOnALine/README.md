# Max Points on a Line

Sources for this problem:
 - https://leetcode.com/problems/max-points-on-a-line/description/
 - https://www.geeksforgeeks.org/count-maximum-points-on-same-line/

Interesting problem. Given n points, return how many points are on the same
line. The general case of this problem is relatively easy, but there are a lot
of tricky edge cases. Let's start though, by looking into the general case. What
makes two points on the same line? Well, two points are always on the same line,
because a line with any slope can be drawn between the two points, connecting them.
So what makes three points on the same line? For three points to be on the same line,
the lines between all points have to have the same slope. Ok so now we're getting somewhere.
So given [(1, 1), (2, 2), (3, 3)], the line in between [(1, 1),  (2, 2)] has a slope of 1, and
the line in between [(1, 1), (3, 3)] also has slope of 1, sow we can safely say that since two
points, when anchored by the same point, have the same slope, three points are on this line.
Of course the line between [(2, 2), (3, 3)] also has the same slope, but it will actually be easier
for us to anchor a single point.

So the idea I had when solving this one was to basically take a point, hold onto it, and take a look
at all other points, and compute the slopes of the lines that connect the two points. If there are two
points that share the _same slope_ in relation to our anchored point, we know that there are 2 + 1 points
on that line. If there are n points, similarly n + 1 points are on that line (because of course we have to
count the anchored point). As such, if there are 0 points that share the same slope when anchored by the same
point, in other words, if all lines between our anchored point and all other points have unique slopes, then only
0 + 1 points are on the same line. Looks like we'll need to track how many times a given slope is encountered. This
binning-by-occurrence problem sounds like a perfect job for a map :) We know that computing slope is relatively simple,
and can be done with: (y2 - y1) / (x2 - x1). You may observe that it is possible to divide by zero with that current scheme
Dividing by 0 would mean two points have no x-axis difference, which seems like a special-case, so let's check out some edge
cases:

 - In: one point
 - Out: 1

 - In: no points
 - Out: 0

 - In: [(1, 1), (1, 1)]
 - Out: 2

 - In: [(1, 1), (1, 0)]
 - Out: 2

 - In: [(1, 1), (0, 1)]
 - Out: 2

Going through some examples it is clear that we have to watch out for the following edge-points:
1.) Same points
2.) Points with no x-axis diff from the anchor point
3.) Points with no y-axis diff from the anchor point

Points from category 2.) should be binned as having line slope 0
Points from category 3.) should be binned as having line slope ∞ (can be something like INT\_MAX maybe)
Points from category 1.) are very special cases, as they meet the conditions of category 2.) and 3.) points
but as such, should not be limited to just either of those. They are essentially gimme-points, which can add
+1 to the max number of points on a given line. In other words, when we come across a same-point, we don't want
to count it immmediately as a point from category 2.), 3.), or any other random point with some slope. Instead,
we should keep this number of points off to the side, and simply add its value to the max number of points sharing
the same line for a given anchor. Speaking of max number of points sharing the same slope, it is true that our map
will keep the number of occurrences for each slope, but we can save ourselves from iterating through the map at the
end to find the highest valued key, by just keeping some curr-max-slope variable off to the side, and whenever we
increment a slope value in the map, check to see if it has overtaken the previous curr-max-slope. We'll maintain this
variable as well as the map, and reset both, for each point. This is a cool trick that's often used in max-occurrence-counting
problems.

We'll want to consider all n - 1 points as anchor points, and the remaining points as points we'll calculate slope with,
in relation to the anchor. We'll also want some sort of global max-points-on-the-same-line variable. It's important that
we know to +1 our max-points-on-the-same-line variable, to account for the anchor point appearing on its own line.

Concerns: When dealing with doubles, which we'll need to represent our computed slope, it is possible that we'll run into
precision issues. This sort of thing should be addressed with an interviwer.

# Complexity analysis

 - Time complexity: O(n<sup>2</sup>)
 - Space complexity: O(n)

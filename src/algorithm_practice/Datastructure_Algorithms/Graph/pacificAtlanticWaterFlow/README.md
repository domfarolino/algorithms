# Pacific Atlantic Water Flow

Source:

 - https://leetcode.com/problems/pacific-atlantic-water-flow/description/

This problem is pretty similar to [surroundedRegions](../surroundedRegions) and
[number of islands](https://leetcode.com/problems/number-of-islands/description/).
It is important to realize that we're not trying to determine whether or not pacific
water can flow into atlantic water or vice versa, but instead, if some water were to
start at some arbitrary point in the map, could water from that source make it to both
the pacific and the atlantic. In more technical terms, we care about sources that can
_reach_ the pacific and atlantic, not areas that are _reachable_ by them.

# Naive

The brute force solution here would be to, for every unit of land in the grid, do a DFS
out from said unit, and if the DFS eventually reaches a unit of land that:

 - borders that pacific, and
 - borders the atlantic

...we know the unit we started from should be included in our returned list of pairs.
The DFS will be O(n\*m), and we'll be carrying it out for each unit of land in the grid
(O(n\*m) times. This is really expensive because we're not saving any of our work anywhere.

DFS will recursively trigger other DFSs. It would be ideal to save the result of those DFSs and we could save the result of those DFSs somewhere
to ensure we don't re-compute results we've already come across, repeating a ton of work. This
brings some implementation complexity, but...

 - Time complexity: O((n\*m)<sup>2</sup>)
 - Space complexity: O(n\*m) (it is tempting to say O(1) here, since we don't maintain an
   copy of the grid during our computation, but you still have to count the size of the returned pairs)

# Optimized

## Complexity analysis

 - Time complexity: O(n\*m)
 - Space complexity: O(n\*m)

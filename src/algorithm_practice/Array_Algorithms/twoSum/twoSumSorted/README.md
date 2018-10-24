# Two Sum Sorted

This is basically the same problem as we see one directory up,
but going the sorting route instead. In this case, the array is
already sorted. This suggests that we perhaps _should_ search for
the complement value in the rest of the array, when focusing on a
given element, via binary search. Again, we'll be doing O(log(n))
searching work for O(n) elements.

# Complexity analysis

 - Time complexity: O(nlog(n))
 - Space complexity: O(1) (the array is already sorted!)

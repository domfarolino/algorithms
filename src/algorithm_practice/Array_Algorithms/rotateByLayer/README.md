# Matrix Layer Rotation

Sources:
 - https://www.hackerrank.com/challenges/matrix-rotation-algo/problem
 - https://leetcode.com/problems/rotate-image/

This problem is described in the first link above, which is also a generalized version of the
Leetcode problem in second link above. At first I tried solving this problem naively. First I
figured out how to rotate the outer-most layer of a given matrix. This can be done by simply
storing the top-left-most value in a temporary variable, and then performing the following
steps:

 1. Shifting the entire top row to the left
 2. Shifting the entire right column up
 3. Shifting the entire bottom row to the right
 4. Shifting the entire left column down
 5. Replacing the value under the top-left-most one with the temporary variable

This was easy enough. To make it generalize to multiple layers, it was clear that that we
needed some left- and top-offset variables, as well as to continually tighten the bounds of
each row and column as we move to deeper layers. With an algorithm that could rotate each layer
of a matrix by one, all that was left is to call it `r` times to satisfy the given number of
rotations.

## Optimization

The above approach is terribly slow (and times-out on Hackerrank) for an enormous number of
rotations. The key optimization to make it realizing that we may not always need to make the
number of rotations specified. For example, if we have a `2x2` matrix, making `n` rotations
where `n` is a multiple of 4, yields the same exact matrix.

```
1 2
4 3
```

This means we can implement some modular arithmetic to help us avoid carrying out an unnecessary
number of layer rotations. Specifically, we can compute the effective number of rotations given `r`
as `r % perimeter`. Note however, that since the "effective" number of rotations for a layer
depends on the layer's perimeter, this means that to implement our optimization, we'll need to
support rotating given layers independently. With this done, we can iterate through the number of
layers in our matrix, computing the offsets, bounds, and "effective" number of rotations. With this
information, we can rotate each layer independently, the correct number of times.

## Complexity analysis

 - Time complexity: O(m\*n<sup>2</sup>)
   - My logic is that the number of layers is bounded by min(m, n), and each
     may be rotated at most, a number of times proportional to the perimeter, which
     is bounded by 4*(max(m, n)). This gives us O(min(m, n)) * O(max(m, n)).
 - Space complexity: O(1)

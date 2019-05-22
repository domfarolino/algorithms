# Majority Element

 - Source: https://leetcode.com/problems/majority-element/description/
 - Source: https://www.geeksforgeeks.org/majority-element/
 - My advanced Algorithms I class
 - https://cs.stackexchange.com/questions/91803

This is a fun problem (description can be found in the above links). What makes
this one interesting is that there exists a very obvious naive solution that
provides both linear time and space complexity, however with some thought, a
constant-space solution reveals itself.

## Boyer-Moore Voting

The constant-space solution is obviously not going to maintain any data structure
whose size requirements are proportional to the input. This may imply that we're
going to maintain a single counter or something of the sort.

Imagine we maintain a single counter `count` that counts the number of times we see
a given number, starting with the first element in the array. Each time we see the
number, we increment `count`, each time we see a different number, we decrement
`count`. Clearly it is possible for `count` to reach `0`. In this case, let's reset
the count, and focus on the number we're currently looking at. This concept of maintaining
a count and resetting it whenever we need is the Boyer-Moore Voting algorithm. Let's look
at a couple trivial examples to see it in action:

```
In: [1, 1, 1, 2, 3]
Out: 1

1.)
    [1, 1, 1, 2, 3]
     ^ count = 1

2.)
    [1, 1, 1, 2, 3]
        ^ count = 2

3.)
    [1, 1, 1, 2, 3]
           ^ count = 3

4.)
    [1, 1, 1, 2, 3]
              ^ count = 2

5.)
    [1, 1, 1, 2, 3]
                 ^ count = 1
```

Since when we get to the end of our array, our non-zero count is associated with `1` (this
is some book-keeping we'll need to maintain off-the-side). In this case, we know `1` is our
majority element. Note that if we cannot guarantee that there is always a majority element,
we'll need to invoke a second simpler algorithm that checks if that last number we arrived at
_actually is_ a majority element if `count == 1`.

This is because, even if there is no majority element, `count` is guaranteed to be non-zero
when we get to the end. Then, we'll just have to see if the element we've landed on actually
appears more than `n/2` times, or if it just _happened to be the last element_.

## Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(1)

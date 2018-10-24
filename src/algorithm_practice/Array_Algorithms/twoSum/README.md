# Two Sum

The source for this problem is:

 - https://leetcode.com/problems/two-sum/description/

This is a good problem because it really exercises the fundamentals,
and has several different approaches. Problem:

In: array of integers _arr_, some number _k_
Out: two indices such that the values in _arr_ at the two indices, when
summed, add up to _k_.

The goal of the problem should be relatively clear from the above sentences.
Some assumptions that would be good to clarify:

 - Is the input sorted? _No_
 - Can the input array have negative numbers? _Yes_
 - Can the input array contain duplicates? _Yes_
 - Can we use the same number twice to contribute to our sum? _Only if it is a duplicate. You cannot use the same number at the same index twice though, no_
 - If there are multiple solutions can we return any valid solution? _Yes_

It is important to see that the problem can be broken down into a smaller problem by focusing on
one number at a time. We're looking for two numbers that sum to _k_, so if we focus on the first
number, now we only need to look for a single number is equal to _k - firstNum_. So, how can we
determine, given a list of integers, whether some number exists? The problem is essentially a
membership problem, to which there are several different solutions.

# Naive Iteration

If we're focusing on a number, we can brute-force check all of the other numbers in the list by
just iterating through the rest of the list, and seeing if the two numbers fit our requirements.
For each number we focus on, attempting to find a second number that fits the bill is O(n). Since
our membership problem is O(n), and we have to do it for O(n) numbers, the solution is quadratic
in time, and uses no extra space.

## Complexity analysis

 - Time complexity: O(n<sup>2</sup>)
 - Space complexity: O(1)

# Sorting

How can we get a faster solution to our membership problem? While focusing on one number, we just
have to see if another number exists in the rest of the list. We know that if the list was sorted,
we can perform "lookups" or "membership queries" in O(log(n)). So, we can spend some time up front
sorting the input list (O(nlog(n))), and for each number we come across, we can search for its complementary
value in the remaining portion of the array in O(log(n)) time. Since we'll be searching O(n) times.

## Complexity analysis

 - Time complexity: O(nlog(n)) (sorting + O(n) searches, each taking O(nlog(n)))
 - Space complexity: O(n) (due to sorting)

# Hashing

How can we get _an even faster_ solution to our membership problem? We know that hash tables/sets are
pretty good for determining existence in O(1) time, so if we can utilize one that provides O(1) time
lookups, for each of the O(n) numbers we'll focus on, we can get an O(n) solution. My first idea was that
for each number in the input array, we want to see if its complement number exists anywhere in the array.
Therefore, first we could first populate a map {number: index} with all of the numbers in the array. Then, for
each number in the array, we check to see if its complement exists. This is nice, but we have to watch out for
duplicate values. If we have the array [1, 2, 4], and sum 8, or 2 maybe, we have to be careful that we don't
count the same number twice if it does not exist twice. So what we could do is make sure each map entry's value
is the last index that a number appears at. Then, when we come across "4" and consult our map asking
"does 8 - 4 = 4 exist?", when it says yes, we have to make sure the index the map has is not the same index as
the value we're looking at. This works nice, but we can also do it in less than two passes.

Let's try and build our map up the other way around. When we come across a value, we should consult our map to
say "have we seen the value's complement _yet_?". If the answer is no, add the entry map[currVal] = currIndex
to the map. If the answer, is yes, return the pair (map[complement], currIndex). By building our map up as we
iterate through, and checking the map before adding a number to it, we're sure to only see complement numbers in
the map that are not the same number we're looking at.

## Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(n)

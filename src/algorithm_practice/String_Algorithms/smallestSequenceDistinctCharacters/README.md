# Smallest Subsequence of Distinct Characters

Source:

 - https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/description/

I thought this was a really interesting problem! The problem asks for the smallest
subsequence of distinct characters, and by smallest, it means lexicographically smallest
(think alphabetical order).

Examples:

 - In: "cdadabcc"
 - Out: "adbc"

Here we can see that the first subsequence of distinct characters we come across by order
is "cdab", which indeed contains all of the distinct characters from the input string.
However, "c" is not the lexicographically smallest character in our string, so we'd benefit
from seeing if we can find a subsequence starting from "b" or "a", which we can!

 - In: "zcbabc"
 - Out: "zabc"

Here, "z" is not the lexico[...] shortest string either, but there exists no subsequence
starting with any other letter that covers our set of distinct characters. However, it is
key to find that even though it is easy to come across "zcba", the string "zabc" is possible
to form, and lexicographically smaller.

(See the source link above for more examples)

# My approach

The approach I took for this problem was to pick the lexico[...] smallest distinct character,
and see if the first instance of it appears before the last instance of all of the other characters.
If so, we know our return subsequence can start with this character. If not, consider the
second-lexico[...] smallest character as our starting character, see if its first instance appears
before the last instance of all other distinct characters, and so on.

When we finally find a valid starting character, record the index of its first location in the input
string as `idx`. Now to find a second character. Iterate over the list of remaining distinct characters
in alphabetical order (does not include the letter we just chose as our starting character). Find a
character that appears after `idx`, but before (or equal to) the last instance of all remaining distinct
characters. Since we're iterating in alphabetical order, once we find one, we know we've found the best
one. Record it to our "return subsequence" string, and remove it from the list of "remaining distinct
characters".

We'll repeat this process until there is only one "remaining" character, in which case it must be the
last one add to our return string. The overall process can be carried out using a few data structures.
Let's look at the operations we want to perform, and see how we can carry them out.

1. Iterate over a list of distinct characters in alphabetical order
   1. This implies collecting a list of distinct characters and storing them in sorted order.
   1. We can build this with a **std::map** or a std::set in O(nlog(n)) time (n being the input length)
1. For each character we iterate over, find its closest index > the index of the last chosen character
   1. We have the index of the last chosen character in `idx`.
   1. If we **map** each character to an ordered list of indices it appears at in the input, we can run binary
      search to find the next-largest index after `idx`.
   1. (See my blog post on [binary search useful variants](https://blog.domfarolino.com/Binary-Search-Useful-Variants/))
1. Now we've found an instance > `idx. We need to see if this instance is <= the last-indices of all remaining
   distinct characters. If so, we know all remaining characters appear _after_ this one, so we choose it
   1. Naively, we can do this by comparing the found index (which is > `idx`) with every other
      character's last index. This will take O(n) time.
   1. However, we can realize we only need to make sure the index we found is <= the smallest of the remaining
      last-indices. We can eagerly build a std::set of last-indices for each distinct character in O(nlog(n))
      time. The set is ordered, so we can query its minimum in O(1) time for a constant comparison.

Note that we can build up all of our data structures in O(nlog(n)) time. For each of the O(n) ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) characters that we'll need to push to our return subsequence string, we'll
need to find the best one, which requires iterating over our sorted list of remaining distinct characters.
The number of iterations in this inner loop can be O(n) as well, giving us O(n<sup>2</sup>) operations.
However, since we're performing binary search for each inner loop iteration, it is more accurately
O(n<sup>2</sup>log(n)).

<sup><sub>**\***(I say O(n), because the number of distinct characters can be at most the size of the input, and therefore is
proportional to O(n))</sub></sup>

This solution beats 100% on leetcode, passing all 65 test cases with a runtime < 0ms.

# Complexity analysis

 - Time complexity: O(n<sup>2</sup>log(n))
 - Space complexity: O(n)

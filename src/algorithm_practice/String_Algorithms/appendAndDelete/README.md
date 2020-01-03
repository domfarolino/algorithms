# Append and Delete

Source:
 - https://www.hackerrank.com/contests/w25/challenges/append-and-delete

This problem may feel a lot like the classic "Edit Distance" problem (see [here][1] and [here][2]),
but the extra constraints imposed by this problem make it much easier, but still interesting. You can
only append a character to the end of the string `s`, or delete a character from the end. Also, deleting
a character from an already-empty string results in a still-empty string. An extra kicker is you have to
see if you can can edit `s` into `t` in **exactly** `k` moves, not _within_ `k` moves.

When I was thinking about this problem, my mind went right to "bounds". That is, there has to be some
easy way we can determine when `k` is obviously not large enough (and can immediately return "No"), and
when `k` is obviously large enough we don't have to do any work (and can immediately return "Yes").

When `k` is greater-than-or-equal the size of the two strings combined, we immediately know the answer is
"Yes", because we can fully delete `s` is, burn any extra moves we have by deleting the empty string, and
rebuild the string to match `t` exactly. Next, if we can compute the exact amount of non-matching characters
between the two strings, we can also immediately determine if `k` is too small to ever be able to overcome the
difference of the two strings. For example:

```
abcdefghijkl
ab
5
```

In the above example, we know we'd have to delete more than `k` characters from `s` to make `t`, so we can
immediately return "No". But how do we actually compute the raw "distance" between the two strings? Well,
remember that the only changes we can make to `s` are at the end of the string; we can not delete any middle
characters, or prepend or insert as well. In this case, we can compute the largest matching substring of `s`
from the beginning. In the above instance, the largest matching substring is `ab`. Therefore, we can compute
the total "distance", or "work needed", as the number of remaining characters in `s` and `t` (i.e.,
the characters of `s` and `t` besides the substring). We can use this distance to help us know whether or not
`k` is insufficient.

Now to the average case. A weird quality of this problem can be seen in the below two examples:

```
In:
abcde
abcd
1

Out:
"Yes"
```

```
In:
abcde
abcd
2

Out:
"No"
```

Just because you have a `k` that is sufficient in one case, does not mean that a larger `k + 1` will
be sufficient too. In fact, many times `k + 1` will not be sufficient, because we have to use _exactly_
that many moves when editing our string. In the last above example, there we can turn `s` into `t` in
one move, but there is no way we can do it in exactly 2, because we can't somehow burn off that last
move. The only time that `k + 1` (or more generally, `k + x`) is guaranteed to be sufficient when `k`
is sufficient, is when `k` >= the size of the two strings combined, because we can burn extra moves on
deleting the emtpy string. Luckily we tackled this case immediately. So the only way `k` can be sufficient
is if `k - distance_between_s_and_t` is an even number. Weird, but makes sense; imagine the total distance
between strings is 5 and `k = 7`. We can use 5 moves to make the strings equal, but now we have two (an even
number) extra! But having an even number of extra moves is always fine, because we can immediately burn 2 moves
buy just appending and immediately deleting. We can do this any number of times we want, but imagine after achieving
equality, we have an odd number of moves. That's a shame, because we can never burn an odd number of moves, and end up
in the same place, meaning we can never re-achieve equality, and must return "No".

[1]: https://leetcode.com/problems/edit-distance/
[2]: https://www.geeksforgeeks.org/edit-distance-dp-5/

## Complexity analysis
 - Time complexity: O(min(|s|, |t|)); matching-substring computation
 - Space complexity: O(min(|s|, |t|)); matching-substring computation

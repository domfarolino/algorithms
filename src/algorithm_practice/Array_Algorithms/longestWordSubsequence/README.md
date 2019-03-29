# Longest Word Subsequence

 - Source: https://techdevguide.withgoogle.com/paths/foundational/find-longest-word-in-dictionary-that-subsequence-of-given-string
 - Related (useful): Binary Search Variants ([blog](https://blog.domfarolino.com/Binary-Search-Useful-Variants/)) ([implementations](https://github.com/domfarolino/algorithms/blob/master/src/algorithm_practice/Searching_And_Sorting/binarySearchClosest/binarySearchClosest.cpp))

This is a former Google interview question, whose description can be found in
the link above. There are several approaches, and in this write-up I cover a
naive approach, and a nice optimization. The first article above has a more
in-depth exposition.

## Naive

The naive solution would be to iterate through each word in the word list,
and just perform some is-a-subsequence check on the given word and the given
string `s`. This subsequence check is relatively simple, and an implementation
can be found in my C++ file.

A small optimization we could do here is maybe sort the given list of words by
the length of each word, such that the longer words appear at the beginning

### Complexity analysis

Let n = size of the given word list, and s = length of the given string.

 - Time complexity: O(n\*s)
 - Space complexity: O(1)

## Optimized Preprocessing

It may be obvious that we cannot do any better than iterating through at least
every word in the given word list. The slowness in the above solution is that
we are iterating through potentially all of the given string `s` for each word,
to determine whether the word is a subsequence or not. Furthermore, the way our
is-a-subsequence check would work, we may iterate through all of `s` even if
`s` is massive compared to the length of the word, which is rather annoying.

The optimization we can make is to preprocess `s` so that we don't have to
iterate through potentially the entire string just to determine whether a given
word is a subsequence or not. Realize that the question of subsequence is a
membership problem. We just need to quickly know if a given letter at index `i`
of the word `w` exists at an index >= `i` in `s`.

We can solve membership-style problems efficiently by maintaining a
map-representation of the given string `s`, `{letter: [all, occurring, indices]}`.
Now, when examining a word `w` in the list of given words, for each character at
index `i`, we can binary search the list given by `map[word[i]]` to determine
whether a value (index) exists in said list, that is greater than the index of the
last-matched value. If so, we keep on keeping on.

----

A subtle improvement would be to sort the given list of words in descending order
by length, so that we're considering the larger words first, however this would
not give us asymptotic improvements, and would actually add a factor of
O(nlog(n)) to our time complexity, though it may potentially be faster in some
situations.

### Complexity analysis

Let n = size of the given word list, and s = length of the given string.
Let k = constant bound of the size of a given word appearing in the word list.

 - Time complexity: O(s + n\*k\*log(s))
 - Space complexity: O(s)

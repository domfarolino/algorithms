# Bold Terms

Write a function that takes in a document in the form of a string, and a list of
search terms. The algorithm should modify the document such that character sequences
matching any of the given terms are wrapped in HTML `<b></b>` tags similar to how a search
engine will behave.

## Assumptions, Clarifications, and Edge Cases

Here are some good assumptions and clarifications to consider:

 - Will we want to only match search terms that are their own word
   (define word)? Or if we have the term `dom` and we have document
   text `dominic` will we want to bol the occurrence of `dom` within
   `dominic`? This is a good question to ask, and the algorithm in this
   repository bolds *any* occurrence of a term.
 - We'll want our passed-in terms list to consist only of
   unique terms so that we don't bold the same term multiple
   times (as many as it appears in the terms list). Making this
   assumption would be convenient, but equally we could make the
   set consist of only unique elements ourselves if we can't make
   this assumption.
 - What should we do if a matching term in the document is already
   surrounded by bold tags? In this case, the tags must have come from
   the original document, as our last assumption makes it clear that we
   will not attempt to bold the same term multiple times. My first thought
   was that if we were creating a real-world algorithm, we might want to check
   if a term has already been bolded before bolding it, as we'd be working with,
   mutating, and re-displaying segments of the document's original HTML (in which
   a term might be bolded). *On second thought*, if we could do a little preprocessing
   (or at least assume some is done for us) and assume we're only dealing with the plaintext
   from the source document, stripped of all HTML markup, we can skip this check and bold terms
   as we wish, as no `<b>` or `</b>` character sequences will ever be present in our document's
   text.
 - What should we do if a search term happens to be a subset of another term, and both are matching
   in the document? For example, given the terms `mini` and `minimum`, should we return:
     - `<b>minimum</b>`
     - `<b><b>mini</b>mum</b>`
     - `<b>mini</b>mum`
  In this case we'll say it doesn't matter however it would be go to look into this if we were
  implementing this in the real world. A good method here would be to process the longest search
  terms first, which would produce the second output above, which is still valid HTML.

## Edge case with possible solutions:

This section is a deeper dive into the real-world edge cases that we may want our algorithm to
cater to. In this trivial interview-style implementation of this algorithm we won't be implementing

### Searching for terms that match characters the algorithm adds

In this algorithm, if we bold some search term (by surrounding it with `<b>` and `</b>`),
and then later search for the terms `<b>` or `</b>`, we'll bold these inserted tag sequences
because it is convenient to treat these inserted sequences as valid document text. In a real
world algorithm however, we'd probably want to ensure we don't bold things we've added to the
document as a side effect of running this algorithm. We want the modifications we're making to
to be purely cosmetic and not contribute to the content of the document.

To address this concern in the real world, we have a few (good?) options:

1. From the given list of search terms, eliminate all terms from the given
   list that match HTML bold tags, or any other HTML tags (if we wish to
   generalize this algorithm). The primary drawback of this method is that
   if the document's plaintext, once stripped of HTML markup, contains text
   like `&lt;b>` or `<b&gt;` in order to render the literal `<b>`, there's no
   way to highlight the rendered document text `<b>` because we can't search for
   `<b>`. Searching for the escaped terms will not work either because the rendered
   counterparts don't match the escaped terms.
2. We could do something similar to what Google seems to do (likely for security), which
   is omit certain characters from search terms that might be utilizing those characters to
   form HTML markup. In this case, searching `<b>` would really bet he same as searching `b`
   as we can remove the `<` and `>`. This allows searching for valid HTML to not result in an
   empty query, so we have the potential of still bolding something useful. Note given our first
   assumption, we assume that the list of terms is unique. This allows for the list to consist of
   the terms `<b>` and `b`. While they are unique, they search for the same thing so if going with
   this solution we'd need to redefine "unique term" to indicate "unique search term" to indicate
   uniqueness is by what the term would actually end up searching for.
3. Warning: This solution is a little messy. If someday we might be adding more than just HTML tags to
   our document, we may not be able to limit users from searching from everything we add (for example if
   we add just general text, our users are often going to want to search for general text). To ensure that
   we don't process or bold text that we've added to a document ourselves, we may want to use a map to keep
   track of which characters in the document string we've added ourselves. This way when we search for the
   occurrence of a term, we can determine whether or not an a given occurrence of that term is a subset of
   text we've added ourselves, or whether it appears in naturally-occurring text. From my perspective it
   would be difficult to update the map to reflect the new positions of the text we've previously added
   once we add more, but this isn't relevant right now, is it :)

## Proposed Solutions

### Naive Solution (implemented)

One solution is to simply for each term, find all occurrences of it in the document,
and before each occurrence, add the characters `<b>`, and after add `</b>`. This can
be done by using `std::string::find` to find an occurrence, performing the aforementioned
operations, and doing the same for future occurrences.

The `std::string::find` method takes an optional second parameter which is an index to start
searching from which we can use to find later occurrences of a term. We can maintain some `findIdx`,
initially `0`, which can keep track of the index from which the current term has been found. Once we
find an occurrence, at say position `x`, we'll want to:

 - Insert `<b>` right before term (at position `findIdx`)
 - Set `findIdx = findIdx + 3` to account for adding three characters behind the occurrence
 - Insert `</b>` right after the term (at position `findIdx + termLength`)
 - Set `findIdx = findIdx + termLength + 4` to start searching for the next term `termLength + 4` positions
   away, or right after the term we've found plus our character additions

It's important to realize that we'd want to generalize our offsets and character additions if we wanted to support
the adding of more than one type of HTML tag in our document.

### Complexity Analysis

Note that we're traversing the entire document `k` times, if there are `k` search terms. This gives us:

Time complexity: `O(n*k)`, if `n` is the length of the document
Space complexity: `O(n)`, since we're returning a new modified copy of the document

### Optimized solution

We could potentially save ourselves from iterating over the document so many times if we were able to perform
the task in one single pass of the document. To do this we'd want to traverse the document with the ability to
match each search term as they come up. In this case we'd probably want to match the longest terms first, so we'd
likely need some way to look ahead. For example, in the document `minimum`, with search terms `m`, and `minimum`, we'd
clearly have a match of `m` right away, but instead of greedily acting on this match right away, it would be nice if we
could save our spot, and keep looking ahead while current string we're looking at matches some part of another, longer
search term. If we match some longer search terms on the way, we can save this information somewhere, but we don't want
to act on a match until we've either matched or failed to match with the longest so-far-matching search term.

The implementation of this would likely be messy and non-trivial, but would produce excellent efficiencies. We might be
able to keep track of the longest so-far-matching search term by using a trie, but I'm just spitballing here.

### Complexity Analysis

Time complexity: `O(n)`
Space complexity: `O(k)`, since we'd need to store our search terms in a new structure capable of the look ahead technique
we previously talked about.

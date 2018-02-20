# Bold Terms

Write a function that takes in a document in the form of a string, and a list of
search terms. The algorithm should modify the document such that character sequences
matching any of the given terms are wrapped in HTML `<b></b>` tags similar to how a search
engine will behave.

## Assumptions, Clarifications, and Edge Cases

Here are some good assumptions and clarifications to consider:

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

## Edge case with possible solutions:

This section is a deeper dive into the real-world edge cases that we may want our algorithm to
cater to. In this trivial interview-style implementation of this algorithm we won't be implementing


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

One solution is to simply for each term, find all occurrences of it in the document,
and before the occurrence add the characters `<b>` after add `</b>`. This can be done
by using std::string::find to find an occurrence, performing the aforementioned
operations, and doing the same for future occurrences. `std::string::find` takes an
optional second parameter which is an index to start searching from which we can use to
find later occurrences of a term. We can maintain some `findIdx` which can keep track of
the index a current term has found, and start start searching

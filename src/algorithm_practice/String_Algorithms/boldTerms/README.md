# Bold Terms

Write a function that takes in a document in the form of a string, and a list of
search terms. The algorithm should modify the document such that character sequences
matching any of the given terms are wrapped in HTML <b></b> tags similar to how a search
engine will behave.

### Some clarifications and edge cases:

 - We'll want our passed-in terms list to consist only of
   unique terms so that we don't double-bold the same term.
   Equally we could make the set unique if we can't make this
   assumption.
 - If a matching term in a document is already surrounded by
   bold tags we're still going to re-bold it. This is because
   if this were actually being implemented we'd likely be dealing
   the text-only content of HTML, so if bold tags exist they are part
   of the document's actual text, not the markup.
   AMENDMENT: Note this is isn't exactly accurate. If we're dealing with
   the actual text there will be

### Edge case with possible solutions:

In this algorithm, if we bold some search term, and then later search for the
terms "<b>" or "</b>", this, for simplicity, can be considered valid text and
we can bold these symbols as well.

In a real-world algorithm we'd probably want to ensure we don't bold
things we've added to the document as a side effect of running this
algorithm, as the modifications we're making to the document should
only be cosmetic. To address this concern in the real world, we have
two good options:
1.) From the given list of search terms, eliminate all terms that match
    HTML bold tags (open/close), or any other HTML tags if we wish to generalize.
    Initially I thought the primary drawback of this solution would be that if a raw
    article's text contains a sequence of characters that matches an HTML tag but is
    meant to be displayed to the user, we'd accidentally skip it, but then it occurred
    to me the only way to display something to the user than an HTML parser would normally
    pick up is to escape special characters, which would make the sequence no longer match
    that of a valid HTML tag.

One solution is to simply for each term, find all occurrences of it
in the document, and before the occurrence add the characters "<b>"
after add "</b>". This can be done by using std::string::find to find
an occurrence, performing the aforementioned operations, and doing the
same for future occurrences. std::string::find takes an optional second
parameter which is an index to start searching from which we can use to
find later occurrences of a term. We can maintain some `findIdx` which can
keep track of the index a current term has found, and start start searching

# Online Election

Source:

 - https://leetcode.com/contest/weekly-contest-103/problems/online-election/
 - https://leetcode.com/problems/online-election/description/

This one is a little bit more of a design question, though not entirely. The reason
I say this is because while it is true we don't get to design the API of our class,
or exactly how we receive our input, since we have to implement a class, we get a lot
of freedom to decide how, if at all, we want to preprocess our data to make queries
speedy later on. Therefore, we have a lot of different approaches to this problem.

Below are some, but first let's cover one oddity in this problem: The fact that we
can be given a time `t` in a query that is not an actual time point we have recorded.
This is really no issue, and just means that if we have the following times vector:
[5, 10, 15, 20], and we're querying the latest result at time `11`, there has been no
change since time `10`, so we'll want to pretend we were given time `10` in the first
place. Essentially, we want to be able to, quite quickly, look up a time in our time
vector, or the next smallest time. Hmm, this sounds like a modified version of binary
search! Go on, I'll give you a minute to read https://blog.domfarolino.com/Binary-Search-Useful-Variants/.

Alright, so now we have a pretty good idea as to how to write a binary search that can
return the index of a value in an array if it exists, and the index of the next smallest
otherwise. The tricky edge case is if we were given a query `t = x`, where x < every value
in the sorted time vector. Normally we'd need to catch this, and return some sort of sentinel
value, but the problem clearly states that this kind of query will never happen, so we won't
need to focus on it 😊.

Now for the approaches. Since we have a lot of freedom in implementation, and can perform
any amount of preprocessing we want really, it would be good to ask some questions to try
and make one option more appealing:
 1. Will we be querying the same set of people/times a lot? How much? If a lot, preprocessing
    would be appealing in hopes that we can minimize each query time in exchange for some
    overhead.
 1. Is the times vector sorted? Yes, and this doesn't have too much of an impact on design.
 1. Will we be given a time query potentially >= every value in the times vector? Yes, and same
    note as above.

Ok, _now_ for Some approaches.

## No preprocessing at all

We can basically ignore the fact that we're in a class, and implement a naive
solution that takes in two vectors, the person and time vectors that is, and
saves them off to the side. Our query function will then have to do all the
work. It'll need to find the appropriate time in the times vector in O(log(n)),
and look at the persons subarray [0, i], where i is the index of the valid time we're
interested in activity up to and including. We'll need a count of each candidate we see
in this subarray, so we can return the winner up to this point.

To store the counts of each candidate vote up to this point in our subarray, we can create
a map. Populating this map with candidates and their respective vote counts will be O(n) with
respect to both time and space. We'll then need to iterate through the map, and choose the key
whose value is the highest, also O(n) time. A small optimization we could make is to keep track
of the maximum key as we insert candidates into the map, but we're still bounded by the O(n)
subarray traversal for each query.

### Complexity analysis

 - Time complexity: O(n) per query
 - Space complexity: O(n) (copies of the original input, as well as the candidate map)

## Preprocessing

With some preprocessing, we can get our queries down to O(log(n)). The realization we need to
make is that we can extend the logic from the previous section to each possible time query up
front. If we have the candidate count and max candidate for a given query, and thus the winning
candidate at a given position, we can easily find the winning candidate for the next position,
by consuming the next candidate, incrementing their vote count, and seeing if it overtakes or
is equal to our set-aside max candidate.

We can store each of these winning candidates at each position in a separate query array the same
size of the candidate person array, and query it in O(1) time after we get our O(log(n)) time. The
time index we care about will be the same index of the value we want in our query array of course.
There are some more minor optimizations, but as George Costanza says, "that's the gist of it!".

### Complexity analysis

 - Time complexity: O(log(n)) per query, O(n) preprocessing hit up front
 - Space complexity O(n) (both)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

// Source: https://leetcode.com/contest/weekly-contest-81/problems/shortest-distance-to-a-character/

/**
 * Shortest distance to character
 * Lovely problem. It's important to seek clarification to understand
 * that:
 *  - The character `c` may appear more than once in the input string
 *  - It will appeart at least once in the input string, guaranteed
 *  - The input string and `c` will always consist of lower-case letters
 *
 * The problem essentially boils down to, for each character in the input
 * string, needing to know the nearest instance of the `c` to it. This data
 * is what we'll populate our return vector with. We could do this rather simply
 * for each character of the input string, iterating through the entirety of the input
 * string and keeping track of the closest index of `c` we find. There are some possible
 * optimizations for the solution, though they only take effect in the best cases. So this
 * solution is rather simple, and inefficient.
 * Complexity analysis:
 * Time complexity: O(n^2)
 * Space complexity: O(n)
 *
 * It would be nice to see if we could build our return vector as we iterate through the input
 * string in one pass. What we could do is run out ahead and find the first instance of `c`, and
 * from here, start iterating through the input string, recording the distance from string[i] to
 * the instance of `c` we know about. Consider the following case:
 * in ==> "aiaaaaaai", "i"
 * With this input ^, we'd want to produce [1, 0, 1, 2, 3, 3, 2, 1, 0], however you can imagine after
 * we find the first instance of "i" and before we find the second instance, our vector would look something
 * like this [1, 0, 1, 2, 3, 4, 5, 6, x]. Then once we come across the final character "i", we'd have to say
 * "Hey, we came across another instance of 'i', we need to go back and fix values in the array that may have been
 * compared to the _other, previous_ instance of "i", in case _this_ instance of "i" is closer! We could go back, keeping
 * track of how far we are away from this instance of "i", correcting our previous assumptions until we don't need to anymore.
 * (You can image the conditions in which we'd stop "correcting"). This is annoying, though it works so long as we keep our `c`
 * index counter up-to-date whenever we run across another instance of `c`.
 * Instead, we could take advantage of the opportunity that we have when we iterate across instances of "i" that we jumped out and
 * found ahead-of-time, to find the _next_ instance. Then for all characters in between the two known instances, we can make intelligent
 * correct-the-first-time comparisons between the two. This should only be as hard as introducing another variable, to give us `firstIdx`
 * and `secondIdx`. These variables will represent the indices of `c` that invariably come before and after characters we're looking at. Then
 * as we're iterating through characters and come across another instance of `c`, we'll have to set `firstIdx = secondIdx`, and go out and find
 * the next `secondIdx`. Now for the edge cases:
 * - What about characters before the first instance of `c`
 * - What about characters after the last instance of `c`
 *
 * When we come across the last instance of `c`, we try and fetch the next instance. When We run off the end and can't find anything, we should mark
 * `secondIdx` as some sentinel value (perhaps INT_MAX) so we know not to use it for comparisons. The same goes for characters before the first instance
 * of `c`. We can set start out by setting `firstIdx = INT_MAX` & `secondIdx` = the index of the first instance of `c`. Then later when we come across the
 * first instance of `c`, we'd do the `firstIdx = secondIdx; fetch the next secondIdx` as normal and continue.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

std::vector<int> shortestToChar(const std::string& s, char c) {
  std::vector<int> returnVec(s.length(), 0);
  int firstIdx = INT_MAX, secondIdx = 0;

  // Find first instance of `c`
  int i = 0;
  while (i < s.length() && s[i] != c) i++;
  secondIdx = i++;

  for (int j = 0; j < s.length(); ++j) {
    if (s[j] == c) {
      firstIdx = secondIdx;

      // Run off and find the next instance of `c`, if it exists
      while (i < s.length() && s[i] != c) ++i;
      if (i == s.length()) i = INT_MAX;
      secondIdx = i++;
      continue;
    }

    if (firstIdx == INT_MAX) {
      returnVec[j] = secondIdx - j;
    } else if (secondIdx == INT_MAX) {
      returnVec[j] = j - firstIdx;
    } else {
      returnVec[j] = std::min(secondIdx - j, j - firstIdx);
    }
  }

  return returnVec;
}

int main() {
  std::string input = "aiaaaaaaaai";
  std::vector<int> resultVec = shortestToChar(input, 'i');

  std::cout << "[";
  for (int i = 0; i < resultVec.size(); ++i) {
    std::cout << resultVec[i] << ", ";
  }
  std::cout << "]" << std::endl;

  return 0;
}

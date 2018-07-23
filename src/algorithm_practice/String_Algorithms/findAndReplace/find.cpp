#include <iostream>
#include <string>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-84/problems/find-and-replace-in-string/

/**
 * Find and replace in string
 * Cool problem. What makes this problem interesting
 * is the fact that all of the finds occurr on the original
 * string ("finding" a source string only considers characters
 * in the original input string), with the edits taking place on
 * the updated edited string. This may sound problematic, but we're
 * given a guarantee that the finds/edits are mutually exclusive, and
 * thus it is safe for them to happen simultaneously. It should also be
 * noted that there are some edge cases with "find". We are guaranteed by
 * the description that all indices will be valid indices in the original
 * string, however it seems possible to have a source string to find that is
 * arbitrarily large. However, some examples demonstrating the mutual exclusiveness
 * of the find/edits are below:
 *
 * 1.) Example of finds not affected by other edits:
 * input = "abcd", indices = [0, 1], sources = ["a", "xb"], targets = ["xx", ""]
 * outputstring = "xxbcd"; because the second find/edit cannot find "xb" at index 1,
 * because in the original string, input[1] == "b". So the only thing that matters are
 * the original indices.
 * 2.) Example of edits being mutually exclusive (not overlapping original characters):
 * It is important to confirm this scenario/example below, because if this guarantee did
 * not hold, it would not be possible for the find/edits to be mutually exclusive and happen
 * simultaneously and seamlessly.
 * input = "ab", indices = [0, 1], sources = ["ab", "b"], targets = ["test", "xyz"]
 * This would not be valid input because the sources overlap. We'd be replacing "ab"
 * with something, and then trying to replace "b" with something. While "b" would exist
 * in the original input string, "b" is effectively being "replaced" in the final string
 * instead of just being shifted around, so it cannot appear in a later find/edit that may
 * tamper with it. With this, we can guarantee that the length of all combined |source| strings
 * is <= the length of the original input string, and sources contains mutually exclusive segments
 * of the original input string.
 *
 * The first idea I had implementing this was that we could do this by modifying the original string,
 * and since characters after the edit could be shifted backwards or forward, we'd want to maintain some
 * map, mapping each original input character to its index. Whenever we made an edit, we'd then adjust all
 * map[i] where i > the index we made the edit, so we now where the original characters now exist. For example
 * given input = "abcd", indices = [1], sources = ["b"], targets = ["eee"], we'd maintain an index map, initially
 * {"a": 0, "b": 1, "c": 2, "d": 3}. We'd make the change "b" => "eee", giving us a new string "aeeecd", and adjust
 * map["c"] = 4, map["d"] = 5, so for future edits we can keep track of where the "new" find indices are. This sounds
 * ok, and the map could actually be an array of indices, where entry 0 would correspond to "a" and so on, however the
 * task of updating _all_ "later" indices given some edit, and inserting potentially large amounts of potentially long
 * strings in the middle of the input string doesn't seem terribly reasonable.
 *
 * I thought that this could be a lot easier if we could ensure that the list of indices was reverse-sorted (as well as the
 * corresponding sources and targets vectors), or at least do some pre-processing to maket his happen. The idea is that if we
 * did all later-appearing edits first (going from high indices => lower), we wouldn't need to shift any mapped indices. Still,
 * we're inserting a lot of substrings which is expensive, and there should be a better way than building the string like this.
 *
 * Instead of trying to concat all of the finds/edits on the fly sequentially with the original string, my next idea was that
 * we could build out the individual portions of the string independently, and then concat them together at the very end to produce
 * a final returns string. The idea is that we'd maintain a list of substrings, initially ["a", "b", "c", "d"] if the input string was
 * "abcd". For each edit, if the "find" succeeded given a |source|, |i|, and the original string, we'd modify modify array[i], which
 * corresponds initially to original[i], and set array[i] = target. At this point we just need to clear out the remaining entries in
 * |arr| that would have been included in the "find". For example; input = "abcd", indices = [0], sources = ["abc"], targets = ["wxyz"].
 * The |arr| would initially be ["a", "b", "c", "d"]. We'd perform find(input, 0, "abc"), which would succeed, and we'd then we'd set
 * arr[0] = "wxyz" (target). With the array looking like ["wxyz", "b", "c", "d"], we have to clear out the other |sourceLength - 1| strings
 * in |arr| that correspond to characters included in the "find". We'd set "b" and "c" = "" in this case. Finally we could just return a concat
 * of all substrings in |arr| as the final string!
 * This is good; there are some slightly simpler ways of doing this, but this is the general idea.
 *
 * Complexity analysis:
 * Time complexity: O(n); |n| = length of final string
 * Space complexity: O(n); |n| = length of final string
 */

// Wrote this instead of using std::string::find, because if std::string::find can't find the
// needle at position i, it will look through the rest of the string. That is not necessary, so
// this is more efficient. There might be a way to limit std::string::find to search through only
// a specific portion of the string, but either way...
bool findInStringAtIndex(const std::string& haystack, int index, const std::string& needle) {
  // At this point, |index| is guaranteed to be within |haystack|
  // Check to see if what we're looking for runs off the end of haystack (is too long)
  if (needle.length() > haystack.length() - index)
    return false;

  // At this point we can search for |needle| in |haystack| at index |index| and guarantee
  // to not run off the end of |haystack| doing so
  for (int i = index; i < index + needle.length(); ++i) {
    if (haystack[i] != needle[i - index])
      return false;
  }

  return true;
}

std::string findAndReplaceString(const std::string& input, const std::vector<int>& indices, const std::vector<std::string>& sources, const std::vector<std::string>& targets) {
  std::string returnString;
  int index;
  std::vector<std::string> stringMap(input.length());

  // Build initial string map
  for (int i = 0; i < input.length(); ++i) stringMap[i] += input[i];

  for (int i = 0; i < indices.size(); ++i) {
    index = indices[i];
    if (!findInStringAtIndex(input, index, sources[i])) continue;
    stringMap[index] = targets[i];

    for (int j = 0; j < sources[i].length() - 1; ++j) {
      stringMap[index + 1 + j] = "";
    }
  }

  for (int i = 0; i < stringMap.size(); ++i) returnString += stringMap[i];
  return returnString;
}

int main() {
  std::string input = "abcd";
  std::vector<int> indices = {0, 1, 2, 3};
  std::vector<std::string> sources = {"a", "b", "e", "d"};
  std::vector<std::string> targets = {"eee", "ffff", "xyz", ""};

  // Expected resulting string = "eeeffff"
  std::string result = findAndReplaceString(input, indices, sources, targets);
  std::cout << result << std::endl;
  return 0;
}

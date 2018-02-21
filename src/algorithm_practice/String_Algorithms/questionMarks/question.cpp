#include <iostream>
#include <string>
#include <climits>

// Source: https://coderbyte.com/editor/guest:Questions%20Marks:Cpp

/**
 * Question Marks
 * Write a function that takes in a string and returns
 * a stringified boolean ("true" or "false"). The boolean
 * should indicate whether or not between every pair of single
 * digit numbers in the string that add to 10, there are exactly
 * three question marks. The question marks do not have to be consecutive.
 * It's always wise to come up with a few different solutions, discuss their
 * performance and possibly implementation, and then figure out which one to
 * go with.
 *
 * 1.) The naive approach that is not the most optimized but would
 * easily get us the right answer is to have a vector of pairs, where
 * each pair consists of the indices of values that add to 10. For example
 * give then following input string "4xx6xx4xx1x9xx5xx5x", our vector would
 * look like [[0, 3], [3, 6], [9, 11], [15, 17]]. Then for each pair in our
 * vector we could iterate through the width of the pair and count the number
 * of ?s. If count != 3 at any point, we return false. If we get to the end without
 * returning false, we return true.
 *
 * Time complexity: O(n) (doing at most two passes)
 * Space complexity: O(n) (fully-numeric string)
 *
 * 2.) A slight optimization on this problem would be to not store each pair and
 * wait to iterate over its width, but instead keep a couple variables aside for
 * the latest pair, and iterate performing the ? count immediately. Again if we
 * get to the end without returning false we return true. Not storing all of the
 * arrays and waiting to iterate is a space optimization.
 *
 * Time complexity: O(n) (see above)
 * Space complexity: O(1)
 *
 * 3.) A slight optimization on our time would be to maintain the ? count as we
 * build each pair, so we don't have to go back and re-iterate through the characters
 * we've already passed. Once we get to the second number in our pair, we just check
 * to see if the first and second numbers sum to 10. If they do, then our ? count is
 * relevant and we check it (and maybe return false). If they do not sum to 10, we can
 * disregard the count, and continue to the next pair. This brings us down to a single
 * pass over the string, which is a time optimization though our asymptotic complexity
 * doesn't change.
 *
 * Time complexity: O(n) (single pass)
 * Space complexity: O(1)
 */

/**
 * Implementation #3, discussed above.
 */
std::string questionMarks(const std::string& input) {
  int firstNum = INT_MAX, qCount = 0;
  bool atLeastOnePair = false; // this is for the requirement that if no pair = 10, return false anyways
  int charAsInt;

  for (int i = 0; i < input.size(); ++i) {
    charAsInt = (int)(input[i] - '0');
    if (firstNum == INT_MAX) {
      // Looking for first # in our pair
      if (charAsInt >= 0 && charAsInt <= '9') firstNum = charAsInt;
    } else {
      // Looking for second # in our pair
      if (charAsInt >= 0 && charAsInt <= 9) {
        // We have our second number!
        if (firstNum + charAsInt == 10) {
          atLeastOnePair = true;
          if (qCount != 3) return "false";
        }

        // Reset firstNum and qCount for next pair
        firstNum = charAsInt;
        qCount = 0;
      } else if (input[i] == '?') qCount++;
    }
  }

  return (atLeastOnePair) ? "true" : "false";
}

int main() {
  std::string test1 = "cc?7??sss?3rr1??????5", test2 = "aa6?9", test3 = "9???1???9??1???9";
  std::cout << questionMarks(test1) << std::endl;
  std::cout << questionMarks(test2) << std::endl;
  std::cout << questionMarks(test3) << std::endl;
  return 0;
}

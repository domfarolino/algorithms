#include <iostream>
#include <string>

// Source: https://leetcode.com/contest/weekly-contest-82/problems/goat-latin/

/**
 * Goat Latin
 * Good string agility problem. Important to ask clarifying questions for this.
 * Ensure that you know an input string only has a _single_ space between words,
 * and that it will never start or end with a space. The basic steps for this problem
 * that I came up with were
 * 1.) Init a return string
 * 2.) For each word in the input string
 *   - Pull a copy of the word out
 *   - Optionally move the first letter to the end
 *   - Add "ma"
 *   - Add wc * "a", where wc is the count of words we've seen so far
 *   - Append new word to the return string
 *   - Continue to next word
 *
 * An alternative solution to this, if we didn't want to return a brand new string, is
 * to modify the original one in-place. This is more complicated, and requires a lot of
 * inserts for each word, which can be quite expensive, thus would have O(n^2) time complexity.
 *
 * Finding "all words" is a task in itself that can be performed in a number of ways. We
 * can either do this all up front, and place each word into a vector and iterate through
 * the vector, or we can do it on-the-fly. I prefer doing this on-the-fly to preserve space,
 * and it shouldn't be that difficult really. To find each word we can do an inch-worm approach
 * where we have two index variables, one representing the start of a word, and the other representing
 * the end of a word or a word boundary. We keep incrementing the end index variable until we hit a word
 * boundary, which is either a space, or past the end of the string. The word in question ranges from
 * [startWord, endWord - 1] inclusive. Once we have this working, we just carry out the rest of the steps
 * in the above list, which is fairly trivial. To reset the index variables, we can just increment the end
 * index variable until it hits non-whitespace, and set the start index variable to it. Luckily for us in this
 * problem, we know that there is only one character between each word.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n) // we're creating a whole new string
 */

bool notVowel(char c) {
  c = std::tolower(c);
  return c != 'a' &&
         c != 'e' &&
         c != 'i' &&
         c != 'o' &&
         c != 'u';
}

std::string toGoatLatin(const std::string& s) {
  std::string returnString, tmp;
  if (!s.size()) return returnString; // see if we can remove this!
  int wordStart = 0, wordEnd = 0, count = 0;

  while (wordEnd <= s.length()) {
    if (wordEnd != s.length() && s[wordEnd] != ' ') {
      wordEnd++;
      continue;
    }

    // Reached a word boundary (word: [wordStart, wordEnd - 1])
    count++;
    if (count > 1) returnString.append(" ");
    tmp = s.substr(wordStart, wordEnd - wordStart /* length */);
    if (notVowel(tmp[0])) {
      tmp += tmp[0];
      tmp.erase(0, 1);
    }
    tmp.append("ma");
    tmp.append(count, 'a');
    returnString.append(tmp);

    wordEnd++;
    wordStart = wordEnd;
  }

  return returnString;
}

int main() {
  int n;
  std::string input;
  std::cin >> n;
  std::cin.get();

  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, input);
    std::cout << toGoatLatin(input) << std::endl;
    input.clear();
  }

  return 0;
}

#include <iostream>

/**
 * This algorithm counts the number of times
 * some substring appears in a string. It utilizes
 * string::find to keep updating the position we're
 * starting from in the string, to perform the find
 * operation. We continue until we cannot find the substring
 * after the point where we found its other occurrences.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

int numTimesExists(const std::string& haystack, const std::string& needle) {
  int count = 0;
  int pos = haystack.find(needle, 0);

  while (pos != -1) {
    pos = haystack.find(needle, pos + needle.size());
    count++;
  }

  return count;
}

int main() {
  std::string needle;
  std::string haystack;

  std::cout << "Input the haystack (string to search within)" << std::endl;
  std::cin >> haystack;
  std::cout << "Input the needle (search substring)" << std::endl;
  std::cin >> needle;

  std::cout << numTimesExists(haystack, needle) << std::endl;
  return 0;
}

#include <iostream>

using namespace std;

// Source: https://leetcode.com/contest/9/problems/reconstruct-original-digits-from-english/

/**
 * Reconstruct Original Digits from English
 * Given a non-empty string containing an out-of-order
 * English representation of digits 0-9, output the digits
 * in ascending order. This problem is kind of neat. Essentially
 * in some giant scrambled string of letters we want to see if the
 * the characters that make up "zero", "one", "two", "three", ... exist
 * in the string. If so we want to remove those characters from the string
 * add the integer representation of the word we found to our ouput string.
 * Notice that in the problem desctiption we must output the characters we
 * find in ascending order. This made me think at first we want to look for
 * and remove all "zero" instances in our string, and then move onto "one"
 * and so on. This is actually not the right way to do this because given the
 * string "zeroonetwothreefourfivesixseveneightnine" you would actually return
 * 01112333...or something like this. The point is that you'd find more instances
 * of "one" than there really are because you'd be taking letters away from the
 * other english representations of numbers. For examples you'd find "one" from
 * the letters "fourseven". This suggests you need to search for some numbers with
 * more strict letter requirements than others. This means you could either find the
 * numbers out of order and sort your output string or just have 10 output strings
 * containing the characters for each number, and then just add them together in the
 * right order.
 *
 * When it comes to actually finding and removing characters from the input string it
 * makes much more sense to use something like a map instead of mutating the original
 * string because many erase operations in a large string will be very inefficient. A
 * map means we'd have to do a little pre-processing to insert all the string's chars
 * into the map, however we get O(1) inserts and removals (removals consist of decrementing
 * the value associated with a given character).
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

class Solution {
public:
  //unordered_map<char, long> inputMap;
  long inputMap[26];

  Solution(string& inputString) {
    initMap(inputString);
  }

  bool findAndRemove(string haystack) {
    for (int i = 0; i < haystack.length(); ++i) {
      if (inputMap[haystack[i] - 97] == 0) return false;
    }

    for (int i = 0; i < haystack.length(); ++i) {
      inputMap[haystack[i] - 97]--;
    }

    return true;
  }

  void initMap(string& s) {
    for (int i = 0; i < 26; ++i) {
      inputMap[i] = 0;
    }

    for (long i = 0; i < s.length(); ++i) {
      inputMap[s[i] - 97]++;
    }
  }

  string originalDigits() {
    string out0 = "",
      out1 = "",
      out2 = "",
      out3 = "",
      out4 = "",
      out5 = "",
      out6 = "",
      out7 = "",
      out8 = "",
      out9 = "";

    // Some order of searching for nums that works
    while (findAndRemove("eight")) out8 += "8";
    while (findAndRemove("six"))   out6 += "6";
    while (findAndRemove("seven")) out7 += "7";
    while (findAndRemove("four"))  out4 += "4";
    while (findAndRemove("five"))  out5 += "5";
    while (findAndRemove("three")) out3 += "3";
    while (findAndRemove("two"))   out2 += "2";
    while (findAndRemove("nine"))  out9 += "9";
    while (findAndRemove("zero"))  out0 += "0";
    while (findAndRemove("one"))   out1 += "1";

    return out0 + out1 + out2 + out3 + out4 + out5 + out6 + out7 + out8 + out9;
  }
};

int main() {
  string inputString;
  cin >> inputString;
  Solution sol(inputString);
  cout << sol.originalDigits();
  return 0;
}

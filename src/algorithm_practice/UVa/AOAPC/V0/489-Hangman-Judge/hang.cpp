#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=430

/**
 * Hangman Judge
 * Solution documentation needed
 */

int firstOccurrence(const string& haystack, int low, int high, char needle) {
  int mid = (low+high)/2;

  while (low <= high) {
    mid = (low+high)/2;

    if (haystack[mid] < needle) {
      low = mid+1;
    } else if (haystack[mid] > needle) {
      high = mid-1;
    } else {
      int farthestLeft = firstOccurrence(haystack, low, mid-1, needle);
      if (farthestLeft != -1) mid = farthestLeft;
      break;
    }

  }

  return (haystack[mid] == needle) ? mid : -1;
}

int lastOccurrence(const string& haystack, int low, int high, char needle) {
  int mid = (low+high)/2;

  while (low <= high) {
    mid = (low+high)/2;

    if (haystack[mid] < needle) {
      low = mid+1;
    } else if (haystack[mid] > needle) {
      high = mid-1;
    } else {
      int farthestRight = lastOccurrence(haystack, mid+1, high, needle);
      if (farthestRight != -1) mid = farthestRight;
      break;
    }

  }

  return (haystack[mid] == needle) ? mid : -1;
}

int numOccurrences(const string& haystack, char needle) {
  int first = firstOccurrence(haystack, 0, haystack.size()-1, needle);

  if (first == -1) return first;

  int last = lastOccurrence(haystack, 0, haystack.size()-1, needle);

  return last-first+1;
}

int main() {
  int round;
  string input, guesses;
  int wrongGuesses, rightGuesses;
  int chars[256] = {0};

  while (cin >> round && round != -1) {
    wrongGuesses = 0, rightGuesses = 0;
    cin >> input >> guesses;

    sort(input.begin(), input.end());

    /**
     * For all unique guesses, either increment rightGuesses by numOfOccurences
     * or increment wrongGuesses by 1. If wrongGuesses every = 7 or rightGuesses
     * ever = input.length() stop
     */
    int i = 0;
    int numOccur = 0;
    while (i < guesses.size() && rightGuesses < input.length() && wrongGuesses < 7) {

      // Only guess unique
      if (!chars[guesses[i]]) {
        numOccur = numOccurrences(input, guesses[i]);
        if (numOccur != -1) rightGuesses += numOccur;
        else wrongGuesses++;
      }

      chars[guesses[i]]++;
      ++i;
    }

    for (int j = 0; j < guesses.length(); ++j) chars[guesses[j]] = 0;

    cout << "Round " << round << endl;
    if (rightGuesses < input.length() && wrongGuesses < 7) cout << "You chickened out." << endl;
    else if (rightGuesses == input.length()) cout << "You win." << endl;
    else if (wrongGuesses == 7) cout << "You lose." << endl;
  }

  return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=94&page=show_problem&problem=431

/**
 * Rotating Sentences
 * Cool problem that sounds harder
 * than it is. Basically we want to maintain
 * some vector of all of the sentences we're given.
 * We want to print some character from each of the
 * sentences in the vector n times, where n is the
 * length of the longest string. What happens when we
 * need to print the 20th character of a string that only
 * has 10? In this case we do a quick boundary check, and
 * print a single space instead. Since we're rotating the
 * sentences 90 degrees, we need to start printing characters
 * from the last sentence first and make our way backwards for
 * every character we have to print. Once all that is worked out
 * the coding is fairly straight forward.
 */

int main() {
  vector<string> sentences;
  sentences.reserve(100);
  string sentence;
  int maxLen = INT_MIN;

  while (getline(cin, sentence)) {
    sentences.push_back(sentence);
    maxLen = max(maxLen, int(sentence.length()));
  }

  for (int i = 0; i < maxLen; ++i) {

    for (int j = sentences.size()-1; j >= 0; --j) {
      if (i < sentences[j].length()) cout << sentences[j][i];
      else cout << " ";
    }

    cout << endl;
  
  }
  
  return 0;
}
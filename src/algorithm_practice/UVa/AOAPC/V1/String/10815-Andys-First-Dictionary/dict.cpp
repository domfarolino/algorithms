#include <iostream>
#include <string>
#include <set>

using namespace std;

/**
 * Andy's First Dictionary
 * Theory and coding complexity of this algorithm
 * are both relatively simple. We basically want to
 * read in a large string of ASCII text and collect each
 * alphabetic word one by one. Since each word is delimited
 * by non-alphabetic characters, we can keep a string to store
 * each word in and once we come across some delimiting character
 * we can do something with the word collected in our string, empty
 * it and continue. Each word we get we want to store and return in
 * sorted order. Utilizing the STL provides us with std::set which is a
 * good choice because unlike an std::unordered_set, we can iterate over it
 * in sorted order. After we collect all of our words we want to iterate over
 * the std::set and print each value in sorted order.
 *
 * Complexity Analysis:
 *
 * Every insertion into std::set costs O(log(n)), making all insertions cost
 * about O(nlog(n)). We can iterate over each value in a non-destructive fashion
 * in O(n).
 * Time complexity: O(nlog(n) + n) = O(nlog(n))
 * Space complexity: O(n) - as we must store all of the words in the string
 *
 * We could also use a vector to hold all of the strings, and then sort it in O(nlog(n)). The
 * iteration over each value in sorted order will be O(n) as it is when using std::set. Iteration
 * in this method is non-destructive.
 * Time complexity: O(nlog(n) + n) = O(nlog(n))
 * Space complexity: O(n) - as we must store all of the words in the string
 *
 * We could also utilize a min heap. Every insertion into a min heap costs O(log(n)), making
 * all insertions cost about O(nlog(n)). To print each value in min heap we must destroy the heap.
 * Each removal from a min heap costs O(log(n)) making the total destruction of the heap cost about
 * O(nlog(n)).
 * Time complexity: O(2nlog(n)) = O(nlog(n))
 * Space complexity: O(n) - as we must store all of the words in the string
 */

void lower(char& inputChar) {
  if (inputChar >= 'A' && inputChar <= 'Z') inputChar += 32;
}

int main() {
  char test;
  string word = "";
  set<string> set;

  cin.get(test);
  lower(test);

  while (test) {
    if (test >= 'a' && test <= 'z') word += test;
    else {
      if (word.length()) {
        set.insert(word);
        word = "";
      }
    }

    if (!cin.get(test)) break;
    lower(test);
  }

  // Iterate over the entire map in sorted order
  std::set<string>::iterator iter = set.begin();
  while (iter != set.end()) {
    cout << *iter << endl;
    iter++;
  }

  return 0;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

// Source: Pramp

/**
 * This is a really great problem to learn many different things IMO.
 * It is a very data structure and algorithm intensive problem for how
 * simple the actual task is. The actual task is: Given a string representing
 * a document, return a vector of vectors, where each inner vector is of length
 * 2, and of format: ["<word>", "<#ofOccurrences>"], and the outer vector is sorted
 * in descending order by the number of occurrences. Words with the same number of
 * occurrences should appear in the relative order in which they appeared in the original
 * document. Words are considered space-separated strings. If punctuation appears in the
 * middle of a word, ignore it. For example "dom.farolino" is the single word "domfarolino".
 * We can consider anything other than whitespace and alphanumeric characters, "punctuation".
 * Also, words (and therefore the entire document really), should be seen as case-insensitive.
 * You should definitely go through some examples of this problem before moving forward.
 *
 * There are several parts to this problem:
 *  1.) Word parsing/tokenization
 *      In order to get a list of words out of the document string, we can do this in one pass
 *      by keeping a temporary string off to the side, and fill the string with a word. When we
 *      see our delimiter, we can push the word to a list of strings or something. This is pretty
 *      simple preprocessing.
 *  2.) Word occurrence counting
 *      With a list of words in hand, we can maintain a map whose <k, v> = <word, #ofOccurrences>.
 *      This can trivially be built by iterating through a list of strings, and incrementing the
 *      occurrence count we maintain for each word. This is a great intermediate data structure to
 *      have on hand right now, but there are two ways in which it is not sufficient for unpacking
 *      and returning:
 *        1.) Maps in C++, even unordered ones, do not retain insertion order, so if two words in
 *            our map have the same occurrence count, we just lost their relative order unfortunately.
 *            If we want to maintain relative order alongside our map, which we need, we can have a vector
 *            of strings that we maintain alongside, and when we come across a word that _does not_ appear
 *            in the map, we can not only add it to the map with occurrence count 1, but also add it to the
 *            end of the vector/queue that we're maintaining. This gives us insertion order and occurrence count.
 *        2.) The map is not sorted by value, which is what matters to us. We can take care of this later though.
 *  3.) Sorting a vector of words and their occurrences, in descending order by their occurrence count
 *      We can unpack our map into a vector of the exact same format that we'd like to return, however it will
 *      be unsorted by occurrence count (map entry value). This is fine though, because we can write a custom
 *      comparator for the outer vector, and sort it with a built-in. We that all of the vectors in our unsorted
 *      vector exist in the relative order that they appear in the document. We have to make sure that our sorting
 *      algorithm maintains this relative order among words with equal occurrence counts. In other words:
 *      [["apple", "80"], ["dom", "2"], ["farolino, "2"], ["donkey", "1"]] becomes:
 *      [["donkey", "1"], ["dom", "2"], ["farolino, "2"], ["apple", "80"]] after sorting, and those middle elements
 *      are left in the same order. Turns out that std::sort is not stable by default :(. However, to our chagrin,
 *      std::stable_sort exists, which is of course stable by default, and _often_ is still O(nlog(n)) in terms of
 *      time complexity.
 *
 * Complexity analysis
 * Time complexity: O(n) + O(mlog(m)) (iterating over the initial string, and sorting the amount of unique words)
 * Space complexity: O(m) (the map, insertion order vector, and return vector)
 */

void toLower(std::string& document) {
  for (char& c: document) c = std::tolower(c);
}

std::vector<std::vector<std::string>> unsortedWordsAndCounts(std::string document) {
  std::vector<std::vector<std::string>> returnVec;
  std::vector<std::string> insertionOrder;
  std::unordered_map<std::string, int> countMap;
  toLower(document);
  std::string tmpStr;

  for (int i = 0; i < document.size(); ++i) {
    // Alpha
    if (std::isalpha(document[i]))
      tmpStr += document[i];
    else if (std::isspace(document[i])) { // Whitespace
      if (!tmpStr.size()) continue;
      if (countMap.find(tmpStr) == countMap.end())
        insertionOrder.push_back(tmpStr);
      countMap[tmpStr]++;
      tmpStr = "";
    }
  }

  if (tmpStr.size()) {
    if (countMap.find(tmpStr) == countMap.end())
      insertionOrder.push_back(tmpStr);
    countMap[tmpStr]++;
  }

  std::vector<std::string> tmpVec(2, "");
  for (std::string uniqueStr: insertionOrder) {
    tmpVec[0] = uniqueStr;
    tmpVec[1] = std::to_string(countMap[uniqueStr]);
    returnVec.push_back(tmpVec);
  }

  return returnVec;
}

std::vector<std::vector<std::string>> wordCountEngine(const std::string& document) {
  std::vector<std::vector<std::string>> returnVec = unsortedWordsAndCounts(document);
  std::stable_sort(returnVec.begin(), returnVec.end(), [](const std::vector<std::string>& a, const std::vector<std::string>&b) {return stoi(a[1]) > stoi(b[1]);});
  return returnVec;
}

int main() {
  std::string document = "Practice makes perfect. you'll only get Perfect by practice. just practice!";
  std::vector<std::vector<std::string>> rV = wordCountEngine(document);

  std::cout << "Test 1:" << std::endl;
  for (auto& vec : rV) {
    std::cout << vec[0] << ": " << vec[1] << std::endl;
  }

  document = "z y x p o n m c b a";
  rV = wordCountEngine(document);

  std::cout << std::endl << "Test 2:" << std::endl;
  for (auto& vec : rV) {
    std::cout << vec[0] << ": " << vec[1] << std::endl;
  }

  return 0;
}

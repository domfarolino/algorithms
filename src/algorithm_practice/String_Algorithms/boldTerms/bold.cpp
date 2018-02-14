#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

// Source: ---

/**
 * For description and complexity analysis see: README.md
 */

std::string boldTerms(std::string doc, const std::vector<std::string>& terms) {
  std::unordered_set<std::string> termSet(terms.begin(), terms.end());
  int foundIdx;

  for (std::unordered_set<std::string>::const_iterator term = termSet.begin(); term != termSet.end(); term++) {
    foundIdx = 0;
    while ((foundIdx = doc.find(*term, foundIdx)) != std::string::npos) {
      doc.insert(foundIdx, "<b>");
      foundIdx += 3;
      doc.insert(foundIdx + (*term).size(), "</b>");
      foundIdx += (*term).size() + 4;
    }
  }

  return doc;
}

int main() {
  int numTests, numTerms;
  std::string doc, tmpTerm;
  std::vector<std::string> terms;

  std::cin >> numTests;
  for (int i = 0; i < numTests; i++) {
    std::cin >> numTerms;
    std::cin.ignore();
    std::getline(std::cin, doc);

    // Collect all of our search terms
    for (int j = 0; j < numTerms; j++) {
      std::cin >> tmpTerm;
      terms.push_back(tmpTerm);
    }

    std::cout << boldTerms(doc, terms) << std::endl;
    terms.clear();
  }

  return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits> // INT_MIN
#include <utility> // std::pair

using namespace std;

// Source: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=96&page=show_problem&problem=350

/**
 * 409 - Excuses Excuses!
 * The theory behind the algorithm is rather simple.
 * Basically what we need to do is for each set, for each
 * excuse iterate through the entire keywords vector and see
 * how many times each excuse keyword appears in the excuse. Maintain
 * a running total variable that keeps track of how many excuses total
 * appear in an excuse string. Associate that total number with the excuse.
 * In this algorithm that is done by storing a vector of pairs in which the
 * first value is the excuse and the second value is its total number of excuses.
 * Maintain a maximum variable as well that keeps the max number of excuse keywords
 * that have appeared in an excuse string. With this, we can iterate through the vector
 * and print all of the excuses whose associated value of total excuses matches the maximum.
 * The excuses that will be printed will be printed in the order we received them. Possibly the
 * trickiest coding segment of this algorithm will be figuring out how many times a single word appears
 * in an excuse string. This is because we have to verify the appearance of of a keyword is valid given
 * its surrounding characters (or lack thereof). We then try and find the next occurrence of that keyword
 * after the first occurrence (if there was one to begin) and keep going until string::find returns npos.
 * Complexity analysis:
 * Time complexity: ADD THIS
 * Space complexity: ADD THIS (10/06/16)
 */

void toLower(string& inputString) {
  for (int i = 0; i < inputString.length(); ++i) {
    if (inputString[i] <= 'Z' && inputString[i] >= 'A') inputString[i] += 32;
  }
}

int numberOfProperAppearances(string keyword, string excuse) {
  int numAppearances = 0, characterAfterAppearance;
  toLower(excuse);
  toLower(keyword);
  
  int firstCharacterOfAppearance = excuse.find(keyword);
  
  while (firstCharacterOfAppearance != string::npos) {
    characterAfterAppearance = firstCharacterOfAppearance + keyword.length();
    if (firstCharacterOfAppearance == 0 && characterAfterAppearance < excuse.length()) {
      // Appearance is first word in excuse and there exists at least one character before the end (that we need to check)
      // if statement checks to see if that character is non-alphabetic
      if (!(excuse[characterAfterAppearance] >= 'a' && excuse[characterAfterAppearance] <= 'z') && !(excuse[characterAfterAppearance] >= 'A' && excuse[characterAfterAppearance] <= 'Z')) numAppearances++;
    } else if (firstCharacterOfAppearance > 0 && characterAfterAppearance == excuse.length()) {
      // Appearance is last word in excuse and there exists at least one character before the beginning (that we need to check)
      // if statement checks to see if that character is non-alphabetic
      if (!(excuse[characterAfterAppearance] >= 'a' && excuse[characterAfterAppearance] <= 'z') && !(excuse[characterAfterAppearance] >= 'A' && excuse[characterAfterAppearance] <= 'Z')) numAppearances++;
    } else {
      // Appearance lies somewhere in the middle not against either of the boundaries. There exists at least one character on either side of word (that we need to check)
      // if statement checks to see if those characters are non-alphabetic
      if ((!(excuse[characterAfterAppearance] >= 'a' && excuse[characterAfterAppearance] <= 'z') && !(excuse[characterAfterAppearance] >= 'A' && excuse[characterAfterAppearance] <= 'Z')) && (!(excuse[firstCharacterOfAppearance-1] >= 'a' && excuse[firstCharacterOfAppearance-1] <= 'z') && !(excuse[firstCharacterOfAppearance-1] >= 'A' && excuse[firstCharacterOfAppearance-1] <= 'Z'))) numAppearances++;
    }
    firstCharacterOfAppearance = excuse.find(keyword, characterAfterAppearance);
  }
  
  return numAppearances;
}

int main() {
  int numKeywords, numExcuses;
  vector<string> keywords;
  vector<pair<string, int> > excuses;
  string tmpString;
  int z = 1;
    
  while (cin >> numKeywords >> numExcuses) {

    keywords.reserve(numKeywords);
    excuses.reserve(numExcuses);

    cin.ignore();

    for (int i = 0; i < numKeywords; ++i) {
      getline(cin, tmpString);
      keywords.push_back(tmpString);
    }

    for (int i = 0; i < numExcuses; ++i) {
      getline(cin, tmpString);
      excuses.push_back(make_pair(tmpString, -1));
    }

    // Guts of the algorithm

    int totalExcuses = 0, maxExcuses = INT_MIN;
    for (int i = 0; i < numExcuses; ++i) {

      for (int j = 0; j < numKeywords; ++j) {
        totalExcuses += numberOfProperAppearances(keywords[j], excuses[i].first);
      }

      excuses[i].second = totalExcuses;
      maxExcuses = max(maxExcuses, totalExcuses);
      totalExcuses = 0;
    
    }

    cout << "Excuse Set #" << z << endl;
    for (int i = 0; i < numExcuses; ++i) {
      if (excuses[i].second == maxExcuses) cout << excuses[i].first << endl;
    }

    keywords.clear();
    excuses.clear();

    cout << endl;
    z++;
  }
    
  return 0;
}
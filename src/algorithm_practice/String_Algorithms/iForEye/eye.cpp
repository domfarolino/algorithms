#include <iostream>
#include <string>
#include <unordered_map>

std::string subs(const std::string& input, std::unordered_map<std::string, char>& uMap) {
  std::string returnString;

  int i = 0, length, end;
  bool madeSubs;
  std::string substrKey;
  while (i < input.size()) {
    length = 4;
    madeSubs = false;
    while (length) {
      // Only consider in-bounds lengths.
      if (i + (length - 1) >= input.size()) {
        length--;
        continue;
      }

      // Assert: index i + (length - 1) is in bounds.
      // Assert: input.substr(i, length) is valid substr.
      substrKey = input.substr(i, length);
      std::transform(substrKey.begin(), substrKey.end(), substrKey.begin(), ::tolower);
      if (uMap.find(substrKey) != uMap.end()) {
        madeSubs = true;
        // Below we append the character `1` time, since that is the length
        // of all the values in our |uMap|.
        if (input[i] >= 'a' && input[i] <= 'z')
          returnString.append(1, uMap[substrKey]);
        else
          returnString.append(1, std::toupper(uMap[substrKey]));
        i += length;

        // Once we've found a substitution, stop looking
        // for more at this particular point.
        break;
      }
      length--;
    }

    // When we make a substitution, we update all of our book-keeping
    // variables as necessary. When we don't, we have to here.
    if (!madeSubs) {
      returnString += input[i];
      i++;
    }
  }

  return returnString;
}

int main() {
  std::unordered_map<std::string, char> uMap;
  uMap["at"] = '@';
  uMap["and"] = '&';

  uMap["one"] = '1';
  uMap["won"] = '1';

  uMap["too"] = '2';
  uMap["to"] = '2';
  uMap["too"] = '2';

  uMap["for"] = '4';
  uMap["four"] = '4';

  uMap["bea"] = 'b';
  uMap["be"] = 'b';
  uMap["bee"] = 'b';

  uMap["sea"] = 'c';
  uMap["see"] = 'c';

  uMap["eye"] = 'i';

  uMap["oh"] = 'o';
  uMap["owe"] = 'o';

  uMap["are"] = 'r';
  uMap["you"] = 'u';
  uMap["why"] = 'y';

  int n;
  std::string input;
  std::cin >> n;

  // Read the first line of the input into the string, even though we read the
  // integer I guess?
  getline(std::cin, input);
  for (int i = 0; i < n; ++i) {
    getline(std::cin, input);
    std::cout << subs(input, uMap) << std::endl;
  }

  return 0;
}

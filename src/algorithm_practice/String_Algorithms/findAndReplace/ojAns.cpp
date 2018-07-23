// Source: https://leetcode.com/problems/find-and-replace-in-string/description/

class Solution {
public:
bool findInStringAtIndex(const std::string& haystack, int index, const std::string& needle) {
  // At this point, |index| is guaranteed to be within |haystack|
  // Check to see if what we're looking for runs off the end of haystack (is too long)
  if (needle.length() > haystack.length() - index)
    return false;

  // At this point we can search for |needle| in |haystack| at index |index| and guarantee
  // to not run off the end of |haystack| doing so
  for (int i = index; i < index + needle.length(); ++i) {
    if (haystack[i] != needle[i - index])
      return false;
  }

  return true;
}

std::string findReplaceString(const std::string& input, const std::vector<int>& indices, const std::vector<std::string>& sources, const std::vector<std::string>& targets) {
  std::string returnString;
  int index;
  std::vector<std::string> stringMap(input.length());

  // Build initial string map
  for (int i = 0; i < input.length(); ++i) stringMap[i] += input[i];

  for (int i = 0; i < indices.size(); ++i) {
    index = indices[i];
    if (!findInStringAtIndex(input, index, sources[i])) continue;
    stringMap[index] = targets[i];

    for (int j = 0; j < sources[i].length() - 1; ++j) {
      stringMap[index + 1 + j] = "";
    }
  }

  for (int i = 0; i < stringMap.size(); ++i) returnString += stringMap[i];
  return returnString;
}
};

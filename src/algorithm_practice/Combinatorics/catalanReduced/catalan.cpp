#include <iostream>
#include <vector>
#include <string>

// Source:https://leetcode.com/problems/optimal-division/description/

/**
 * This is a modified problem, inspired by Leetcode's "optimal division".
 *   - Optimal division (https://leetcode.com/problems/optimal-division/description/)
 *
 * For a more full explanation of what's going on here, please see the README file in this directory.
 */

std::vector<std::string> reducedParenOrderings(const std::vector<int>& vec, int s, int e, bool topLevel = false) {
  std::vector<std::string> returnVec, left, right;

  if (e - s == 0)
    returnVec.push_back(std::to_string(vec[s]));

  for (int i = s; i < e; ++i) {
    left = reducedParenOrderings(vec, s, i);
    right = reducedParenOrderings(vec, i + 1, e);

    // Combine left and right
    for (int l = 0; l < left.size(); ++l) {
      for (int r = 0; r < right.size(); ++r) {
        if (i == e - 1)
          returnVec.push_back(left[l] + + "/" + right[r]);
        else
          returnVec.push_back(left[l] + "/(" + right[r] + ")");
      }
    }
  }

  return returnVec;
}

std::vector<std::string> reducedParenOrderingsBroken(const std::vector<int>& vec, int s, int e, bool topLevel = false) {
  std::vector<std::string> returnVec, inside;

  // Base case.
  std::string baseString;
  if (e - s == 0 || e - s == 1) {
    baseString.append(std::to_string(vec[s]));
    if (e - s == 1)
      baseString.append("/" + std::to_string(vec[e]));
    returnVec.push_back(baseString);
    return returnVec;
  }

  for (int i = s; i <= e; ++i) {
    if (i > s) baseString.append("/");
    baseString.append(std::to_string(vec[i]));
  }
  returnVec.push_back(baseString);

  int start = s + 1, len;
  std::string prefix, suffix;
  while (start <= e - 1) {
    len = 2;
    while (len <= e - s && start + len - 1 <= e) {
      inside = reducedParenOrderingsBroken(vec, start, start + len - 1);

      // Build prefix and suffix strings
      // Range of subsequence is [start, start + len - 1]
      prefix = "";
      suffix = "";
      for (int i = s; i <= e; ++i) {
        if (i < start) {
          prefix += std::to_string(vec[i]);
          if (i < start - 1) prefix += "/";
        } else if (i > start + len - 1) {
          suffix += std::to_string(vec[i]);
          if (i < e) suffix += "/";
        }
      }

      for (auto innerGroup: inside) {
        if (innerGroup.size() > 1)
          returnVec.push_back(prefix + "/(" + innerGroup + ")");
        else
          returnVec.push_back(prefix + innerGroup);
        if (suffix.size()) returnVec[returnVec.size() - 1] += "/" + suffix;
      }

      len++;
    }

    start++;
  }

  return returnVec;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "You're dumb! (Or clever?)" << std::endl;
    return 1;
  }

  std::vector<int> v;
  int n = atoi(argv[1]);

  for (int i = 1; i <= n; ++i)
    v.push_back(i);

  std::vector<std::string> returnStrings = reducedParenOrderings(v, 0, v.size() - 1, true);

  for (int i = 0; i < returnStrings.size(); ++i)
    std::cout << returnStrings[i] << std::endl;

  return 0;
}

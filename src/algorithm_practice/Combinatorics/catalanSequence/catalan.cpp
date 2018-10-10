#include <iostream>
#include <vector>
#include <string>

// Source: (See below)

/**
 * This is a modified problem, inspired by
 *   1.) Optimal division (https://leetcode.com/problems/optimal-division/description/)
 *   2.) Generate Parentheses (https://leetcode.com/problems/generate-parentheses/description/)
 *
 * For a more full explanation of what's going on here, please see the README file in this directory.
 */

std::vector<std::string> parenOrderings(const std::vector<int>& vec, int s, int e, bool topLevel = false) {
  std::vector<std::string> returnVec, left, right;

  // Base case.
  if (e - s == 0)
    returnVec.push_back(std::to_string(vec[s]));

  for (int i = s; i < e; ++i) {
    left = parenOrderings(vec, s, i);
    right = parenOrderings(vec, i + 1, e);

    // Combine left and right.
    for (int l = 0; l < left.size(); ++l) {
      for (int r = 0; r < right.size(); ++r) {
        if (topLevel) // Avoid unecessary parens out outer level.
          returnVec.push_back(left[l] + right[r]);
        else
          returnVec.push_back("(" + left[l] + right[r] + ")");
      }
    }
  }

  return returnVec;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Gotta provide a number <n>" << std::endl;
    return 1;
  }

  std::vector<int> v;
  int n = atoi(argv[1]);

  for (int i = 1; i <= n; ++i)
    v.push_back(i);

  std::vector<std::string> returnStrings = parenOrderings(v, 0, v.size() - 1, true);

  for (int i = 0; i < returnStrings.size(); ++i)
    std::cout << returnStrings[i] << std::endl;

  return 0;
}

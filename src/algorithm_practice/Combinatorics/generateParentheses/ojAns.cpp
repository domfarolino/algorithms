// Source: https://leetcode.com/problems/generate-parentheses/description/

class Solution {
public:
    void parenCombinationsHelper(int numOpensLeft, int numClosedLeft, std::string& tmp, std::vector<std::string>& vec) {
  // Base case
  if (numOpensLeft == 0 && numClosedLeft == 0) {
    vec.push_back(tmp);
    return;
  }

  if (numOpensLeft < numClosedLeft) {
    // Close ")"
    tmp.append(")");
    parenCombinationsHelper(numOpensLeft, numClosedLeft - 1, tmp, vec);
    tmp.pop_back();
  }

  if (numOpensLeft != 0) {
    // Open "("
    tmp.append("(");
    parenCombinationsHelper(numOpensLeft - 1, numClosedLeft, tmp, vec);
    tmp.pop_back();
  }
}

std::vector<std::string> generateParenthesis(int n) {
  std::vector<std::string> returnVec;

  std::string tmp;
  parenCombinationsHelper(n, n, tmp, returnVec);

  return returnVec;
}
};

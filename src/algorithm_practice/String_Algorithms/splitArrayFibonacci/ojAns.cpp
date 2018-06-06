// Source: https://leetcode.com/contest/weekly-contest-86/problems/split-array-into-fibonacci-sequence/

class Solution {
public:
int lengthOfIntFromString(const std::string& str, int start, long goal) {
  int i;
  long value = str[start] - '0'; // char to int

  for (i = start + 1; i < str.size(); i++) {
    if (value == goal) return i - (start + 1) + 1;
    if (value >= INT_MAX) return 0;
    value *= 10;
    value += str[i] - '0';
  }

  return (value == goal) ? i - (start + 1) + 1 : 0;
}

// Helper called for every stack frame but the first; builds the rest of the sequence
void restOfSequence(const std::string& str, long firstNum, long secondNum, int begin, std::vector<int>& returnVec) {
  long thirdNumToFind = firstNum + secondNum;
  if (begin >= str.size() || thirdNumToFind >= INT_MAX)
    return;

  int lengthOfThirdNum = lengthOfIntFromString(str, begin, firstNum + secondNum);
  if (!lengthOfThirdNum)
    return;

  returnVec.push_back(thirdNumToFind);
  int size = returnVec.size();
  restOfSequence(str, secondNum, thirdNumToFind, begin + lengthOfThirdNum, returnVec);
  if (returnVec.size() == size && begin + lengthOfThirdNum < str.size())
    returnVec.pop_back();
}

/**
 * Where everything starts
 */
std::vector<int> splitIntoFibonacci(const std::string& str) {
  std::vector<int> returnVec;
  long firstNum, secondNum;
  int size;
  for (int i = 0; i < std::min(int(str.size()) - 2, 10); i++) {
    firstNum = std::stoul(str.substr(0, i + 1));
    if (str[0] == '0') firstNum = 0;

    for (int j = i + 1; j < std::min(int(str.size() - 1), i + 1 + 10); j++) {
      secondNum = std::stoul(str.substr(i + 1, j - (i + 1) + 1));
      if (str[i + 1] == '0')
        secondNum = 0;
      if (firstNum >= INT_MAX || secondNum >= INT_MAX)
        break;

      returnVec.push_back(firstNum);
      returnVec.push_back(secondNum);
      restOfSequence(str, firstNum, secondNum, j + 1, returnVec);
      if (returnVec.size() == 2) {
        returnVec.clear();
      } else return returnVec;
    }
  }

  return returnVec;
}
};

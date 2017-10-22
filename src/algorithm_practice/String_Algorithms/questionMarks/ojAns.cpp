// Source: https://coderbyte.com/results/domfarolino:Questions%20Marks:Cpp

#include <iostream>
#include <string>
using namespace std;

std::string questionMarks(const std::string& input) {
  int firstNum = 10, qCount = 0;
  bool atLeastOnePair = false; // this is for the requirement that if no pair = 10, return false anyways
  int charAsInt;

  for (int i = 0; i < input.size(); ++i) {
    charAsInt = (int)(input[i] - '0');
    if (firstNum == 10) {
      // Looking for first # in our pair
      if (charAsInt >= 0 && charAsInt <= '9') firstNum = charAsInt;
    } else {
      // Looking for second # in our pair
      if (charAsInt >= 0 && charAsInt <= 9) {
        // We have our second number!
        if (firstNum + charAsInt == 10) {
          atLeastOnePair = true;
          if (qCount != 3) return "false";
        }

        // Rest firstNum and qCount for next pair
        firstNum = charAsInt;
        qCount = 0;
      } else if (input[i] == '?') qCount++;
    }
  }

  return (atLeastOnePair) ? "true" : "false";
}

int main() {
  cout << questionMarks(gets(stdin));
  return 0;
}

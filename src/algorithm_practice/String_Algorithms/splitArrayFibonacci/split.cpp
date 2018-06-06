#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-86/problems/split-array-into-fibonacci-sequence/

/**
 * Split Array into Fibonacci Sequence
 * What a lovely and interesting problem. This was a really cool
 * one. Right off the bat it felt like an interesting backtracking
 * problem, and it was! After going through some examples it should
 * be clear that the first two chosen numbers set the stage for the
 * entire rest of the integers. My thought was that we wanted to have
 * a way to generate all of the possible first two numbers (that were
 * of course less <= 2^31 - 1), and for these pairs of integers, we want
 * to see if we can find the needed third number (first + second) from the
 * beginning of the rest of the string. The "rest" of the string starts with
 * the first digit coming after the last included in our second number. For
 * example, if the string was "7815", the first "first number" we could try out
 * would be 7, and the first "second number" would be 8. We know that in order to
 * continue successfully the third number would have to be 15. I opted to factor this
 * third-number-finding logic out into a helper function that takes a string, a starting
 * index, and a goal, and determines whether or not the third number can be extracted. In
 * the actual implementation, I opt to return the length of the third number if it exists,
 * because, where we continue later in the string looking for the next number depends on that.
 *
 * From here, given the first and second number, if we've found the third number successfully,
 * we can recursively continue down the string with the first and second number as the second and
 * third number. Finally, if we get to the end of the string and we've found all possible "third number"s,
 * we know the string can properly be split into a fibonacci sequence. If not, we have to unwind all the way
 * down, and try a new pair of first and second numbers to see if we can set the stage right this time to make
 * it through the entire string. Implementation-wise, I opted to have a single vector that each stack frame appends
 * a found-number to, and recursively calls the same routine with. If the recursive call results in the vector's size
 * unchanged, that means we could not split the array into a fibonacci sequence, and we can pop our found third number
 * until we get to the bottom. If we can try again, we do, else we return the eventually-empty vector. Implementation-
 * wise we want to make sure that we're only considering adding numbers that can fit in a signed integer, and don't overflow
 * in a way that would make us perform invalid comparisons later on.
 *
 * Complexity analysis
 * Time complexity: O(n) (but since n <= 200, I guess we could say O(1)?)
 *   The reason I say O(n) is because I imagine a theoretical worst case situation in which we generate the first
 *   two numbers, get all the way to the second to the last digit in the string, realize we can't find a needed final
 *   number split the array into a fibonacci sequence, go all the way back down to the first two numbers, and do the same
 *   thing. This sounds suspiciously O(n^2)-like with the repeated O(n) traversals, however since we can only accept a maximum
 *   of 2^31 - 1 as an entry, we can put an upper, constant bound (k) of O(n) traversals we make, thus making it an O(n) solution.
 *   Again, if we wanted to be really picky we could say n <= 200, so the solution is O(1) :)
 * Space complexity: O(1)
 */

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

void printVec(const std::vector<int>& vec) {
  std::cout << "{ ";
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << ", ";
  }
  std::cout << "} " << std::endl;
}

int main() {
  int n;
  std::string in;
  std::vector<int> fib;

  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> in;
    fib = splitIntoFibonacci(in);
    printVec(fib);
    fib.clear();
  }

  return 0;
}

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Source: https://www.hackerrank.com/challenges/ctci-balanced-brackets

/**
 * The goal of this algorithm is to determine whether a string
 * consisting only of open and close bracket characters such as
 * "[](){}" is balanced. The algorithm is fairly simple and utilizes
 * a stack. Basically we iterate through the entire expression string
 * we're given, and if we come across an opening bracket we want to push
 * it to the stack which makes sense. If we come across a closing one, it
 * must match the last thing we pushed to the stack (assuming the stack has
 * things in it) or else it is not valid. If they match (open/close pair) then
 * we can pop from the stack and keep moving on. After get through the entire string
 * without returning false it is easy to think "ok, just return true now". To see how
 * this is detrimental consider the following expression string: "[[[[[[". Sure we have
 * no issues while iterating however if we finish iterating through the expression string
 * and there are still characters in our stack this means we are missing closing brackets.
 * We should return false.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

bool matches(char open, char close) {
  if (open == '{' && close == '}' || open == '[' && close == ']' || open == '(' && close == ')') return true;
  return false;
}

bool isBalanced(string expression) {
  stack<char> stk;
  char curr;

  for (int i = 0; i < expression.length(); ++i) {
    curr = expression[i];

    if (curr == '{' || curr == '[' || curr == '(') {
      stk.push(curr);
    } else {
      if (!stk.size() || !matches(stk.top(), curr)) return false;
      stk.pop();
    }
  }

  return stk.size() == 0;
}

int main() {
  string expression = "{{{[[[(((())))]]]}}}";

  cout << isBalanced(expression) << endl;
  return 0;
}

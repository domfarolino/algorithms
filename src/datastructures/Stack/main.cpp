#include <iostream>
#include <assert.h>

#include "Stack.h"

using namespace std;

void pushAndSize() {
  Stack<int> stack;
  assert(stack.size() == 0);
  stack.push(1);
  assert(stack.size() == 1);
  stack.push(1);
  assert(stack.size() == 2);
}

void pushAndEmpty() {
  Stack<int> stack;
  assert(stack.empty());
  stack.push(1);
  assert(!stack.empty());
  stack.push(1);
  assert(!stack.empty());
}

void popAndSize() {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  assert(stack.size() == 3);
  stack.pop();
  assert(stack.size() == 2);
  stack.pop();
  assert(stack.size() == 1);
  stack.pop();
  assert(stack.size() == 0);
  stack.pop();
  assert(stack.size() == 0);
}

void popAndEmpty() {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  assert(!stack.empty());
  stack.pop();
  assert(!stack.empty());
  stack.pop();
  assert(!stack.empty());
  stack.pop();
  assert(stack.empty());
  stack.pop();
  assert(stack.empty());
}

void top() {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  assert(stack.top() == 3);
  assert(stack.top() == 3); // make sure stack.top() doesn't pop
  stack.pop();
  assert(stack.top() == 2);
  stack.pop();
  assert(stack.top() == 1);
  stack.pop();

  bool threwError = false;

  try {
    stack.top();
  } catch (std::exception &e) {
    threwError = true;
  }

  assert(threwError);
}

void clear() {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  stack.clear();
  stack.clear();

  assert(stack.size() == 0);
  assert(stack.empty());

  bool threwError = false;

  try {
    stack.top();
  } catch (std::exception e) {
    threwError = true;
  }

  assert(threwError);
}

int main() {
  pushAndSize();
  pushAndEmpty();
  popAndSize();
  popAndEmpty();
  top();
  clear();

  cout << "\x1B[32m✔ All tests pass\x1B[32m" << endl;
  return 0;
}

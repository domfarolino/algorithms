#include <iostream>
#include <assert.h>

#include "stack.h"

void pushAndSize() {
  stack<int> stck;
  assert(stck.size() == 0);
  stck.push(1);
  assert(stck.size() == 1);
  stck.push(1);
  assert(stck.size() == 2);
}

void pushAndEmpty() {
  stack<int> stck;
  assert(stck.empty());
  stck.push(1);
  assert(!stck.empty());
  stck.push(1);
  assert(!stck.empty());
}

void popAndSize() {
  stack<int> stck;
  stck.push(1);
  stck.push(2);
  stck.push(3);

  assert(stck.size() == 3);
  stck.pop();
  assert(stck.size() == 2);
  stck.pop();
  assert(stck.size() == 1);
  stck.pop();
  assert(stck.size() == 0);
  stck.pop();
  assert(stck.size() == 0);
}

void popAndEmpty() {
  stack<int> stck;
  stck.push(1);
  stck.push(2);
  stck.push(3);

  assert(!stck.empty());
  stck.pop();
  assert(!stck.empty());
  stck.pop();
  assert(!stck.empty());
  stck.pop();
  assert(stck.empty());
  stck.pop();
  assert(stck.empty());
}

void top() {
  stack<int> stck;
  stck.push(1);
  stck.push(2);
  stck.push(3);

  assert(stck.top() == 3);
  assert(stck.top() == 3); // make sure stack::top() doesn't pop
  stck.pop();
  assert(stck.top() == 2);
  stck.pop();
  assert(stck.top() == 1);
  stck.pop();

  bool threw_error = false;

  try {
    stck.top();
  } catch (std::exception &e) {
    threw_error = true;
  }

  assert(threw_error);
}

void clear() {
  stack<int> stck;
  stck.push(1);
  stck.push(2);
  stck.push(3);

  stck.clear();
  stck.clear();

  assert(stck.size() == 0);
  assert(stck.empty());

  bool threw_error = false;

  try {
    stck.top();
  } catch (std::logic_error e) {
    threw_error = true;
  }

  assert(threw_error);
}

void copyConstructor() {
  stack<int> right;
  right.push(1);
  right.push(2);
  right.push(3);

  stack<int> left = right;
  right.clear();

  assert(left.size() == 3);
  assert(left.top() == 3);
}

void copyAssignment() {
  stack<int> left, center, right;
  right.push(1);
  right.push(2);
  right.push(3);

  left = center = right;
  right.clear();

  assert(left.size() == 3);
  assert(center.size() == 3);
  assert(left.top() == 3);
  assert(center.top() == 3);

  center.clear();

  assert(left.size() == 3);
  assert(center.size() == 0);
  assert(center.empty());
}

int main() {
  pushAndSize();
  pushAndEmpty();
  popAndSize();
  popAndEmpty();
  top();
  clear();

  copyConstructor();
  copyAssignment();

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

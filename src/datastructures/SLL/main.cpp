#include <iostream>
#include <assert.h>

#include "SLL.h"

void sizeAndEmpty() {
  SLL<int> list;

  assert(list.size() == 0);
  assert(list.empty());

  list.addToTail(1);
  assert(list.size() == 1);
  assert(!list.empty());

  list.addToHead(2);
  assert(list.size() == 2);
  assert(!list.empty());

  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
}

void addToHead() {
  SLL<int> list;
  assert(list.listToString() == "");
  assert(list.size() == 0);
  list.addToHead(1);
  assert(list.listToString() == "1,");
  assert(list.size() == 1);
  list.addToHead(2);
  assert(list.listToString() == "2,1,");
  assert(list.size() == 2);
  list.addToHead(-1);
  assert(list.listToString() == "-1,2,1,");
  assert(list.size() == 3);
}

void addToTail() {
  SLL<int> list;
  assert(list.listToString() == "");
  assert(list.size() == 0);
  list.addToTail(1);
  assert(list.listToString() == "1,");
  assert(list.size() == 1);
  list.addToTail(2);
  assert(list.listToString() == "1,2,");
  assert(list.size() == 2);
  list.addToTail(-1);
  assert(list.listToString() == "1,2,-1,");
  assert(list.size() == 3);
}

void addToMix() {
  SLL<int> list;
  assert(list.listToString() == "");
  assert(list.size() == 0);
  list.addToTail(1);
  assert(list.listToString() == "1,");
  assert(list.size() == 1);
  list.addToHead(2);
  assert(list.listToString() == "2,1,");
  assert(list.size() == 2);
  list.addToHead(3);
  assert(list.listToString() == "3,2,1,");
  assert(list.size() == 3);
  list.addToTail(4);
  assert(list.listToString() == "3,2,1,4,");
  assert(list.size() == 4);
  list.addToHead(5);
  assert(list.listToString() == "5,3,2,1,4,");
  assert(list.size() == 5);
}

void removeFromHead() {
  SLL<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);
  list.addToHead(4);
  assert(list.listToString() == "4,3,2,1,");
  assert(list.size() == 4);
  list.removeFromHead();
  assert(list.listToString() == "3,2,1,");
  assert(list.size() == 3);
  list.removeFromHead();
  assert(list.listToString() == "2,1,");
  assert(list.size() == 2);
  list.removeFromHead();
  assert(list.listToString() == "1,");
  assert(list.size() == 1);
  list.removeFromHead();
  assert(list.listToString() == "");
  assert(list.size() == 0);
  list.removeFromHead();
  list.removeFromHead();
  list.removeFromHead();
  list.removeFromHead();
  assert(list.listToString() == "");
  assert(list.size() == 0);
}

void removeFromTail() {
  SLL<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);
  list.addToHead(4);
  assert(list.listToString() == "4,3,2,1,");
  assert(list.size() == 4);
  list.removeFromTail();
  assert(list.listToString() == "4,3,2,");
  assert(list.size() == 3);
  list.removeFromTail();
  assert(list.listToString() == "4,3,");
  assert(list.size() == 2);
  list.removeFromTail();
  assert(list.listToString() == "4,");
  assert(list.size() == 1);
  list.removeFromTail();
  assert(list.listToString() == "");
  assert(list.size() == 0);
  list.removeFromTail();
  list.removeFromTail();
  list.removeFromTail();
  list.removeFromTail();
  assert(list.listToString() == "");
  assert(list.size() == 0);
}

void remove() {
  SLL<int> list;
  list.addToHead(3);
  list.addToHead(2);
  list.addToHead(1);

  list.remove(4);
  assert(list.listToString() == "1,2,3,");
  assert(list.size() == 3);
  list.remove(2);
  assert(list.listToString() == "1,3,");
  assert(list.size() == 2);
  list.remove(1);
  assert(list.listToString() == "3,");
  assert(list.size() == 1);
  list.remove(3);
  list.remove(2);
  list.remove(2);
  list.remove(2);
  assert(list.listToString() == "");
  assert(list.size() == 0);
  assert(list.empty());
}

void clear() {
  SLL<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);

  list.clear();
  assert(list.listToString() == "");
  assert(list.size() == 0);
  assert(list.empty());
  list.clear();
  assert(list.listToString() == "");
  assert(list.size() == 0);
  assert(list.empty());

  list.addToHead(1);
  assert(list.size() == 1);
  assert(!list.empty());
}

void copyConstructor() {
  SLL<int> right;
  right.addToTail(1);
  right.addToTail(2);

  SLL<int> left = right;

  right.clear();
  right.addToHead(3);
  assert(left.listToString() == "1,2,");
  assert(left.size() == 2);

  assert(right.listToString() == "3,");
  assert(right.size() == 1);
}

void copyAssignment() {
  SLL<int> left, center, right;

  for (int i = 0; i < 5; ++i) right.addToTail(i);

  left = center = right;

  assert(left.listToString() == center.listToString());
  assert(left.size() == center.size());

  assert(center.listToString() == right.listToString());
  assert(center.size() == right.size());

  right.clear();
  center.addToHead(49);

  assert(left.listToString() == "0,1,2,3,4,");
  assert(center.listToString() == "49,0,1,2,3,4,");
  assert(right.listToString() == "");
}

int main() {
  sizeAndEmpty();
  addToHead();
  addToTail();
  addToMix();
  removeFromHead();
  removeFromTail();
  remove();
  clear();

  copyConstructor();
  copyAssignment();

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

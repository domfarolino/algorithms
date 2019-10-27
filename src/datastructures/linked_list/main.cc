#include <iostream>
#include <assert.h>

#include "linked_list.h"

void sizeAndEmpty() {
  linked_list<int> list;

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
  linked_list<int> list;
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.addToHead(1);
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.addToHead(2);
  assert(list.to_string() == "2,1,");
  assert(list.size() == 2);
  list.addToHead(-1);
  assert(list.to_string() == "-1,2,1,");
  assert(list.size() == 3);
}

void addToTail() {
  linked_list<int> list;
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.addToTail(1);
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.addToTail(2);
  assert(list.to_string() == "1,2,");
  assert(list.size() == 2);
  list.addToTail(-1);
  assert(list.to_string() == "1,2,-1,");
  assert(list.size() == 3);
}

void addToMix() {
  linked_list<int> list;
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.addToTail(1);
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.addToHead(2);
  assert(list.to_string() == "2,1,");
  assert(list.size() == 2);
  list.addToHead(3);
  assert(list.to_string() == "3,2,1,");
  assert(list.size() == 3);
  list.addToTail(4);
  assert(list.to_string() == "3,2,1,4,");
  assert(list.size() == 4);
  list.addToHead(5);
  assert(list.to_string() == "5,3,2,1,4,");
  assert(list.size() == 5);
}

void removeFromHead() {
  linked_list<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);
  list.addToHead(4);
  assert(list.to_string() == "4,3,2,1,");
  assert(list.size() == 4);
  list.removeFromHead();
  assert(list.to_string() == "3,2,1,");
  assert(list.size() == 3);
  list.removeFromHead();
  assert(list.to_string() == "2,1,");
  assert(list.size() == 2);
  list.removeFromHead();
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.removeFromHead();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.removeFromHead();
  list.removeFromHead();
  list.removeFromHead();
  list.removeFromHead();
  assert(list.to_string() == "");
  assert(list.size() == 0);
}

void removeFromTail() {
  linked_list<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);
  list.addToHead(4);
  assert(list.to_string() == "4,3,2,1,");
  assert(list.size() == 4);
  list.removeFromTail();
  assert(list.to_string() == "4,3,2,");
  assert(list.size() == 3);
  list.removeFromTail();
  assert(list.to_string() == "4,3,");
  assert(list.size() == 2);
  list.removeFromTail();
  assert(list.to_string() == "4,");
  assert(list.size() == 1);
  list.removeFromTail();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.removeFromTail();
  list.removeFromTail();
  list.removeFromTail();
  list.removeFromTail();
  assert(list.to_string() == "");
  assert(list.size() == 0);
}

void remove() {
  linked_list<int> list;
  list.addToHead(3);
  list.addToHead(2);
  list.addToHead(1);

  list.remove(4);
  assert(list.to_string() == "1,2,3,");
  assert(list.size() == 3);
  list.remove(2);
  assert(list.to_string() == "1,3,");
  assert(list.size() == 2);
  list.remove(1);
  assert(list.to_string() == "3,");
  assert(list.size() == 1);
  list.remove(3);
  list.remove(2);
  list.remove(2);
  list.remove(2);
  assert(list.to_string() == "");
  assert(list.size() == 0);
  assert(list.empty());
}

void clear() {
  linked_list<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);

  list.clear();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  assert(list.empty());
  list.clear();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  assert(list.empty());

  list.addToHead(1);
  assert(list.size() == 1);
  assert(!list.empty());
}

void copyConstructor() {
  linked_list<int> right;
  right.addToTail(1);
  right.addToTail(2);

  linked_list<int> left = right;

  right.clear();
  right.addToHead(3);
  assert(left.to_string() == "1,2,");
  assert(left.size() == 2);

  assert(right.to_string() == "3,");
  assert(right.size() == 1);
}

void copyAssignment() {
  linked_list<int> left, center, right;

  for (int i = 0; i < 5; ++i) right.addToTail(i);

  left = center = right;

  assert(left.to_string() == center.to_string());
  assert(left.size() == center.size());

  assert(center.to_string() == right.to_string());
  assert(center.size() == right.size());

  right.clear();
  center.addToHead(49);

  assert(left.to_string() == "0,1,2,3,4,");
  assert(center.to_string() == "49,0,1,2,3,4,");
  assert(right.to_string() == "");
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

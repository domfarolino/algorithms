#include <iostream>
#include <assert.h>

#include "SLL.h"

using namespace std;

void addToHead() {
  SLL<int> list;
  assert(list.listToString() == "");
  list.addToHead(1);
  assert(list.listToString() == "1,");
  list.addToHead(2);
  assert(list.listToString() == "2,1,");
  list.addToHead(-1);
  assert(list.listToString() == "-1,2,1,");
}

void addToTail() {
  SLL<int> list;
  assert(list.listToString() == "");
  list.addToTail(1);
  assert(list.listToString() == "1,");
  list.addToTail(2);
  assert(list.listToString() == "1,2,");
  list.addToTail(-1);
  assert(list.listToString() == "1,2,-1,");
}

void addToMix() {
  SLL<int> list;
  assert(list.listToString() == "");
  list.addToTail(1);
  assert(list.listToString() == "1,");
  list.addToHead(2);
  assert(list.listToString() == "2,1,");
  list.addToHead(3);
  assert(list.listToString() == "3,2,1,");
  list.addToTail(4);
  assert(list.listToString() == "3,2,1,4,");
  list.addToHead(5);
  assert(list.listToString() == "5,3,2,1,4,");
}

void removeFromHead() {
  SLL<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);
  list.addToHead(4);
  assert(list.listToString() == "4,3,2,1,");
  list.removeFromHead();
  assert(list.listToString() == "3,2,1,");
  list.removeFromHead();
  assert(list.listToString() == "2,1,");
  list.removeFromHead();
  assert(list.listToString() == "1,");
  list.removeFromHead();
  assert(list.listToString() == "");
  list.removeFromHead();
  list.removeFromHead();
  list.removeFromHead();
  list.removeFromHead();
  assert(list.listToString() == "");
}

void removeFromTail() {
  SLL<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);
  list.addToHead(4);
  assert(list.listToString() == "4,3,2,1,");
  list.removeFromTail();
  assert(list.listToString() == "4,3,2,");
  list.removeFromTail();
  assert(list.listToString() == "4,3,");
  list.removeFromTail();
  assert(list.listToString() == "4,");
  list.removeFromTail();
  assert(list.listToString() == "");
  list.removeFromTail();
  list.removeFromTail();
  list.removeFromTail();
  list.removeFromTail();
  assert(list.listToString() == "");
}

void remove() {
  SLL<int> list;
  list.addToHead(3);
  list.addToHead(2);
  list.addToHead(1);

  list.remove(4);
  assert(list.listToString() == "1,2,3,");
  list.remove(2);
  assert(list.listToString() == "1,3,");
  list.remove(1);
  assert(list.listToString() == "3,");
  list.remove(3);
  list.remove(2);
  list.remove(2);
  list.remove(2);
  assert(list.listToString() == "");
}

void clear() {
  SLL<int> list;
  list.addToHead(1);
  list.addToHead(2);
  list.addToHead(3);

  list.clear();
  assert(list.listToString() == "");
  list.clear();
  assert(list.listToString() == "");
}

int main() {
  addToHead();
  addToTail();
  addToMix();
  removeFromHead();
  removeFromTail();
  remove();
  clear();

  cout << "\x1B[32m✔ All tests pass\x1B[32m" << endl;
  return 0;
}

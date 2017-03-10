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

int main() {
  addToHead();
  addToTail();
  addToMix();

  cout << "\x1B[32m✔ All tests pass\x1B[32m" << endl;
  return 0;
}

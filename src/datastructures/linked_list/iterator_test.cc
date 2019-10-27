#include <iostream>
#include <assert.h>
#include "linked_list.h"

void iteratorIncrement() {
  linked_list<int> list;
  for (int i = 0; i < 20; ++i) {
    list.addToHead(20 - i - 1);
  }

  linked_list_iterator<int> a = list.begin();
  linked_list_iterator<int> b = list.begin();

  for (int i = 0; i < 19; ++i) {
    assert(*a++ == *++b - 1);
  }
}

void iteratorTraversal() {
  linked_list<int> list;

  for (int i = 0; i < 20; ++i) {
    list.addToHead(20 - i - 1);
  }

  linked_list_iterator<int> it = list.begin();
  int i = 0;

  while (it != list.end()) {
    assert(*it++ == i++);
  }

  assert(i == 20);
}

int main() {
  iteratorIncrement();
  iteratorTraversal();

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

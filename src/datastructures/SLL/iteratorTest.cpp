#include <iostream>
#include <assert.h>
#include "SLL.h"

void iteratorIncrement() {
  SLL<int> list;
  for (int i = 0; i < 20; ++i) {
    list.addToHead(20 - i - 1);
  }

  SLLIterator<int> a = list.begin();
  SLLIterator<int> b = list.begin();

  for (int i = 0; i < 19; ++i) {
    assert(*a++ == *++b - 1);
  }
}

void iteratorTraversal() {
  SLL<int> list;

  for (int i = 0; i < 20; ++i) {
    list.addToHead(20 - i - 1);
  }

  SLLIterator<int> it = list.begin();
  int i = 0;

  while (it != list.end()) {
    assert(*it++ == i++);
  }

  assert(i == 20);
}

int main() {
  iteratorIncrement();
  iteratorTraversal();

  std::cout << "\x1B[32m✔ All tests pass\x1B[32m" << std::endl;
  return 0;
}

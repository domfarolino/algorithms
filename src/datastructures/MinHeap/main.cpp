#include <iostream>
#include <cstdlib>
#include <assert.h>

#include "MinHeap.h"

void insertAndSize() {
  MinHeap<int> heap;
  assert(heap.size() == 0);
  heap.insert(0);
  assert(heap.size() == 1);
  heap.insert(0);
  assert(heap.size() == 2);
}

void insertAndEmpty() {
  MinHeap<int> heap;
  assert(heap.empty());
  heap.insert(0);
  assert(!heap.empty());
  heap.insert(0);
  assert(!heap.empty());
}

void removeAndSize() {
  MinHeap<int> heap;
  heap.insert(0);
  heap.insert(1);
  heap.insert(2);
  assert(heap.size() == 3);
  heap.remove();
  assert(heap.size() == 2);
  heap.remove();
  assert(heap.size() == 1);
  heap.remove();
  assert(heap.size() == 0);
  heap.remove();
  assert(heap.size() == 0);
}

void removeAndEmpty() {
  MinHeap<int> heap;
  heap.insert(0);
  heap.insert(1);
  heap.insert(2);
  assert(!heap.empty());
  heap.remove();
  assert(!heap.empty());
  heap.remove();
  assert(!heap.empty());
  heap.remove();
  assert(heap.empty());
  heap.remove();
  assert(heap.empty());
}

void peek() {
  srand(time(NULL));
  MinHeap<int> heap;

  for (int i = 0; i < 20; ++i) {
    heap.insert(rand() % 31);
  }

  int minThusFar = -1;

  while (!heap.empty()) {
    assert(heap.peek() >= minThusFar);
    minThusFar = heap.peek();
    heap.remove();
  }
}

void copyConstructor() {
  MinHeap<int> right;
  right.insert(1);
  right.insert(2);
  right.insert(3);

  MinHeap<int> left = right;
  right.clear();

  assert(left.size() == 3);
  assert(left.peek() == 1);
}

void copyAssignment() {
  MinHeap<int> left, center, right;
  right.insert(1);
  right.insert(2);
  right.insert(3);

  left = center = right;
  right.clear();

  assert(left.size() == 3);
  assert(center.size() == 3);
  assert(left.peek() == 1);
  assert(center.peek() == 1);

  center.clear();

  assert(left.size() == 3);
  assert(center.size() == 0);
  assert(center.empty());
}

int main() {
  insertAndSize();
  insertAndEmpty();
  removeAndSize();
  removeAndEmpty();
  peek();

  copyConstructor();
  copyAssignment();

  std::cout << "\x1B[32m✔ All tests pass\x1B[32m" << std::endl;
  return 0;
}

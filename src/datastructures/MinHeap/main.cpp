#include <iostream>
#include <cstdlib>
#include <assert.h>

#include "MinHeap.h"

void insertAndSize() {
  MinHeap<int> heap;
  assert(heap.Size() == 0);
  heap.Insert(0);
  assert(heap.Size() == 1);
  heap.Insert(0);
  assert(heap.Size() == 2);
}

void insertAndEmpty() {
  MinHeap<int> heap;
  assert(heap.Empty());
  heap.Insert(0);
  assert(!heap.Empty());
  heap.Insert(0);
  assert(!heap.Empty());
}

void removeAndSize() {
  MinHeap<int> heap;
  heap.Insert(0);
  heap.Insert(1);
  heap.Insert(2);
  assert(heap.Size() == 3);
  heap.Remove();
  assert(heap.Size() == 2);
  heap.Remove();
  assert(heap.Size() == 1);
  heap.Remove();
  assert(heap.Size() == 0);
  heap.Remove();
  assert(heap.Size() == 0);
}

void removeAndEmpty() {
  MinHeap<int> heap;
  heap.Insert(0);
  heap.Insert(1);
  heap.Insert(2);
  assert(!heap.Empty());
  heap.Remove();
  assert(!heap.Empty());
  heap.Remove();
  assert(!heap.Empty());
  heap.Remove();
  assert(heap.Empty());
  heap.Remove();
  assert(heap.Empty());
}

void Peek() {
  srand(time(NULL));
  MinHeap<int> heap;

  for (int i = 0; i < 20; ++i) {
    heap.Insert(rand() % 31);
  }

  int minThusFar = -1;

  while (!heap.Empty()) {
    assert(heap.Peek() >= minThusFar);
    minThusFar = heap.Peek();
    heap.Remove();
  }
}

void copyConstructor() {
  MinHeap<int> right;
  right.Insert(1);
  right.Insert(2);
  right.Insert(3);

  MinHeap<int> left = right;
  right.Clear();

  assert(left.Size() == 3);
  assert(left.Peek() == 1);
}

void copyAssignment() {
  MinHeap<int> left, center, right;
  right.Insert(1);
  right.Insert(2);
  right.Insert(3);

  left = center = right;
  right.Clear();

  assert(left.Size() == 3);
  assert(center.Size() == 3);
  assert(left.Peek() == 1);
  assert(center.Peek() == 1);

  center.Clear();

  assert(left.Size() == 3);
  assert(center.Size() == 0);
  assert(center.Empty());
}

int main() {
  insertAndSize();
  insertAndEmpty();
  removeAndSize();
  removeAndEmpty();
  Peek();

  copyConstructor();
  copyAssignment();

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

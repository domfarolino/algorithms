#include <iostream>
#include <math.h>
#include <assert.h>
#include "Vector.h"

using namespace std;

void pushBackAndSize() {
  Vector<int> vector(10);

  for (int i = 0; i < 100; ++i) {
    vector.push_back(i);
    assert(vector.size() == i + 1);
  }
}

void popBackAndSize() {
  Vector<int> vector(10);

  for (int i = 0; i < 100; ++i) {
    vector.push_back(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vector.size() == i + 1);
    vector.pop_back();
    assert(vector.size() == i);
  }
}

void pushBackAndIndex() {
  Vector<int> vector;

  for (int i = 0; i < 100; ++i) {
    vector.push_back(i);
  }

  for (int i = 0; i < 100; ++i) {
    assert(vector[i] == i);
  }

  // Capacity should be next power of two higher than (size() - 1)
  assert(vector.capacity() == pow(2, floor(log2(vector.size() - 1) + 1)));
}

void popBackAndIndex() {
  Vector<int> vector;

  for (int i = 0; i < 100; ++i) {
    vector.push_back(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vector[i] == i);
    vector.pop_back();
  }
}

void pushFrontAndSize() {
  Vector<int> vector(10);

  for (int i = 0; i < 100; ++i) {
    vector.push_front(i);
    assert(vector.size() == i + 1);
  }
}

void popFrontAndSize() {
  Vector<int> vector(10);

  for (int i = 0; i < 100; ++i) {
    vector.push_front(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vector.size() == i + 1);
    vector.pop_front();
    assert(vector.size() == i);
  }
}

void pushFrontAndIndex() {
  Vector<int> vector;

  for (int i = 0; i < 100; ++i) {
    vector.push_front(i);
  }

  for (int i = 0; i < 100; ++i) {
    assert(vector[i] == 99 - i);
  }

  // Capacity should be next power of two higher than (size() - 1)
  assert(vector.capacity() == pow(2, floor(log2(vector.size() - 1) + 1)));
}

void popFrontAndIndex() {
  Vector<int> vector;

  for (int i = 0; i < 100; ++i) {
    vector.push_front(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vector[0] == i);
    vector.pop_front();
  }
}

void sizeTest() {
  Vector<int> vector(10);

  for (int i = 0; i < 100; ++i) {
    vector.push_back(10);
    vector.push_front(11);
  }

  for (int i = 0; i < 100; ++i) {
    vector.pop_back();
    vector.pop_front();
    vector.pop_back();
    vector.pop_front();
  }

  assert(vector.size() == 0);
}

void reverseTest() {
  const int size = 100;
  Vector<int> vector(size);

  for (int i = 0; i < size; ++i) {
    vector.push_back(i);
  }

  vector.reverse();

  for (int i = 0; i < size; ++i) {
    assert(vector[i] == size - 1 - i);
  }

}

int main() {
  pushBackAndSize();
  popBackAndSize();
  pushBackAndIndex();
  popBackAndIndex();

  pushFrontAndSize();
  popFrontAndSize();
  pushFrontAndIndex();
  popFrontAndIndex();

  sizeTest();
  reverseTest();

  cout << "\x1B[32m✔ All tests pass\x1B[32m" << endl;
  return 0;
}

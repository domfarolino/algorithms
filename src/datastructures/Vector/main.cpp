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

void size() {
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

void reverse() {
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

void clear() {
  Vector<int> vector(100);

  for (int i = 0; i < 20; ++i) {
    vector.push_back(i);
  }

  vector.clear();
  vector.clear();

  assert(vector.size() == 0);
  assert(vector.empty());
  // Should reset vector to a fresh, usable form
  assert(vector.capacity() == 1);
}

void overloadedConstructor() {
  Vector<int> vector(-100);

  assert(vector.empty());
  assert(vector.size() == 0);
  assert(vector.capacity() == 1);

  vector.push_back(1);

  assert(!vector.empty());
  assert(vector.size() == 1);
  assert(vector.capacity() == 1);

  vector.push_back(1);

  assert(!vector.empty());
  assert(vector.size() == 2);
  assert(vector.capacity() == 2);

  Vector<int> vector2(10);
  assert(vector2.empty());
  assert(vector2.size() == 0);
  assert(vector2.capacity() == 10);

  for (int i = 0; i < 15; ++i) {
    vector2.push_back(i);
  }

  assert(vector2.size() == 15);
  // Once capacity is met, it doubles
  assert(vector2.capacity() == 20);
}

void copyConstructor() {
  Vector<int> right;

  for (int i = 0; i < 1000; ++i) {
    right.push_back(i);
  }

  Vector<int> left = right;

  assert(left.size() == right.size());
  assert(left.capacity() == right.capacity());

  for (int i = 0; i < left.size(); ++i) {
    assert(left[i] == i);
  }

  right[1] = 100;
  right.pop_front();

  assert(left.size() != right.size());
  assert(left[0] != right[0]);
}

void copyAssignment() {
  Vector<int> left, center, right(100);

  for (int i = 0; i < 1000; ++i) {
    right.push_back(i);
  }

  left = center = right;

  assert(left.size() == center.size());
  assert(center.size() == right.size());
  assert(left.capacity() == center.capacity());
  assert(center.capacity() == right.capacity());

  for (int i = 0; i < left.size(); ++i) {
    assert(left[i] == center[i]);
    assert(center[i] == right[i]);
  }

  right.pop_front();
  center[0] = 666;

  assert(left.size() != right.size());
  assert(center.size() != right.size());

  assert(left[0] != center[0]);
  assert(left[0] != right[0]);
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

  size();
  reverse();
  clear();
  overloadedConstructor();

  copyConstructor();
  copyAssignment();

  cout << "\x1B[32m✔ All tests pass\x1B[32m" << endl;
  return 0;
}

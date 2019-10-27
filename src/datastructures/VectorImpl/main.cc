#include <iostream>
#include <math.h>
#include <assert.h>

#include "vector.h"

void pushBackAndSize() {
  vector<int> vec(10);

  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
    assert(vec.size() == i + 1);
  }
}

void popBackAndSize() {
  vector<int> vec(10);

  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vec.size() == i + 1);
    vec.pop_back();
    assert(vec.size() == i);
  }
}

void pushBackAndIndex() {
  vector<int> vec;

  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  for (int i = 0; i < 100; ++i) {
    assert(vec[i] == i);
  }

  // Capacity should be next power of two higher than (size() - 1)
  assert(vec.capacity() == pow(2, floor(log2(vec.size() - 1) + 1)));
}

void popBackAndIndex() {
  vector<int> vec;

  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vec[i] == i);
    vec.pop_back();
  }
}

void pushFrontAndSize() {
  vector<int> vec(10);

  for (int i = 0; i < 100; ++i) {
    vec.push_front(i);
    assert(vec.size() == i + 1);
  }
}

void popFrontAndSize() {
  vector<int> vec(10);

  for (int i = 0; i < 100; ++i) {
    vec.push_front(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vec.size() == i + 1);
    vec.pop_front();
    assert(vec.size() == i);
  }
}

void pushFrontAndIndex() {
  vector<int> vec;

  for (int i = 0; i < 100; ++i) {
    vec.push_front(i);
  }

  for (int i = 0; i < 100; ++i) {
    assert(vec[i] == 99 - i);
  }

  // Capacity should be next power of two higher than (size() - 1)
  assert(vec.capacity() == pow(2, floor(log2(vec.size() - 1) + 1)));
}

void popFrontAndIndex() {
  vector<int> vec;

  for (int i = 0; i < 100; ++i) {
    vec.push_front(i);
  }

  for (int i = 99; i >= 0; --i) {
    assert(vec[0] == i);
    vec.pop_front();
  }
}

void size() {
  vector<int> vec(10);

  for (int i = 0; i < 100; ++i) {
    vec.push_back(10);
    vec.push_front(11);
  }

  for (int i = 0; i < 100; ++i) {
    vec.pop_back();
    vec.pop_front();
    vec.pop_back();
    vec.pop_front();
  }

  assert(vec.size() == 0);
}

void reverse() {
  const int size = 100;
  vector<int> vec(size);

  for (int i = 0; i < size; ++i) {
    vec.push_back(i);
  }

  vec.reverse();

  for (int i = 0; i < size; ++i) {
    assert(vec[i] == size - 1 - i);
  }

}

void clear() {
  vector<int> vec(100);

  for (int i = 0; i < 20; ++i) {
    vec.push_back(i);
  }

  vec.clear();
  vec.clear();

  assert(vec.size() == 0);
  assert(vec.empty());
  // Should reset vec to a fresh, usable form
  assert(vec.capacity() == 1);
}

void overloadedConstructor() {
  vector<int> vec(-100);

  assert(vec.empty());
  assert(vec.size() == 0);
  assert(vec.capacity() == 1);

  vec.push_back(1);

  assert(!vec.empty());
  assert(vec.size() == 1);
  assert(vec.capacity() == 1);

  vec.push_back(1);

  assert(!vec.empty());
  assert(vec.size() == 2);
  assert(vec.capacity() == 2);

  vector<int> vec2(10);
  assert(vec2.empty());
  assert(vec2.size() == 0);
  assert(vec2.capacity() == 10);

  for (int i = 0; i < 15; ++i) {
    vec2.push_back(i);
  }

  assert(vec2.size() == 15);
  // Once capacity is met, it doubles
  assert(vec2.capacity() == 20);
}

void copyConstructor() {
  vector<int> right;

  for (int i = 0; i < 1000; ++i) {
    right.push_back(i);
  }

  vector<int> left = right;

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
  vector<int> left, center, right(100);

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

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

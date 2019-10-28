#include <iostream>
#include <assert.h>

#include "queue.h" // To test this implementation
// #include "../queueFromStacks/queue.h" // to test the queue from Stacks implementation

void enqueueAndSize() {
  queue<int> q;
  assert(q.size() == 0);
  q.enqueue(1);
  assert(q.size() == 1);
  q.enqueue(2);
  assert(q.size() == 2);
  q.enqueue(3);
}

void enqueueAndEmpty() {
  queue<int> q;
  assert(q.empty());
  q.enqueue(1);
  assert(!q.empty());
  q.enqueue(2);
  assert(!q.empty());
}

void dequeueAndSize() {
  queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  assert(q.size() == 3);
  q.dequeue();
  assert(q.size() == 2);
  q.dequeue();
  assert(q.size() == 1);
  q.dequeue();
  assert(q.size() == 0);
  q.dequeue();
  assert(q.size() == 0);
}

void dequeueAndEmpty() {
  queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  assert(!q.empty());
  q.dequeue();
  assert(!q.empty());
  q.dequeue();
  assert(!q.empty());
  q.dequeue();
  assert(q.empty());
  q.dequeue();
  assert(q.empty());
}

void front() {
  queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  assert(q.front() == 1);
  assert(q.front() == 1); // make sure queue.front() doesn't dequeue
  q.dequeue();
  assert(q.front() == 2);
  q.dequeue();
  assert(q.front() == 3);
  q.dequeue();

  bool threwError = false;

  try {
    q.front();
  } catch (std::exception &e) {
    threwError = true;
  }

  assert(threwError);
}

void clear() {
  queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  q.clear();
  q.clear();

  assert(q.size() == 0);
  assert(q.empty());

  bool threwError = false;

  try {
    q.front();
  } catch (std::logic_error e) {
    threwError = true;
  }

  assert(threwError);
}

void copyConstructor() {
  queue<int> right;
  right.enqueue(1);
  right.enqueue(2);
  right.enqueue(3);

  queue<int> left = right;
  right.clear();

  assert(left.size() == 3);
  assert(left.front() == 1);
}

void copyAssignment() {
  queue<int> left, center, right;
  right.enqueue(1);
  right.enqueue(2);
  right.enqueue(3);

  left = center = right;
  right.clear();

  assert(left.size() == 3);
  assert(center.size() == 3);
  assert(left.front() == 1);
  assert(center.front() == 1);

  center.clear();

  assert(left.size() == 3);
  assert(center.size() == 0);
  assert(center.empty());
}

int main() {
  enqueueAndSize();
  enqueueAndEmpty();
  dequeueAndSize();
  dequeueAndEmpty();
  front();
  clear();

  copyConstructor();
  copyAssignment();

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

#include <iostream>
#include <assert.h>

#include "Queue.h"

using namespace std;

void enqueueAndSize() {
  Queue<int> q;
  assert(q.size() == 0);
  q.enqueue(1);
  assert(q.size() == 1);
  q.enqueue(2);
  assert(q.size() == 2);
  q.enqueue(3);
}

void enqueueAndEmpty() {
  Queue<int> q;
  assert(q.empty());
  q.enqueue(1);
  assert(!q.empty());
  q.enqueue(2);
  assert(!q.empty());
}

void dequeueAndSize() {
  Queue<int> q;
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
  Queue<int> q;
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
  Queue<int> q;
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

int main() {
  enqueueAndSize();
  enqueueAndEmpty();
  dequeueAndSize();
  dequeueAndEmpty();
  front();
  cout << "\x1B[32m✔ All tests pass\x1B[32m" << endl;
  return 0;
}

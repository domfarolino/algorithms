#ifndef QUEUE_FROM_STACKS_H
#define QUEUE_FROM_STACKS_H

#include "../stack/stack.h"

template <typename T>
class queue {
private:
  stack<T> inbox, outbox;
  void transfer();

public:
  queue() {}

  int size() const {
    return inbox.size() + outbox.size();
  }

  bool empty() const {
    return inbox.empty() && outbox.empty();
  }

  void enqueue(T);
  void dequeue();
  T front();
  void clear();
};

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void queue<T>::enqueue(T val) {
  inbox.push(val);
}

/**
 * Time complexity: O(1) amortized
 * Space complexity: O(1)
 */
template <typename T>
void queue<T>::dequeue() {
  if (inbox.empty() && outbox.empty()) return;

  if (outbox.empty()) {
    transfer();
  }

  outbox.pop();
}

/**
 * Time complexity: O(1) amortized
 * Space complexity: O(1)
 */
template <typename T>
T queue<T>::front() {
  if (inbox.empty() && outbox.empty()) throw std::logic_error("Trying to view top element of an empty stack");

  if (outbox.empty()) {
    transfer();
  }

  return outbox.top();
}

/**
 * Private utility to transfer elements from incoming stack to outgoing stack.
 * More or less reverses the order of a stack while still allowing items to be inputted.
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void queue<T>::transfer() {
  while (!inbox.empty()) {
    outbox.push(inbox.top());
    inbox.pop();
  }
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void queue<T>::clear() {
  inbox.clear();
  outbox.clear();
}

#endif // QUEUE_FROM_STACKS_H

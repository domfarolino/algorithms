#ifndef QUEUE_H
#define QUEUE_H

#include "../Stack/Stack.h"

template <typename T>
class Queue {
private:
  Stack<T> inbox, outbox;
  void transfer();

public:
  Queue() {}

  int size() const {
    return inbox.size() + outbox.size();
  }

  bool empty() const {
    return inbox.empty() && outbox.empty();
  }

  void enqueue(T);
  void dequeue();
  T front();
};

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void Queue<T>::enqueue(T val) {
  this->inbox.push(val);
}

/**
 * Time complexity: O(1) amortized
 * Space complexity: O(1)
 */
template <typename T>
void Queue<T>::dequeue() {
  if (this->inbox.empty() && this->outbox.empty()) return;

  if (this->outbox.empty()) {
    this->transfer();
  }

  this->outbox.pop();
}

/**
 * Time complexity: O(1) amortized
 * Space complexity: O(1)
 */
template <typename T>
T Queue<T>::front() {
  if (this->inbox.empty() && this->outbox.empty()) throw std::logic_error("Trying to view top element of an empty stack");

  if (this->outbox.empty()) {
    this->transfer();
  }

  return this->outbox.top();
}

/**
 * Private utility to transfer elements from incoming stack to outgoing stack.
 * More or less reverses the order of a stack while still allowing items to be inputted.
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void Queue<T>::transfer() {
  while (!inbox.empty()) {
    outbox.push(inbox.top());
    inbox.pop();
  }
}

#endif

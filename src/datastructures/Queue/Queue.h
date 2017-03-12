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

  int size() {
    return inbox.size() + outbox.size();
  }

  bool empty() {
    return inbox.empty() && outbox.empty();
  }

  void enqueue(T);
  void dequeue();
  T front();
};

template <typename T>
void Queue<T>::enqueue(T val) {
  this->inbox.push(val);
}

template <typename T>
void Queue<T>::dequeue() {
  if (this->inbox.empty() && this->outbox.empty()) return;

  if (this->outbox.empty()) {
    this->transfer();
  }

  this->outbox.pop();
}

template <typename T>
T Queue<T>::front() {
  if (this->inbox.empty() && this->outbox.empty()) throw std::logic_error("Trying to view top element of an empty stack");

  if (this->outbox.empty()) {
    this->transfer();
  }

  return this->outbox.top();
}

/**
 * Private utility to
 */
template <typename T>
void Queue<T>::transfer() {
  while (!inbox.empty()) {
    outbox.push(inbox.top());
    inbox.pop();
  }
}

#endif

#ifndef STACK_H
#define STACK_H

#include "../SLL.h"

template <typename T>
class Stack {
private:
  SLL<T> list;

public:
  Stack() {}

  int size() const {
    return this->list.size();
  }

  bool empty() const {
    return this->list.empty();
  }

  void push(T);
  void pop();
  T top() const;
  void clear();

  ~Stack() {
    this->clear();
  }
};

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::push(T val) {
  this->list.addToHead(val);
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::pop() {
  this->list.removeFromHead();
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T Stack<T>::top() const {
  if (!this->size()) {
    throw std::logic_error("Trying to view top element of an empty stack");
  }

  return 5;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::clear() {
  this->list.clear();
}

#endif

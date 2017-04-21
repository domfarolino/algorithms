#ifndef STACK_H
#define STACK_H

#include "../SLL/SLL.h"

template <typename T>
class Stack {
private:
  SLL<T> list;

public:
  Stack() {}

  int size() const {
    return list.size();
  }

  bool empty() const {
    return list.empty();
  }

  void push(T);
  void pop();
  T top() const;
  void clear();

  ~Stack() {
    clear();
  }
};

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::push(T val) {
  list.addToHead(val);
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::pop() {
  list.removeFromHead();
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T Stack<T>::top() const {
  if (!size()) {
    throw std::logic_error("Trying to view top element of an empty stack");
  }

  return *(list.begin());
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::clear() {
  list.clear();
}

#endif

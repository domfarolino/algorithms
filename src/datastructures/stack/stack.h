#ifndef STACK_H
#define STACK_H

#include "linked_list/linked_list.h"

template <typename T>
class stack {
private:
  linked_list<T> list;

public:
  stack() {}

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
};

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void stack<T>::push(T val) {
  list.add_to_head(val);
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void stack<T>::pop() {
  list.remove_from_head();
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T stack<T>::top() const {
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
void stack<T>::clear() {
  list.clear();
}

#endif // STACK_H

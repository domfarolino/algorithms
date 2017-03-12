#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
class Stack {
private:
  Node<T> *head;
  int _size;

public:
  Stack(): head(NULL), _size(0) {}

  int size() {
    return this->_size;
  }

  bool empty() {
    return this->_size == 0;
  }

  void push(T);
  void pop();
  T top();
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
  this->head = new Node<T>(val, this->head); // the ole swap
  this->_size++;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::pop() {
  if (!this->head) return;

  Node<T> *tmp = this->head->next;
  delete this->head;

  this->_size--;
  this->head = tmp;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T Stack<T>::top() {
  if (!this->size()) {
    throw std::logic_error("Trying to view top element of an empty stack");
  }

  return this->head->val;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void Stack<T>::clear() {
  Node<T> *next;

  while (this->head) {
    next = this->head->next;
    delete this->head;
    this->head = next;
  }

  this->_size = 0;
  // Don't need to set this->head = NULL because of the way we iterate
  // We guarantee that this->head = NULL at the end of the function
}

#endif

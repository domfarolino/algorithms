#ifndef SLL_H
#define SLL_H

#include "SLLIterator.h"
#include <utility> // std::swap

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
class SLL {
private:
  Node<T> *head, *tail;
  int _size;

public:
  SLL(): head(NULL), tail(NULL), _size(0) {}
  SLL(const SLL<T>&);
  SLL<T>& operator=(SLL<T>);

  int size() const {
    return this->_size;
  }

  bool empty() const {
    return (this->_size == 0) && (this->head == this->tail && this->tail == NULL);
  }

  void addToHead(T);
  void addToTail(T);
  void removeFromHead();
  void removeFromTail();
  void remove(T);
  bool exists(T) const;
  void clear();

  SLLIterator<T> begin() const {
    return SLLIterator<T>(this->head);
  }

  SLLIterator<T> end() const {
    Node<T> *end;

    if (this->tail) {
      end = this->tail->next;
    } else {
      end = this->tail;
    }

    return SLLIterator<T>(end);
  }

  std::string listToString() const;
  void printList() const;

  ~SLL() {
    this->clear();
  }
};

/**
 * Copy constructor
 */
template <typename T>
SLL<T>::SLL(const SLL<T>& other): head(NULL), tail(NULL), _size(0) {
  Node<T> *otherPtr = other.head;

  while (otherPtr) {
    this->addToTail(otherPtr->val);
    otherPtr = otherPtr->next;
  }
}

/**
 * Copy assignment operator
 * Using copy-swap idiom
 */
template <typename T>
SLL<T>& SLL<T>::operator=(SLL<T> other) {
  // Perform member variable swap
  std::swap(this->_size, other._size);
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
  return *this;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void SLL<T>::addToHead(T elem) {
  if (!this->head) {
    this->head = this->tail = new Node<T>(elem);
    this->_size++;
    return;
  }

  Node<T> *newHead = new Node<T>(elem, this->head);
  this->head = newHead; // could jam this into one line
  this->_size++;
}

/**
 * Time complexity: O(1)
 * Space complexity O(1)
 */
template <typename T>
void SLL<T>::addToTail(T elem) {
  if (!this->head) {
    this->head = this->tail = new Node<T>(elem);
    this->_size++;
    return;
  }

  this->tail->next = new Node<T>(elem);
  this->tail = this->tail->next;
  this->_size++;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void SLL<T>::removeFromHead() {
  if (!this->head) return;

  Node<T> *tmp = this->head->next;

  delete this->head;

  this->head = tmp;
  if (!this->head) this->tail = NULL;

  this->_size--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void SLL<T>::removeFromTail() {
  if (!this->tail) return;

  if (this->head == this->tail) {
    return this->removeFromHead();
  }

  Node<T> *curr = this->head;
  while (curr->next != this->tail) {
    curr = curr->next;
  }

  delete this->tail;

  this->tail = curr;
  this->tail->next = NULL; // important

  this->_size--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void SLL<T>::remove(T elem) {
  if (!this->head) return;

  if (this->head->val == elem) {
    return this->removeFromHead();
  }

  Node<T> *tmp = this->head;
  while (tmp->next && tmp->next->val != elem) {
    tmp = tmp->next;
  }

  // Could not find it
  if (!tmp->next) return;

  Node<T> *next = tmp->next->next; // either proper "next" node, or "NULL" after old tail

  if (tmp->next == this->tail) {
    this->tail = tmp;
  }

  delete tmp->next;
  tmp->next = next; // seals gap for regular list, or ensures list ends with NULL

  this->_size--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
bool SLL<T>::exists(T elem) const {
  Node<T> tmp = this->head;

  while (tmp) {
    if (tmp->val == elem) return true;
    tmp = tmp->next;
  }

  return false;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void SLL<T>::clear() {
  while (!this->empty()) {
    this->removeFromHead();
  }
}

/**
 * Utility for testing
 */
template <typename T>
std::string SLL<T>::listToString() const {
  std::string result;
  Node<T> *tmp = this->head;

  while (tmp) {
    result += std::to_string(tmp->val);
    result += ',';
    tmp = tmp->next;
  }

  return result;
}

/**
 * Utility for testing
 */
template <typename T>
void SLL<T>::printList() const {
  std::cout << this->listToString() << std::endl;
}

#endif

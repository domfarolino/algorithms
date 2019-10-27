#ifndef linked_list_H
#define linked_list_H

#include <utility> // std::swap

#include "linked_list_iterator.h"

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T in_val, Node<T> *in_next= nullptr): val(in_val), next(in_next) {}
};

template <typename T>
// TODO(domfarolino): Rename this class..maybe LinkedList.
class linked_list {
private:
  Node<T> *head_, *tail_;
  int size_;

public:
  linked_list(): head_(nullptr), tail_(nullptr), size_(0) {}
  linked_list(const linked_list<T>&);
  linked_list<T>& operator=(linked_list<T>);

  int size() const {
    return size_;
  }

  bool empty() const {
    return (size_ == 0) && (head_ == tail_ && tail_ == nullptr);
  }

  void addToHead(T);
  void addToTail(T);
  void removeFromHead();
  void removeFromTail();
  void remove(T);
  bool exists(T) const;
  void clear();

  linked_list_iterator<T> begin() const {
    return linked_list_iterator<T>(head_);
  }

  linked_list_iterator<T> end() const {
    Node<T> *end;

    if (tail_) {
      end = tail_->next;
    } else {
      end = tail_;
    }

    return linked_list_iterator<T>(end);
  }

  std::string to_string() const;

  ~linked_list() {
    clear();
  }
};

/**
 * Copy constructor
 */
template <typename T>
linked_list<T>::linked_list(const linked_list<T>& other): linked_list() {
  Node<T> *other_ptr = other.head_;

  while (other_ptr) {
    addToTail(other_ptr->val);
    other_ptr = other_ptr->next;
  }
}

/**
 * Copy assignment operator
 * Using copy-swap idiom
 */
template <typename T>
linked_list<T>& linked_list<T>::operator=(linked_list<T> other) {
  // Perform member variable swap
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  return *this;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void linked_list<T>::addToHead(T elem) {
  if (!head_) {
    head_ = tail_ = new Node<T>(elem);
    size_++;
    return;
  }

  Node<T>* new_head = new Node<T>(elem, head_);
  head_ = new_head; // could jam this into one line
  size_++;
}

/**
 * Time complexity: O(1)
 * Space complexity O(1)
 */
template <typename T>
void linked_list<T>::addToTail(T elem) {
  if (!head_) {
    head_ = tail_ = new Node<T>(elem);
    size_++;
    return;
  }

  tail_->next = new Node<T>(elem);
  tail_ = tail_->next;
  size_++;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void linked_list<T>::removeFromHead() {
  if (!head_) return;

  Node<T> *tmp = head_->next;

  delete head_;

  head_ = tmp;
  if (!head_) tail_ = nullptr;

  size_--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void linked_list<T>::removeFromTail() {
  if (!tail_) return;

  if (head_ == tail_) {
    return removeFromHead();
  }

  Node<T> *curr = head_;
  while (curr->next != tail_) {
    curr = curr->next;
  }

  delete tail_;

  tail_ = curr;
  tail_->next = nullptr; // important

  size_--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void linked_list<T>::remove(T elem) {
  if (!head_) return;

  if (head_->val == elem) {
    return removeFromHead();
  }

  Node<T> *tmp = head_;
  while (tmp->next && tmp->next->val != elem) {
    tmp = tmp->next;
  }

  // Could not find it
  if (!tmp->next) return;

  Node<T> *next = tmp->next->next; // either proper "next" node, or "nullptr" after old tail

  if (tmp->next == tail_) {
    tail_ = tmp;
  }

  delete tmp->next;
  tmp->next = next; // seals gap for regular list, or ensures list ends with nullptr

  size_--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
bool linked_list<T>::exists(T elem) const {
  Node<T> tmp = head_;

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
void linked_list<T>::clear() {
  while (!empty()) {
    removeFromHead();
  }
}

/**
 * Utility for testing
 */
template <typename T>
std::string linked_list<T>::to_string() const {
  std::string result;
  Node<T> *tmp = head_;

  while (tmp) {
    result += std::to_string(tmp->val);
    result += ',';
    tmp = tmp->next;
  }

  return result;
}

#endif

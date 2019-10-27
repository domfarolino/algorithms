#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <utility> // std::swap

template <typename T>
class linked_list {
private:
  struct Node {
    T val;
    Node* next;
    Node(T in_val, Node* in_next = nullptr): val(in_val), next(in_next) {}
  };

  Node *head_, *tail_;
  int size_;

public:
  linked_list(): head_(nullptr), tail_(nullptr), size_(0) {}
  linked_list(const linked_list<T>&);
  linked_list<T>& operator=(linked_list<T>);

  // class linked_list::iterator.
  class iterator {
   private:
    Node* node_ptr_;

   public:
    iterator(Node *in_ptr): node_ptr_(in_ptr) {}

    bool operator==(const iterator& other) const {
      return node_ptr_ == other.node_ptr_;
    }

    bool operator!=(const iterator& other) const {
      return node_ptr_ != other.node_ptr_;
    }

    iterator operator++() {
      node_ptr_ = node_ptr_->next;
      return *this;
    }

    iterator operator++(int) {
      iterator old_state = *this;
      node_ptr_ = node_ptr_->next;
      return old_state;
    }

    T& operator*() const {
      return node_ptr_->val;
    }
  }; // linked_list::iterator.

  int size() const {
    return size_;
  }

  bool empty() const {
    return (size_ == 0) && (head_ == tail_ && tail_ == nullptr);
  }

  void add_to_head(T);
  void add_to_tail(T);
  void remove_from_head();
  void remove_from_tail();
  void remove(T);
  bool exists(T) const;
  void clear();

  iterator begin() const {
    return iterator(head_);
  }

  iterator end() const {
    return iterator(nullptr);
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
  Node *other_ptr = other.head_;

  while (other_ptr) {
    add_to_tail(other_ptr->val);
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
void linked_list<T>::add_to_head(T elem) {
  if (!head_) {
    head_ = tail_ = new Node(elem);
    size_++;
    return;
  }

  Node* new_head = new Node(elem, head_);
  head_ = new_head; // could jam this into one line
  size_++;
}

/**
 * Time complexity: O(1)
 * Space complexity O(1)
 */
template <typename T>
void linked_list<T>::add_to_tail(T elem) {
  if (!head_) {
    head_ = tail_ = new Node(elem);
    size_++;
    return;
  }

  tail_->next = new Node(elem);
  tail_ = tail_->next;
  size_++;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void linked_list<T>::remove_from_head() {
  if (!head_) return;

  Node *tmp = head_->next;

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
void linked_list<T>::remove_from_tail() {
  if (!tail_) return;

  if (head_ == tail_) {
    return remove_from_head();
  }

  Node *curr = head_;
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
    return remove_from_head();
  }

  Node *tmp = head_;
  while (tmp->next && tmp->next->val != elem) {
    tmp = tmp->next;
  }

  // Could not find it
  if (!tmp->next) return;

  Node *next = tmp->next->next; // either proper "next" node, or "nullptr" after old tail

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
  Node tmp = head_;

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
    remove_from_head();
  }
}

/**
 * Utility for testing
 */
template <typename T>
std::string linked_list<T>::to_string() const {
  std::string result;
  Node *tmp = head_;

  while (tmp) {
    result += std::to_string(tmp->val);
    result += ',';
    tmp = tmp->next;
  }

  return result;
}

#endif // LINKED_LIST_H

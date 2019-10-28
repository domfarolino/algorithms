#ifndef QUEUE_H
#define QUEUE_H

#include "../linked_list/linked_list.h"

template <typename T>
class queue {
private:
  linked_list<int> list;

public:
  queue() {}

  int size() const {
    return list.size();
  }

  bool empty() const {
    return list.empty();
  }

  void enqueue(T);
  void dequeue();
  T front() const;
  void clear();
};

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void queue<T>::enqueue(T val) {
  list.add_to_tail(val);
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void queue<T>::dequeue() {
  list.remove_from_head();
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T queue<T>::front() const {
  if (!size()) {
    throw std::logic_error("Trying to view front element of an empty queue");
  }

  return *(list.begin());
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void queue<T>::clear() {
  list.clear();
}

#endif // QUEUE_H

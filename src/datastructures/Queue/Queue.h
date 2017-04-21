#ifndef QUEUE_H
#define QUEUE_H

#include "../SLL/SLL.h"

template <typename T>
class Queue {
private:
  SLL<int> list;

public:
  Queue() {}

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
void Queue<T>::enqueue(T val) {
  list.addToTail(val);
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void Queue<T>::dequeue() {
  list.removeFromHead();
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T Queue<T>::front() const {
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
void Queue<T>::clear() {
  list.clear();
}

#endif

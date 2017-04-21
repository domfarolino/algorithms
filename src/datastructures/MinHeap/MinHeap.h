#ifndef MINHEAP_H
#define MINHEAP_H

#include "../Vector/Vector.h"

template <typename T>
class MinHeap {
private:
  Vector<T> vec;
  void bubbleUp(int);
  void bubbleDown(int);

public:
  MinHeap() {}

  int size() const {
    return this->vec.size();
  }

  bool empty() const {
    return this->vec.empty();
  }

  void insert(T);
  void remove();
  T peek() const;

  void printHeap() const {
    for (int i = 0; i < this->vec.size(); ++i) {
      std::cout << this->vec[i] << ", ";
    }

    std::cout << std::endl;
  }

  void clear();
};

/**
 * Time complexity: O(log(n))
 * Space complexity: O(1) amortized
 */
template <typename T>
void MinHeap<T>::insert(T elem) {
  this->vec.push_back(elem);
  this->bubbleUp(this->vec.size() - 1);
}

/**
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::remove() {
  if (this->vec.empty()) return;
  this->vec[0] = this->vec[this->vec.size() - 1];
  this->vec.pop_back();
  this->bubbleDown(0);
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T MinHeap<T>::peek() const {
  if (this->vec.empty()) throw std::logic_error("Trying to peek on an empty heap");
  return this->vec[0];
}

/**
 * Private utility to maintain heap invariant
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::bubbleUp(int index) {
  if (!index) return;

  T currElem = this->vec[index];

  int parentIndex = (index - 1) / 2;

  if (this->vec[parentIndex] > currElem) {
    // Swap parent and child, continue bubbling from parent
    T parentItem = this->vec[parentIndex];
    this->vec[parentIndex] = currElem;
    this->vec[index] = parentItem;
    return this->bubbleUp(parentIndex);
  }
}

/**
 * Private utility to maintain heap invariant
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::bubbleDown(int index) {
  if (index >= this->vec.size()) return;

  bool hasLeftChild = false, hasRightChild = false;
  int lChildIndex = index * 2 + 1, rChildIndex = index * 2 + 2;

  if (lChildIndex < this->vec.size() && this->vec[index] > this->vec[lChildIndex]) hasLeftChild = true;
  if (rChildIndex < this->vec.size() && this->vec[index] > this->vec[rChildIndex]) hasRightChild = true;

  int indexToSwap;

  /**
   * Set indexToSwap equal to the valid index whose
   * value in the vector is the lowest (highest priority)
   */
  if (hasLeftChild && hasRightChild) indexToSwap = (this->vec[lChildIndex] <= this->vec[rChildIndex]) ? lChildIndex : rChildIndex;
  else if (hasLeftChild) indexToSwap = lChildIndex;
  else if (hasRightChild) indexToSwap = rChildIndex;
  else return;

  T childItem = this->vec[indexToSwap];
  this->vec[indexToSwap] = this->vec[index];
  this->vec[index] = childItem;
  return bubbleDown(indexToSwap);
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::clear() {
  this->vec.clear();
}

#endif

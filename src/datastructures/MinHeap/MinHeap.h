#ifndef MINHEAP_H
#define MINHEAP_H

#include "../Vector/Vector.h"

template <typename T>
class MinHeap {
private:
  Vector<T> vec_;
  void BubbleUp(int);
  void BubbleDown(int);

public:
  MinHeap() {}

  int Size() const {
    return vec_.size();
  }

  bool Empty() const {
    return vec_.empty();
  }

  void Insert(T);
  void Remove();
  T Peek() const;

  void PrintHeap() const {
    for (int i = 0; i < vec_.size(); ++i) {
      std::cout << vec_[i] << ", ";
    }

    std::cout << std::endl;
  }

  void Clear();
};

/**
 * Time complexity: O(log(n))
 * Space complexity: O(1) amortized
 */
template <typename T>
void MinHeap<T>::Insert(T elem) {
  vec_.push_back(elem);
  BubbleUp(vec_.size() - 1);
}

/**
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::Remove() {
  if (vec_.empty()) return;
  vec_[0] = vec_[vec_.size() - 1];
  vec_.pop_back();
  BubbleDown(0);
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T MinHeap<T>::Peek() const {
  if (vec_.empty())
    throw std::logic_error("Trying to Peek on an empty heap");

  return vec_[0];
}

/**
 * Private utility to maintain heap invariant
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::BubbleUp(int index) {
  if (!index) return;

  T current_element = vec_[index];

  int parent_index = (index - 1) / 2;

  if (vec_[parent_index] > current_element) {
    // Swap parent and child, continue bubbling from parent
    T parent_item = vec_[parent_index];
    vec_[parent_index] = current_element;
    vec_[index] = parent_item;
    return BubbleUp(parent_index);
  }
}

/**
 * Private utility to maintain heap invariant
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::BubbleDown(int index) {
  if (index >= vec_.size()) return;

  bool has_left_child = false, has_right_child = false;
  int l_child_idx = index * 2 + 1, r_child_idx = index * 2 + 2;

  if (l_child_idx < vec_.size() && vec_[index] > vec_[l_child_idx]) has_left_child = true;
  if (r_child_idx < vec_.size() && vec_[index] > vec_[r_child_idx]) has_right_child = true;

  int index_to_swap;

  /**
   * Set index_to_swap equal to the valid index whose
   * value in the vector is the lowest (highest priority)
   */
  if (has_left_child && has_right_child) index_to_swap = (vec_[l_child_idx] <= vec_[r_child_idx]) ? l_child_idx : r_child_idx;
  else if (has_left_child) index_to_swap = l_child_idx;
  else if (has_right_child) index_to_swap = r_child_idx;
  else return;

  T child_item = vec_[index_to_swap];
  vec_[index_to_swap] = vec_[index];
  vec_[index] = child_item;
  return BubbleDown(index_to_swap);
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void MinHeap<T>::Clear() {
  vec_.clear();
}

#endif

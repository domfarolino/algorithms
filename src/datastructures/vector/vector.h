#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept> // std::logic_error
#include <string>    // std::to_string.
#include <utility>   // std::swap.

#define MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a >= _b ? _a : _b; })

template <typename T>
class vector {
private:
  int size_, capacity_;
  T *data_;

public:
  vector(): size_(0), capacity_(1), data_(new T[capacity_]) {}
  vector(int in_capacity): size_(0), capacity_(MAX(1, in_capacity)), data_(new T[capacity_]) {}

  vector(const vector<T>&);
  vector& operator=(vector<T>);

  int size() const {
    return size_;
  }

  int capacity() const {
    return capacity_;
  }

  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    delete[] data_;
    capacity_ = 1;
    data_ = new T[capacity()];
    size_ = 0;
  }

  ~vector() {
    delete[] data_;
  }

  void push_back(T);
  void push_front(T);
  void pop_back();
  void pop_front();
  void reverse();
  T& operator[](int) const;
};

/**
 * Copy constructor
 */
template <typename T>
vector<T>::vector(const vector<T>& other) {
  data_ = new T[other.capacity()];
  capacity_ = other.capacity();

  for (int i = 0; i < other.size(); ++i) {
    data_[i] = other[i];
  }

  size_ = other.size();
}

/**
 * Copy assignment operator
 * Using copy-swap idiom
 */
template<typename T>
vector<T>& vector<T>::operator=(vector<T> other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
  return *this;
}

/**
 * Time complexity: O(1) amortized
 * Space complexity: O(1) amortized
 */
template <typename T>
void vector<T>::push_back(T val) {
  if (size_ >= capacity_) {
    T *tmp_data = new T[capacity_ * 2];

    for (int i = 0; i < size_; ++i) {
      tmp_data[i] = data_[i];
    }

    delete[] data_;
    data_ = tmp_data;

    capacity_ *= 2;
  }

  data_[size_++] = val;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1) amortized
 */
template <typename T>
void vector<T>::push_front(T val) {
  bool max_size = size_ == capacity_;
  T *tmp_data = data_;

  if (max_size) {
    data_ = new T[capacity_ * 2];
    capacity_ *= 2;
  }

  for (int i = size_ - 1; i >= 0; --i) {
    data_[i + 1] = tmp_data[i];
  }

  if (max_size) delete[] tmp_data;

  data_[0] = val;
  size_++;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void vector<T>::pop_back() {
  if (!empty()) size_--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void vector<T>::pop_front() {
  if (!empty()) {
    for (int i = 1; i < size_; ++i) {
      data_[i - 1] = data_[i];
    }

    size_--;
  }
}

/**
 * Time complexity: O(n)
 * Space complexity O(1)
 */
template <typename T>
void vector<T>::reverse() {
  T tmp;
  int i = 0, j = size_ - 1;

  while (i < j) {
    tmp = data_[i];
    data_[i] = data_[j];
    data_[j] = tmp;
    ++i;
    --j;
  }
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
T& vector<T>::operator[](int idx) const {
  if (idx >= 0 && idx < size_) {
    return data_[idx];
  } else {
    throw std::logic_error("Access out of bounds " + std::to_string(idx));
  }
}

#endif

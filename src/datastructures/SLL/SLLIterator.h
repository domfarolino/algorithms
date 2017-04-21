#ifndef SLL_ITERATOR
#define SLL_ITERATOR

template <typename T>
struct Node;

template <typename T>
class SLLIterator {
private:
  Node<T> *nodePtr;

public:
  SLLIterator(Node<T> *inPtr): nodePtr(inPtr) {}

  bool operator==(const SLLIterator<T>& other) const {
    return nodePtr == other.nodePtr;
  }

  bool operator!=(const SLLIterator<T>& other) const {
    return nodePtr != other.nodePtr;
  }

  SLLIterator<T> operator++() {
    nodePtr = nodePtr->next;
    return *this;
  }

  SLLIterator<T> operator++(int) {
    SLLIterator<T> oldState = *this;
    nodePtr = nodePtr->next;
    return oldState;
  }

  T& operator*() const {
    return nodePtr->val;
  }
};

#endif

#ifndef SLL_ITERATOR
#define SLL_ITERATOR

template <typename T>
struct Node;

template <typename T>
class linked_list_iterator {
private:
  Node<T> *nodePtr;

public:
  linked_list_iterator(Node<T> *inPtr): nodePtr(inPtr) {}

  bool operator==(const linked_list_iterator<T>& other) const {
    return nodePtr == other.nodePtr;
  }

  bool operator!=(const linked_list_iterator<T>& other) const {
    return nodePtr != other.nodePtr;
  }

  linked_list_iterator<T> operator++() {
    nodePtr = nodePtr->next;
    return *this;
  }

  linked_list_iterator<T> operator++(int) {
    linked_list_iterator<T> oldState = *this;
    nodePtr = nodePtr->next;
    return oldState;
  }

  T& operator*() const {
    return nodePtr->val;
  }
};

#endif

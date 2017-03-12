#ifndef SLL_H
#define SLL_H

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

public:
  SLL(): head(NULL), tail(NULL) {}

  ~SLL() {
    this->clear();
  }

  void addToHead(T);
  void addToTail(T);
  void removeFromHead();
  void removeFromTail();
  void remove(T);
  bool exists(T);
  void clear();

  std::string listToString();
  void printList();

};

template <typename T>
void SLL<T>::addToHead(T elem) {
  if (!this->head) {
    this->head = this->tail = new Node<T>(elem);
    return;
  }

  Node<T> *newHead = new Node<T>(elem, this->head);
  this->head = newHead;
}

template <typename T>
void SLL<T>::addToTail(T elem) {
  if (!this->head) {
    this->head = this->tail = new Node<T>(elem);
    return;
  }

  this->tail->next = new Node<T>(elem);
  this->tail = this->tail->next;
}

template <typename T>
void SLL<T>::removeFromHead() {
  if (!this->head) return;

  Node<T> *tmp = this->head->next;

  delete this->head;
  this->head = NULL;

  this->head = tmp;
  if (!this->head) this->tail = NULL;
}

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
  this->tail->next = NULL;
}

template <typename T>
void SLL<T>::remove(T elem) {
  if (!this->head) return;

  if (this->head->val == elem) return this->removeFromHead();

  Node<T> *tmp = this->head;
  while (tmp->next && tmp->next->val != elem) {
    tmp = tmp->next;
  }

  // Could not find it
  if (!tmp->next) return;

  Node<T> *next = tmp->next->next;

  if (tmp->next == this->tail) {
    this->tail = tmp;
  }

  delete tmp->next;
  tmp->next = next;
}

template <typename T>
bool SLL<T>::exists(T elem) {
  Node<T> tmp = this->head;

  while (tmp) {
    if (tmp->val == elem) return true;
    tmp = tmp->next;
  }

  return false;
}

template <typename T>
void SLL<T>::clear() {
  Node<T> *tmp = this->head;

  while (tmp) {
    tmp = tmp->next;
    delete this->head;
    this->head = tmp;
  }
}

/**
 * Utility for testing
 */
template <typename T>
std::string SLL<T>::listToString() {
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
void SLL<T>::printList() {
  std::cout << this->listToString() << std::endl;
}

#endif

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

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void SLL<T>::addToHead(T elem) {
  if (!this->head) {
    this->head = this->tail = new Node<T>(elem);
    return;
  }

  Node<T> *newHead = new Node<T>(elem, this->head);
  this->head = newHead; // could jam this into one line
}

/**
 * Time complexity: O(1)
 * Space complexity O(1)
 */
template <typename T>
void SLL<T>::addToTail(T elem) {
  if (!this->head) {
    this->head = this->tail = new Node<T>(elem);
    return;
  }

  this->tail->next = new Node<T>(elem);
  this->tail = this->tail->next;
}

/**
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template <typename T>
void SLL<T>::removeFromHead() {
  if (!this->head) return;

  Node<T> *tmp = this->head->next;

  delete this->head;

  this->head = tmp;
  if (!this->head) this->tail = NULL;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
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
  this->tail->next = NULL; // important!
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
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

  Node<T> *next = tmp->next->next; // either proper "next" node, or "NULL" after old tail

  if (tmp->next == this->tail) {
    this->tail = tmp;
  }

  delete tmp->next;
  tmp->next = next; // seals gap for regular list, or ensures list ends with NULL
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
bool SLL<T>::exists(T elem) {
  Node<T> tmp = this->head;

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
void SLL<T>::clear() {
  Node<T> *next = this->head;

  while (this->head) {
    next = this->head->next;
    delete this->head;
    this->head = next;
  }

  // Don't need to set this->head = NULL because of the way we iterate
  // We guarantee that this->head = NULL at the end of the function
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

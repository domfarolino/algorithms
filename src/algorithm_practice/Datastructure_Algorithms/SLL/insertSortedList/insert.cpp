#include <iostream>

using namespace std;

// Source: http://www.geeksforgeeks.org/given-a-linked-list-which-is-sorted-how-will-you-insert-in-sorted-way/
// Source: https://www.hackerrank.com/challenges/insert-a-node-into-a-sorted-doubly-linked-list <-- tested with this OJ

/**
 * Inserting a value into an already sorted linked list
 * The idea is to take the head of a linked list and some
 * value, and create a new node to insert into the linked list.
 * First let's cover some of the base cases and then we'll look
 * at finding the correct position to insert the new node. Of course
 * if we're given a NULL head, we want to set the head = newNode whose
 * value = the value we were given. If the head's value is < the value that
 * we should insert, then we should insert our new value before the current head.
 * In every other generic case we'll won't be modifying the head, but since we might
 * in the base cases, our function should return the head of the list, modified or not.
 * Assuming the very generic scenario with the list 1 -> 2 -> 4 -> 5 and we want to insert
 * the value 3. It is clear that 3 should be inserted between 2 and 4. We know that we'll need
 * a reference to 2 before we insert, so that we can set 2's next property = newNode. To find the
 * insertion point we'll need to maintain some curr pointer that starts with the head. We'll iterate
 * through the list until curr->next is no longer < val. It is at this point that we know our newNode
 * should be inserted between curr and curr->next.
 *
 * Given that we're at the proper position to insert a node there are two ways to go about it.
 * 1.)
 *    Node* tmpNode = curr->next;
 *    curr->next = newNode;
 *    newNode->next = tmpNode;
 *
 * 2.)
 *    newNode->next = curr->next;
 *    curr->next = newNode;
 *
 * Clearly the second method is more efficient as it does not require a temporary pointer to be created.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity; O(1)
 */

template <typename T>
struct Node {
  T val;
  Node *next;
  Node(T inVal, Node *inNext = NULL): val(inVal), next(inNext) {}
};

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
Node<T>* insertNode(Node<T> *head, T val) {
  if (!head || val < head->val) {
    Node<T>* newNode = new Node<T>(val);
    newNode->next = head;
    return newNode;
  }

  Node<T>* curr = head;

  // Find insertion point
  while (curr->next && curr->next->val < val) {
    curr = curr->next;
  }

  Node<T>* newNode = new Node<T>(val);
  newNode->next = curr->next;
  curr->next = newNode;

  return head;
}

/**
 * Utility function to delete linked list
 */
template <typename T>
void deleteList(Node<T>* head) {
  if (!head) return;
  deleteList(head->next);
  delete head;
}

int main() {
  Node<int>* aHead = new Node<int>(1);
  aHead->next = new Node<int>(2);
  aHead->next->next = new Node<int>(4);

  Node<int>* resultHead = insertNode(aHead, 3);

  Node<int>* curr = resultHead;

  while (curr) {
    cout << curr->val << " -> ";
    curr = curr->next;
  }
  cout << endl;

  deleteList(resultHead);
  return 0;
}

#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
// Source: https://www.hackerrank.com/challenges/30-linked-list-deletion

/**
 * Code and idea explains itself
 * Always good to write these with
 * templates to understand what kind
 * of assumptions you are making, often
 * with comparisons and assignments.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

template <typename T>
struct Node {
  T val;
  Node<T>* next;
  Node(T inVal, Node* inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
Node<T>* removeDuplicates(Node<T>* head) {
  if (!head) return NULL;
  Node<T> *curr = head, *next = head->next;

  while (next) {
    if (curr->val == next->val) {
      next = next->next;
      delete curr->next;
      curr->next = next;
    } else {
      curr = next;
      next = next->next;
    }
  }

  return head;
}

// Helper function to delete linked list
template <typename T>
void deleteList(Node<T>* head) {
  if (!head) return;
  deleteList(head->next);
  delete head;
  head = NULL; // ehh why not you know
}

int main() {
  // Build test list
  Node<int>* head = new Node<int>(1);
  head->next = new Node<int>(2);
  head->next->next = new Node<int>(2);
  head->next->next->next = new Node<int>(3);

  Node<int>* realHead = removeDuplicates(head);
  head = realHead;

  while (head) {
    cout << head->val << " -> ";
    head = head->next;
  }

  cout << "null abyss" << endl;

  deleteList(realHead);
  return 0;
}

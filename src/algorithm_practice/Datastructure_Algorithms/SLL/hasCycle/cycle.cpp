#include <iostream>
#include <string>

using namespace std;

// Source: https://leetcode.com/problems/linked-list-cycle/

/**
 * Linked List Cycle
 *
 * Write an algorithm to determine if a singly linked list
 * has a cycle in it. What we want to do is carry two pointers
 * one 'first', one 'second'. Both will start at the head and first
 * will increment by one and second will increment by two. If they ever
 * equal each other then there is a cycle. It is important to remember that
 * the two pointers increment independently of each other. Note that advancing
 * the slower pointer, nothing special is required however when advancing the fast
 * pointer we must see if fast->next exists, before setting fast = fast->next->next.
 *
 * We know that if ever fast->next == NULL || fast->next->next == NULL we have reached
 * the end of our list, thus there is no cycle. We keep advancing each pointer until they
 * either become equal or we hit the end of the list. It is relatively easy to prove that
 * if there is a cylce they will become equal. When exactly they will become equal is dependent
 * on how far the fast pointer is into the cycle when the slow pointer first enters it.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
bool hasCycle(Node<T> *head) {
  if (!head) return false;

  Node<T> *slow = head, *fast = head->next;

  while (slow != fast) {
    slow = slow->next;
    if (!fast || !fast->next) return false;
    fast = fast->next->next;
  }

  return true;
}

template <typename T>
void deleteList(Node<T> *head) {
  Node<T> *tmp;

  while (head) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}

int main() {
  Node<int> *head = new Node<int>(1);
  head->next = new Node<int>(2);

  cout << hasCycle(head) << endl;

  deleteList(head);
  return 0;
}

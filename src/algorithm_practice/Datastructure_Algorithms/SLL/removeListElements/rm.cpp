#include <iostream>

// Source: https://leetcode.com/problems/remove-linked-list-elements/description/

/**
 * Remove linked list elements
 * This problem is rather trivial, but quite neat! Basically
 * the task is that of removing all elements from a linked list
 * that match a certain given value. Given a NULL list, return NULL.
 * Consider the following input:
 *
 * In: 1 -> 2 -> 2, n = 2
 * Out: 1 -> x
 *
 * In: 1 -> 2 -> 2, n = 1
 * 2 -> 2
 *
 * Clearly we can iterate through our list, and whenever we find a node
 * whose value matches the one we're looking for (`n`), we should delete
 * the node. Note that normally when we remove a node from a list, we have
 * a reference to the previous node, so we can delete the doomed node and jump
 * over it, bridging the gap. Since here it is possible to delete the head, that
 * will slightly complicate our mechanics. We could:
 *  1.) Deal with the complication, and just special case head deletions, and try
 *      and get them all out of the way at once with some special logic, for example:
 *      while (head->val == n) {
 *        tmp = head->next;
 *        delete head;
 *        head = tmp;
 *      }
 *      ...and then continue with another loop looking at the more general case, where
 *      we start at the head, and look at all "next" nodes to see if they should be deleted.
 *
 *  2.) Do _only_ the general case, and take care of head deletions with the general case
 *      of creating a fake head pointer that points to, and sits before the original head.
 *      This way all of our deletions are the general case of having a reference before the
 *      doomed node, even in head deletions!
 *
 *  3.) Do this recursively with a trival solution. With recursive list solutions we often see the
 *      pattern of being able to operate directly on the "head" node in a given stack frame. This is
 *      because all references to earlier nodes are held in suspended frames, so whatever we return in
 *      a given frame, we don't have to worry about what comes behind us, because the previous recursive
 *      call and frames can take care of any prior references we don't need to worry about. Now, this pattern
 *      in this given situation manifests itself in a way such that we have the luxury of treating all node deletions
 *      as we would if they were the head, since the recursive solution treats all nodes as if they are the heads of their
 *      own sublist. For simplicity, this is the solution I've implemented below.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n), main downfall of using a recursive solution in this case
 */

template <typename T>
struct Node {
  T val;
  Node *next;
  Node (T inVal, Node *inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
void deleteList(Node<T> *head) {
  if (!head) return;
  deleteList(head->next);
  delete head;
}

template <typename T>
void printList(Node<T> *head) {
  while (head) {
    std::cout << head->val << " -> ";
    head = head->next;
  }

  std::cout << std::endl;
}

template <typename T>
Node<T>* removeElements(Node<T>* head, T val) {
  if (!head) return NULL;
  if (head->val == val) {
    delete head;
    return removeElements(head->next, val);
  } else {
    head->next = removeElements(head->next, val);
    return head;
  }
}

int main() {
  Node<int> *head = new Node<int>(1);
  head->next = new Node<int>(2);
  head->next->next = new Node<int>(1);
  head->next->next->next = new Node<int>(2);

  head = removeElements(head, 1);
  printList(head);

  deleteList(head);
  return 0;
}

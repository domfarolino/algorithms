#include <iostream>

using namespace std;

// Source: http://www.geeksforgeeks.org/delete-a-given-node-in-linked-list-under-given-constraints/
// Source: https://leetcode.com/problems/remove-linked-list-elements/

/**
 * Delete a node from a linked list list with value `val`.
 * Assume you are given the head of a singly linked
 * list and the value a list node that must be removed.
 * Let's first cover the base cases. There of course is
 * the case where the head is NULL, and the case where the
 * head is the node we need to delete. In the first case we'd
 * just want to return NULL and in the second case we'd be deleting
 * the head node but also modifying the head of the list. Since it is
 * possible for our algorithm to modify the head of the list we should
 * probably return the head in case it has been modified. You should confirm
 * all of this and other assumptions with your interviewer. In the average case,
 * we're going to want to to iterate through the list until we find the node we wish
 * to delete. In order to delete a node from a list, we should have a pointer to the node
 * before it so that we can properly take it out of the list without disrupting the relative
 * order of surrounding nodes etc. We'll maintain a temporary pointer curr that we'll initialize
 * to the head. We'll keep advancing the pointer forward until curr->next = val in which case we'll
 * delete curr->next. This is ideal since curr will be the reference to the node before it. The process
 * of deleting a node is fairly simple. Consider the following:
 *
 * Node *tmpNode = curr->next;
 * curr->next = curr->next->next;
 * delete tmpNode;
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Now consider the problem in which we want to delete multiple nodes with the value `val`. In this case, we'd
 * want to not stop once we found a single instance of the node we want to delete. Instead we'll want to handle the
 * deletion process inside the while loop which will change the condition of the loop since we'll want to run to the
 * end of the list every time. Our second base case can also change.
 * 1.)
 *    Instead of checking to see if the head's value is equal to the passed in value, we may want to want to keep deleting
 *    the head while head->val = val. Then we can continue with our regular body while loop as we would.
 * 2.)
 *    We can actually avoid the above by skipping the base case check (head->val == val) and continue with the regular loop
 *    as we would normally. This will delete ALL nodes in the list with a particular value EXCEPT the head. Then before we return
 *    we can do a simple check to see if the head we're about to return has a value = val. If it does we simple delete head and return
 *    head->next. This is totally safe because we know given the main body while loop, that the reset of the list does not have nodes whose
 *    value = val. So either head->next will be the head of a list of nodes without value val, or it is NULL. Both are totally valid!
 *
 * Complexity analysis: SAME!
 */

template <typename T>
struct Node {
  T val;
  Node *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
Node<T>* removeNode(Node<T> *head, T val) {
  if (!head) return NULL;
  if (head->val == val) {
    Node<T> *tmpNode = head;
    head = head->next;
    delete tmpNode;
    return head;
  }

  Node<T> *curr = head;

  while (curr->next && curr->next->val != val) {
    curr = curr->next;
  }

  if (curr->next) {
    Node<T> *tmpNode = curr->next;
    curr->next = curr->next->next;
    delete tmpNode;
  }

  return head;
}

template <typename T>
Node<T>* removeNodes(Node<T> *head, T val) {
  if (!head) return NULL;

  Node<T> *curr = head, *tmpNode;

  while (curr->next) {
    if (curr->next->val == val) {
      tmpNode = curr->next;
      curr->next = curr->next->next;
      delete tmpNode;
    } else {
      curr = curr->next;
    }
  }

  if (head->val == val) {
    tmpNode = head;
    head = head->next;
    delete tmpNode;
  }

  return head;
}

/**
 * Utility function for deleting a linked list
 */
template <typename T>
void deleteList(Node<T> *head) {
  if (!head) return;
  deleteList(head->next);
  delete head;
}

int main() {
  Node<int> *head = new Node<int>(1);
  head->next = new Node<int>(1);
  head->next->next = new Node<int>(3);
  head->next->next->next = new Node<int>(4);

  // Node<int> *removeResult = removeNode(head, 1);
  Node<int> *removeResult = removeNodes(head, 1);

  Node<int> *tmp = removeResult;

  while (tmp) {
    cout << tmp->val << " -> ";
    tmp = tmp->next;
  }

  cout << endl;

  deleteList(removeResult);
  return 0;
}

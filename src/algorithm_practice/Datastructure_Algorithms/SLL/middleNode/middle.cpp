#include <iostream>

// Source: https://leetcode.com/problems/middle-of-the-linked-list/description/

/**
 * Given the head of a singly linked list, return the middle node of
 * the linked list. If there are two middle nodes, return the second
 * middle node.
 * 
 * Since we don't know the size of the given linked list, we need to
 * figure out a way to find the middle node. We simply cannot just 
 * move one pointer one node at a time since we have no idea how long
 * the list is. So that means two pointers are needed to solve this
 * problem. If one pointer is moving one node at a time, and another
 * pointer is moving two nodes at a time, the pointer moving two nodes
 * at a time will reach the end first.
 * 
 * What does this mean?
 * 
 * Since we have a pointer moving one node at a time and a fast pointer
 * moving two nodes at a time, once the fast pointer reaches the end 
 * the slow pointer should be in the middle of the list. Then we can
 * simply return that node.
 * 
 * Here is an example:
 * 
 * Both pointers start at the head.
 * 
 *     head->node->node->node->node->node
 *     ^ ^
 *  slow fast
 * 
 * Move the slow one node and move fast two nodes.
 * 
 *     head->node->node->node->node->node
 *            ^     ^
 *           slow  fast
 * 
 * Move them again...
 * 
 *     head->node->node->node->node->node
 *                  ^            ^
 *                 slow        fast
 * 
 * Move them one more time...
 * 
 *     head->node->node->node->node->node
 *                        ^                 ^
 *                       slow              fast
 * 
 * Now that fast is no longer valid, we can return slow as the answer.
 * 
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

/**
 * The given 'ListNode' struct from LeetCode 
 */
template <typename T>
struct ListNode {
  int val;
  ListNode<T> *next;
  ListNode(): val(0), next(nullptr) {}
  ListNode(int x): val(x), next(nullptr) {}
  ListNode(int x, ListNode<T> *in_next): val(x), next(in_next) {}
};

/**
 * Solution
 */
template <typename T>
ListNode<T>* middleNode(ListNode<T>* head) {
  ListNode<T> *fast = head, *slow = head;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  return slow;
}

/**
 * Utility function to delete linked list 
 */
template <typename T>
void deleteList(ListNode<T> *head) {
  ListNode<T> *tmp;

  while (head) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}

int main() {
  ListNode<int> *head = new ListNode<int>(1);
  head->next = new ListNode<int>(2);
  head->next->next = new ListNode<int>(3);
  head->next->next->next = new ListNode<int>(4);
  head->next->next->next->next = new ListNode<int>(5);
  head->next->next->next->next->next = new ListNode<int>(6);

  ListNode<int> *middle = middleNode(head);

  std::cout << middle->val << "\n";

  deleteList(head);
  return 0;
}

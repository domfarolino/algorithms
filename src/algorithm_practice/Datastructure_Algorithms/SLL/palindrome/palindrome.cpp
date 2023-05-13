#include <iostream>

// Source: https://leetcode.com/problems/palindrome-linked-list/

/**
 * Given the head of a singly linked list, return true if it is a 
 * palindrome or false otherwise.
 * 
 * A naive approach to this problem would be to try to iterate over
 * the linked list and store the values into an array. Then compare
 * them to the linked list. In order to be able to solve this with
 * O(1) space, we need a better approach.
 * 
 * In order to do this, we will need to compare the first element with
 * the last element one at a time while working towards the middle of 
 * the linked list. This means we need to reverse half of the linked 
 * list. Using two pointers, a fast and a slow, we can find the middle
 * node. A full explanation on finding the middle node can be found 
 * in this repository at "./middleNode/middle.cpp".
 *     head->next->next->next
 *     ↑ ↑
 *  slow fast
 * 
 *     head->next->next->next
 *            ↑           ↑
 *          slow         fast
 * 
 *     head->next->next->next
 *                  ↑          ↑
 *                slow        fast
 * 
 * Once we find the middle node, the right half of the list needs 
 * to be reversed. Since we found the middle node, we can use another
 * pointer to store the next node, and another to store the previous
 * node. We can swap the pointers around right here without losing a 
 * reference to the rest of the second half of the list. A full 
 * explanation on reversing a linked list can be found in this repository
 * at "./reverseList/reverse.cpp". Now the list should look like this:
 *                  ↓ This node's next will actually be nullptr.
 *     head->next->next<-next
 * 
 * We still have access to the original head, and now we have another
 * pointer to the last value in the list. (We'll call it tail since it
 * is the last item in the list).
 *                  
 *     head->next->next<-next
 *      ↑                  ↑
 *     curr              tail
 * 
 * Now we can compare the values while moving the pointers 'towards' 
 * eachother. If the values aren't the same, return false. If the
 * pointers reach their respective "ends" of the list, we can return 
 * true!
 * 
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

/**
 * The given 'ListNode' struct from LeetCode.
 */
template <typename T>
struct ListNode {
  T val;
  ListNode<T>* next;
  ListNode(): val(0), next(nullptr) {}
  ListNode(T x): val(x), next(nullptr) {}
  ListNode(T x, ListNode<T>* in_next): val(x), next(in_next) {}
};

/**
 * Utility function to reverse half of the linked list.
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
ListNode<T>* reverse(ListNode<T>* head) {
  if (!head) return nullptr;

  ListNode<T>* prev = nullptr;
  ListNode<T>* curr = head;
  ListNode<T>* next = nullptr;

  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

/**
 * Utility function to find the middle node.
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
ListNode<T>* middleNode(ListNode<T>* head) {
  if (!head) return nullptr;

  ListNode<T>* slow = head;
  ListNode<T>* fast = head;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}

/**
 * The solution.
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
bool isPalindrome(ListNode<T>* head) {
  if (!head) return false;

  ListNode<T>* curr = head;
  ListNode<T>* tail = reverse(middleNode(head));
  ListNode<T>* original_tail = tail; // So we can delete the full LL.

  while (tail) {
    if (tail->val != curr->val) {
      // Could just return here but let's put the list back in order first.
      reverse(original_tail);
      return false;
    }
    tail = tail->next;
    curr = curr->next;
  }
  return true;
}

/**
 * Utility function to delete linked list.
 */
template <typename T>
void deleteList(ListNode<T>* head) {
  if (!head) return;
  deleteList(head->next);
  delete head;
}

/**
 * Utility function to print the linked list. 
 */
template <typename T>
void printNode(ListNode<T>* head) {
  ListNode<T>* tmp = head;

  while (tmp) {
    std::cout << tmp->val << "->";
    tmp = tmp->next;
  }
  std::cout << "NULL";
}

int main() {
  ListNode<int>* palindrome = new ListNode<int>(1);
  palindrome->next = new ListNode<int>(2);
  palindrome->next->next = new ListNode<int>(2);
  palindrome->next->next->next = new ListNode<int>(1);
  
  printNode(palindrome);
  std::cout << " is" << (isPalindrome(palindrome) ? " " : " not ") << "a palindrome.\n";
  
  deleteList(palindrome);

  ListNode<int>* not_palindrome = new ListNode<int>(1);
  not_palindrome->next = new ListNode<int>(2);
  not_palindrome->next->next = new ListNode<int>(2);
  not_palindrome->next->next->next = new ListNode<int>(2);

  printNode(not_palindrome);
  std::cout << " is" << (isPalindrome(not_palindrome) ? " " : " not ") << "a palindrome.\n";
  
  deleteList(not_palindrome);

  return 0;
}

#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/add-two-numbers/
// Source: http://www.geeksforgeeks.org/add-two-numbers-represented-by-linked-lists/

/**
 * Given two linked lists representing base 10 non-negative integers
 * stored in reverse order return a list that represents their base 10
 * sum also in reverse order.
 *
 * The "reverse order" restraint is actually a very good thing since we naturally
 * add numbers starting wth their least significant digits and this lets us do that.
 * When we normally add two numbers, we sum their individual digits at some place value
 * and if the sum > base we carry the remainder over for it to be evaluated in the next
 * digit sum. The typical traversing and adding is intuitively easy so let's cover our edge
 * cases. If one of the input lists is NULL we want to return the other one. If they're both
 * NULL we'll just return one of them. We'll use the two passed in list pointers to act as
 * placeholders in their respective lists and we'll increment them as we need to move forward.
 * While both of the pointers are not NULL, we'll keep adding values to a return list. The values
 * will be computed from (aCurrPtr->val + bCurrPtr->val + carry) % 10. We'll of course need to maintain
 * a return list that we'll be adding to as we go. We can keep a pointer to the end of the return
 * list so that we can keep pushing values to the end end and incrementing the pointer as necessary.
 * IMPORTANT: There is often a situation where we need to deal with a list from the inside of a loop.
 * In the average case we just take the list pointer, push something after it, and increment our pointer
 * however in the very initial case we actually have to create the list's head pointer. We could just have a
 * conditional in the loop to check to see if the list exist, if it does not we create it, else we handle the
 * situation how we would in the average case. Evaluating this conditional n times is very wasteful though because
 * of the n times we evaluate it, only one evaluation will ever use it! There are two ways to go about getting around
 * this. The first one is rather sub-par and the second is much more optimal. I first came up with the first one before
 * arriving at the second:
 *
 * 1.) We could initialize the list with a new node whose value = 0 outside of the while loop. Then inside the while loop
 * we can just take the head, correct its value, and create a head->next whose value = 0. The the first line of each while
 * loop we could just correct the node's value. The pseudo-code would look like this:
 *
 * head = new Node(0), listPtr = head;
 *
 * while (/condition/)
 *    listPtr->val = /setValueHere/
 *    listPtr->next = new Node(0); // setup node for next iteration (what if we don't need it though!!! Can't really delete it!)
 *    listPtr = listPtr->next;
 *
 * return head;
 *
 * The big drawback with this solution is that no matter what, our list will have an extra node at the end of it. Deleting this
 * node cannot be done without having a reference to the value behind it. Of course we can free the memory with `delete listLatest`
 * however the node before `listLatest` is still pointing to that memory which we have freed, and therefore does not point to NULL
 * and cannot be trusted. Messy!
 *
 * 2.) We could initialize the list outside of the loop as in the previous example, however we could still treat the list as if it
 * were ALWAYS the average case! The last example didn't work because we pushed nodes too early, so to remedy this we could just initialize
 * the list with a pre-head node, and keep pushing to the back of it. Everytime we enter the while loop we'll be dealing with the list as if
 * it were the average case. In other words we enter the loop having access to some node and then push something after it, and increment our ptr.
 * In order to return this list we'll then need to return preHead->next since the first node was just a dummy node. Pseudo-code below:
 *
 * preHead = new Node(0), listPtr = preHead;
 *
 * while (/condition/)
 *    listPtr->next = new Node(/setValueHere/);
 *    listPtr = listPtr->next;
 *
 * return preHead->next;
 *
 * Note we never have to check to see if the list exists on the first iteration since we've initialized a dummy node. The real list starts
 * at preHead->next so we'll have to return the list starting there. Not bad!
 *
 * Complexity analysis:
 * Time complexity: O(n), where n = max(length(a), length(b)), or log(max(a, b))
 * Space complexity: O(n), where n = max(length(a), length(b)), or log(max(a, b))
 */

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

/**
 * Homework: without looking at `ojAns.cpp` try and optimize
 * the following code by getting rid of the two extra while loops!
 */
Node<int>* addTwoNumbers(Node<int> *a, Node<int> *b) {
  if (!a && !b) return NULL;

  Node<int> *preHead = new Node<int>(0), *returnHead = preHead;
  int carry = 0;

  while (a && b) {
    returnHead->next = new Node<int>((a->val + b->val + carry) % 10);
    carry = (a->val + b->val + carry) / 10;

    a = a->next;
    b = b->next;
    returnHead = returnHead->next;
  }

  while (a) {
    returnHead->next = new Node<int>((a->val + carry) % 10);
    carry = (a->val + carry) / 10;

    a = a->next;
    returnHead = returnHead->next;
  }

  while (b) {
    returnHead->next = new Node<int>((b->val + carry) % 10);
    carry = (b->val + carry) / 10;

    b = b->next;
    returnHead = returnHead->next;
  }

  if (carry) {
    returnHead->next = new Node<int>(carry);
  }

  returnHead = preHead->next;
  delete preHead;
  return returnHead;
}

/**
 * Utility function to delete linked list
 */
template <typename T>
void deleteList(Node<T> *head) {
  if (!head) return;
  deleteList(head->next);
  delete head;
}

int main() {
  Node<int> *a = new Node<int>(0);
  a->next = new Node<int>(0);
  a->next->next = new Node<int>(2);
  a->next->next->next = new Node<int>(3);

  Node<int> *b = new Node<int>(0);
  b->next = new Node<int>(0);
  b->next->next = new Node<int>(0);
  b->next->next->next = new Node<int>(1);
  b->next->next->next->next = new Node<int>(1);

  Node<int> *sumHead = addTwoNumbers(a, NULL), *tmp = sumHead;

  while (tmp) {
    cout << tmp << ": " << tmp->val << ", ";
    tmp = tmp->next;
  }

  cout << endl;

  deleteList(a);
  deleteList(b);
  deleteList(sumHead);
  return 0;
}

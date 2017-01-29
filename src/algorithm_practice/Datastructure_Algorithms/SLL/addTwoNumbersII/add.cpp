#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/add-two-numbers-ii/
// Source: http://www.geeksforgeeks.org/sum-of-two-linked-lists/

/**
 * This algorithm is just like `addTwoNumbers` with the only
 * difference being that the lists are not in reverse order for us.
 * Instead the most significant digit of each list-represented integer
 * is at the head. This poses some minor difficulties as we'll need to start
 * with the least significant digits of each integer when adding. We know if we
 * can get to the ends of each list with recursion then we can can just unwind toward
 * the beginning through the stack frames and add like usual. So let's boil the problem
 * into one where we are given two linked lists, possibly of varying length, and w need to
 * get to the very last node of each. If we were given the list:
 *
 * 1 -> 2 -> 3 -> 4
 * 5 -> 6 -> 7
 *
 * We obviously couldn't recurse to the end with the following pointers passed into a function:
 *
 * (1, 5)
 * (2, 6)
 * (3, 7)
 * (3, 4)
 *
 * While this does get us to the end of each list, it stretches the first list out too far
 * in that we have multiple `3`s to make the shorter list as long as the second. In reality
 * we want:
 *
 * (1, X)
 * (2, 5)
 * (3, 6)
 * (4, 7)
 *
 * This is because we know that when adding the numbers 1234 + 567, 567 has no digit at the same place
 * value as `1` in 1234. This digit will stand alone. To achieve the desired recursion, we could just keep
 * track of the lengths of each list. We'll want to recurse only looking at values from the longer list until
 * the remaining list lenghts are equal. Then and only then we'll consider values from both lists. Basically we
 * just want to move forward in the longer one by (longList - shortList) nodes. For example if we have the lists:
 *
 * 1 -> 2 -> 3 -> 4
 * 5 -> 6 -> 7
 *
 * We'll start by passing in (1, 5, 4, 3) to our function. The first two values are the pointers to the lists and the
 * next two are their respective lengths. Since the lengths are not equal we'll only want to consider values from the longer
 * list. In order to get those length values equal for our future calls we'll have to keep advancing forward in the longer list.
 * Our next call will be (2, 5, 3, 3). Since the lengths are equal we can continue advancing at equal rates in each list until the
 * two pointers become NULL. This can be our base case, if both pointers are NULL we'll want to return a NULL list.
 *
 * Once we get to the end we can start adding values and unwinding toward the beginning of the lists. In the above example when we get
 * to `4` and `7` we can add them up and push that value to our return list. Two things are about to happen. We need to consider how to
 * push the value to a return list (and how to maintain said return list) and we'll have to ensure that the carry value as a result of the
 * integer makes its way back to the previous stack frame so it can consider it in its addition.
 *
 * Pushing values to our return list is actually very simple. The return list will need to be in order, so to build a list in order we can just
 * keep pushing values to the beginning of it, and inching our head pointer further away from the tail. We'll need to return the head of this list
 * from each frame, so that each previous frame can link off of it. Now let's figure out how we're going to share the value of the `carry` function
 * with a previous frame. Needing a value to persist from frame to frame is fairly simple can be done with either a static variable (often messy) or
 * a parameter passed by reference! The integer reference is probably the best way to do this, and we'll need to set the value of this carry reference
 * right after we finish our current addition. This will let the previous frame (next most significant addition) take into account our carry.
 *
 * In the current explained implementation the return list will only be as long as the longest list, but what if we need to actually add a new value to
 * the beginning of it? For example, if we add 99 + 1 the answer is 100, however our algorithm is only equipped to return 00. The very last time the carry
 * value is set it is ignored, so the algorithm only works when the final carry = 0. To get this working properly we can call our helper function with some
 * default carry value (init = 0) and check to see if carry != 0 after the recursion is done. If so, we just pop one more value onto the front.
 *
 * Now let's figure out how this will all be constructed. I first picture a function which will take in the two lists.
 * We'll then need to get the length of both of them. With the lengths of the lists we can call a helper function with the
 * pointers to each list and their respective lengths. This helper function will recurse to the end of each list starting with
 * the head of each list. On its way back, unwinding from the end, we'll be adding node values taking into account the value of
 * the newly returned frame's carry value. Once our helper function is done recursing we do a quick check to see if the carry is
 * 0 or not. We act accordingly and return the proper head! Woo!
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n), implicit stack frames via recursion
 */

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
int lengthOfList(Node<T> *head) {
  int returnLength = 0;

  while (head) {
    returnLength++;
    head = head->next;
  }

  return returnLength;
}

/**
 * Helper function for addTwoNumbers. This algorithm always
 * expects list a to have a length >= list b.
 */
Node<int>* addTwoNumbersHelper(Node<int> *a, Node<int> *b, int aLen, int bLen, int& carry) {
  if (!a && !b) return NULL;

  if (aLen != bLen) {
    Node<int> *next = addTwoNumbersHelper(a->next, b, aLen - 1, bLen, carry);
    Node<int> *returnHead = new Node<int>((a->val + carry) % 10);
    returnHead->next = next;
    carry = (a->val + carry) / 10;
    return returnHead;
  }

  Node<int> *next = addTwoNumbersHelper(a->next, b->next, aLen - 1, bLen - 1, carry);
  Node<int> *returnHead = new Node<int>((a->val + b->val + carry) % 10);
  returnHead->next = next;
  carry = (a->val + b->val + carry) / 10;
  return returnHead;
}

Node<int>* addTwoNumbers(Node<int> *a, Node<int> *b) {
  int aLen = lengthOfList(a), bLen = lengthOfList(b), carry = 0;
  Node<int> *returnHead;
  if (aLen >= bLen) returnHead = addTwoNumbersHelper(a, b, aLen, bLen, carry);
  else returnHead = addTwoNumbersHelper(b, a, bLen, aLen, carry);

  if (carry) {
    Node<int> *preHead = new Node<int>(carry, returnHead); // could make value `1` instead of `carry`
    return preHead;
  }

  return returnHead;
}

template <typename T>
void deleteList(Node<T> *head) {
  if (!head) return;
  deleteList(head->next);
  delete head;
}

int main() {
  Node<int> *a = new Node<int>(1);
  a->next = new Node<int>(5);
  a->next->next = new Node<int>(6);
  a->next->next->next = new Node<int>(7);

  Node<int> *b = new Node<int>(9);
  b->next = new Node<int>(8);
  b->next->next = new Node<int>(9);

  Node<int> *sumHead = addTwoNumbers(a, b), *tmp = sumHead;

  while (tmp) {
    cout << tmp->val;
    tmp = tmp->next;
  }

  cout << endl;

  deleteList(a);
  deleteList(b);
  deleteList(sumHead);
  return 0;
}

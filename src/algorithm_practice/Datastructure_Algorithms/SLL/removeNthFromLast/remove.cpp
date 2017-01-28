#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list/

/**
 * Given a linked list, remove the nth node from the tail and
 * return the list head.
 *
 * Typically when we remove a node from a linked list we want to
 * have a reference (ptr) to the node before the one we're removing.
 * In the case where we would have to remove the head from the list, we
 * would not have a reference to the (non-existent) node before it so we
 * might want to handle this separately. We could also use a fakeHead pointer
 * to treat the removal of the head like the removal of any other node. More on
 * that later. We should also assume that `n` may not be valid. My code will cover
 * this even though leetcode explicitly says `n` will be valid.
 *
 * We can solve this problem both iteratively and recursively. Let's first look at
 * the iterative version. We're going to want to maintain two pointers. The first pointer
 * will advance n nodes, and then finally the second one will start to follow at the same pace.
 * The point is to let the first node get n nodes ahead of the second. This way when the first node
 * reaches the end node, the second node will be right behind the nth from last node. Simple example:
 *
 * 1 -> 2 , n = 1
 *
 * We'll want to delete `2` from the list. This means we'll want our second pointer to be at the (n + 1)th
 * from last node when the first pointer reaches the end. This simple case makes it obvious we want our first
 * pointer to traverse `n` nodes before the second begins moving. This pattern is extendible to any node in the
 * list. We stop when the first pointer has reached the last in the list. Let's see another example.
 *
 * 1 -> 2 -> 3, n = 1
 *
 * In this case we'll want the second (slower) pointer to be at `2` when we wish to delete `3`. So we'll send
 * the first pointer exactly `n` nodes ahead. This way the second pointer will be at the (n - 1)th node from last
 * when the first pointer is at the nth from last. In these cases we'll perform a regular delete operation on the nth
 * from last node and return the head. In the case where n is invalid, we'll just return the head. In the case where we
 * must delete the head of the list (n = length of list) we could catch this early and handle it separately. An alternative
 * approach would be to maintain a fakeHead that sits before the real head. This would mean we'll always have a reference to
 * the node before the head, making head deletion as trivial as deleting any other node. Let's see an example.
 *
 * fH -> 1 -> 2, n = 1
 *
 * We know the second (slower) pointer will start at the fH pointer, so that we can delete the head if need be, but where will
 * first pointer start. Well, we could have it start at either the fH pointer, or at the regular head. Let's say we want it to start
 * at the regular head. If we wanted to delete the tail, since the first pointer will already be one pointer ahead of the second one
 * we'll only send it ahead n-1 nodes before they both advance together. This is the most basic case, as we know we'll always want the
 * second pointer to be 1 node behind the second pointer, and since it starts out 1 behind, they should move together off the bat. This
 * case helps us see that our logic is right. We can easily extend it to the situation where we delete the head. In this case, n = 2, therefore
 * we'll send the first pointer ahead (2 - 1) nodes before they traverse together. Sending the first pointer ahead one node eventually puts it ahead
 * of the second pointer by two nodes. It will be at the tail, therefore both pointers will stop advancing, and we should delete the second->next node.
 *
 * So far so good. Now we just need to spot the case where we're given an invalid n. When given an invalid n, we can realize that the first pointer will
 * not be able to actually reach the end of the list. In other words, when we're trying to advance the first pointer, we'll realize we cannot advance it far
 * enough (some loop condition?) and we should return the head immediately.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Let's now take a look at the recursive version of this algorithm. A common pattern we see in linked list algorithms is that we may need to store a reference
 * to the node behind the one of interest, so we can perform some operation like deleting a node. With recursion, we can often implicitly store references to nodes
 * in stack frames instead of explicitly keeping them in variables. This means we can just focus on the steps we need to perform once we arrive at the node of interest
 * since references to all of the previous nodes are stored implicitly on the stack. For example when we recursively delete a node from a linked list, if the current node
 * we're on is the one we want to delete, we'll just delete it, and return the node that appears after it. This works for the base case, and also in other cases, where we'll
 * set currentNode->next = recursiveCall(currentNode->next). It is a little wasteful, in that if there are n elements in the list, we're duplicating (n - 2) assignments that
 * already exist, but it gives us the ability to just return a single node from each frame and have very simple code. This algorithm is very similar to just deleting a node from
 * a linked list, the only difference being we don't want to check the node's value to determine whether or not it should be deleted, but instead we want to check how far it is from
 * the back, probably by maintaining some counter variable. So, how we do we maintain a counter variable that persists in between stack frames? There are two main ways to do this. One
 * requires us to have a slightly bloated function signature, by passing in some integer reference that each stack frame can modify/view without making a copy of, and the other is to use
 * a static variable inside the function. The static variable is nice because it hides some nice implementation details inside the function and only gets assigned one time (point of static).
 * We'll want to check this static counter on each frame and if the counter equals some value, we'll know to delete the current node. Now we need to figure out our method of actually mutating
 * the static counter. We'll want to increment the counter as we unwind back from the end of the list to the beginning. This means we'll want to be incrementing after the recursive call in each
 * frame, as this is when we'll be unwinding. Let's consider an example:
 *
 * 1 -> 2 -> 3 -> 5, n = 2
 *
 * With n = 2, we know we'll want to delete the `3` node. This means we'll need our static counter variable `i = 2` when we hit `3` as we're headed back to the beginning of the list. Of course
 * this means `i = 1` when we're on the last node. We can recurse past the `5` node to hit our base case (null head), and then increment the counter. Once the counter is incremented we can check
 * to see if `i == n`, and if so, delete the current node. Everything else from here is just like a regular recursive algorithm to delete a node from a linked list.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n) - due to stack frame accumulation
 */

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
Node<T>* removeNthFromLastIterative(Node<T> *head, int n) {
  if (!head) return NULL;

  Node<T> *fakeHead = new Node<T>(0);
  fakeHead->next = head;

  Node<T> *first = head, *second = fakeHead;

  // Advance first ptr by n - 1 nodes
  while (n - 1 && first) {
    first = first->next;
    n--;
  }

  // In case n is invalid
  if (!first) return head;

  // Advance both pointers at the same
  // pace until first = tail of list
  while (first->next) {
    first = first->next;
    second = second->next;
  }

  Node<T> *tmp = second->next;
  second->next = second->next->next;
  delete tmp;

  tmp = fakeHead->next;
  delete fakeHead;
  return tmp;
}

/**
 * Note the use of a static integer may mess with your
 * ability to use this function as a member of a class.
 */
template <typename T>
Node<T>* removeNthFromLastRecursive(Node<T>* head, int n) {
  if (!head) return NULL;

  static int i = 0; // initialized once

  Node<T>* next = removeNthFromLastRecursive(head->next, n);
  ++i;

  if (i == n) {
    delete head;
    return next;
  }

  head->next = next; // duplicate assignment I was talking about
  return head;
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
  head->next->next = new Node<int>(3);
  head->next->next->next = new Node<int>(4);
  head->next->next->next->next = new Node<int>(5);

  head = removeNthFromLastIterative(head, 1);

  Node<int> *tmp = head;

  while (tmp) {
    cout << tmp->val << " -> ";
    tmp = tmp->next;
  }

  cout << endl;

  head = removeNthFromLastRecursive(head, 2);

  tmp = head;

  while (tmp) {
    cout << tmp->val << " -> ";
    tmp = tmp->next;
  }

  cout << endl;

  deleteList(head);
  return 0;
}

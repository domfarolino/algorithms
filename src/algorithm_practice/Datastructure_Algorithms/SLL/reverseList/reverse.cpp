#include <iostream>

// Source: https://leetcode.com/problems/reverse-linked-list/

/**
 * Reverse a linked list
 * Classic fundamental data structure problem. We'll tackle this both
 * iteratively and recursively for good measure. The iterative version
 * is pretty simple, and its solution stems out of necessity. Lets look
 * at some examples and base cases first:
 *
 * In: 1 -> 2 -> 3 -> NULL
 * Out: 3 -> 2 -> 1 -> NULL
 *
 * In: 1 -> 2 -> 3 -> 4 -> NULL
 * Out: From 3 on, this problem is no more interesting...no surprises in this example
 *
 * In: NULL
 * Out: NULL
 *
 * In: 1 -> NULL
 * Out: 1 -> NULL
 * Explanation: A single node is already considered reversed
 *
 * In: 1 -> 2 -> NULL
 * Out: 2 -> 1 -> NULL
 *
 * As we may be able to see, the issue is relatively simple, and the general case seems
 * to be when we have 3 nodes or more, as the problem is no longer "special". We can do
 * a single reversal swap between two nodes really easy, for example:
 *         prev curr
 *          |    |
 *          v    v
 * Initial: 1 -> 2 -> 3 -> NULL
 * Perform: curr->next = prev
 * After swap: 1 <- 2 -> 3 -> NULL
 *
 * That part is trivial, but notice that once we make 2->next point to 1, we lose a reference
 * to the rest of the list. We can keep this reference the whole time if we introduce a pointer
 * variable that runs out and grabs the reference to the rest of the list after we locally reverse
 * some pair of nodes.
 *
 *        prev curr  next
 *          |    |    |
 *          v    v    v
 * Initial: 1 -> 2 -> 3 -> NULL
 *
 * Perform: curr->next = prev
 *
 *           prev curr  next
 *             |    |    |
 *             v    v    v
 * After swap: 1 <- 2 -> 3 -> NULL
 *
 * After this, we can move to the next pair of nodes to reverse, and keep moving along knowing we'll
 * always be able to access the rest of the list after a local swap. To move forward we can just slide
 * out pointer variables along by one. Since we'll be modifying |curr|, we need to ensure that we do so
 * when it is non-NULL. When we slide |curr| along, making curr = next, we'll want to return |prev| if and
 * only if |curr| _is_ NULL. In that case, |prev| will be the new head of our list.
 *
 * One thing we're missing is making the new tail of the list point to NULL. We can actually handle that from
 * the beginning, by starting out with prev = NULL, and curr = head. In this case, we'll set curr->next = NULL,
 * which is exactly what we want. Note that this works for the one- and two-node cases as well. If |curr| is non-NULL,
 * we at least have a single node in our list. If next = NULL, when we set |curr| to it, we'll safely return |prev| as
 * expected. If next is non-NULL, we continue as always until it, and eventually |curr|, are NULL and we return, essentially
 * making the two-node-and-on cases "general".
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Recursive solution!
 * The recursive solution to this problem is kind of strange.
 * As with all recursive problems, we want to break the problem down into smaller
 * versions of itself until we hit the most diluted of cases, the base case, which is
 * trivial. In this case, given the head of a list, it makes sense to want to recurse
 * on the list that starts with head->next for any given stack frame, and assume that
 * the result of this recursion will return the _remaining portion_ of the list in reverse
 * order.
 *
 * So imagine our list is:
 * 1 -> 2 -> 3 -> NULL
 *
 * We can hold onto `1`, and recurse on `2` (1->next), and assume that the remaining yet reversed
 * portion of the list will look like this:
 *
 * NULL <- 2 <- 3
 *
 * ...however by the time we get back to the `1` stack frame, `1` still points to `2`, also giving us:
 *
 * 1 -> 2 <- 3 <- NULL
 *
 * Even though 2->next = NULL, we still have access to the tail `2` of this list, through 1->next.
 * In this case we want to set 1->next->next = 1, which makes 2->next = 1, not NULL, appending 1 to
 * the list. After this, we want to set 1->next = NULL to ensure that in any given stack frame the list
 * we're returning is an entirely complete self-composed null-terminating list. We'll still want to return
 * the head from the previous list segment, which we can assume is what the recursive call turns.
 *
 * Our base case here is when head == NULL, in which case we want to return NULL. Also when we attempt to
 * recurse when we're on the final element of the list, we'll be recursing on NULL. This means the recursion
 * will return NULL because of the base case we just established. In this case, we want to return |head|, because
 * the reverse of a single element is itself, this is a special case since we're not performing any reversal logic.
 * This very |head| that we return in our last stack frame will be the |head| that we constantly return throughout
 * each stack frame. Note: what makes this solution powerful is not what we return at each frame, because it is essentially
 * the same once we get to the very end! It is instead the operations we're performing at each level.
 *
 * Takeaways: The key is assuming the recursive call perfectly performs the task we want on a smaller subproblem,
 * and that we are recursing right off the bat, and performing our logic after recursion, which lets us run all the
 * way out as far as we can first, and run our logic essentially in reverse order. Also to reiterate, what is important
 * is that we're recursing right off the bat, which effectively lets us first perform our logic in the later stack frames
 * after our recursion bottoms out.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n), implicitly in stack frames
 */

template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T inVal, Node<T> *inNext = NULL): val(inVal), next(inNext) {}
};

template <typename T>
Node<T>* reverseIterative(Node<T> *head) {
  if (!head) return NULL;
  Node<T> *prev = NULL, *curr = head, *next;

  while (curr) {
    // Grab our reference to the rest of the list
    next = curr->next;

    // Perform the reversal at this location
    curr->next = prev;

    // Slide variables along the list
    prev = curr;
    curr = next;
  }

  return prev;
}

template <typename T>
Node<T>* reverseRecursive(Node<T>* head) {
  if (!head) return NULL;

  Node<T> *finalHead = reverseRecursive(head->next);
  if (!finalHead) return head;

  head->next->next = head;
  head->next = NULL;
  return finalHead;
}

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

  std::cout << "NULL" << std::endl;
}

int main() {
  Node<int> *head = new Node<int>(1);
  head->next = new Node<int>(2);
  head->next->next = new Node<int>(3);

  head = reverseIterative(head);
  printList(head);

  head = reverseRecursive(head);
  printList(head);
  deleteList(head);
  return 0;
}

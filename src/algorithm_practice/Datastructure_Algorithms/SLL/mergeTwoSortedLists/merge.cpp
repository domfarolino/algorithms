#include <iostream>

// Source: https://leetcode.com/problems/merge-two-sorted-lists/description/

/**
 * Merge two sorted lists
 * This problem is relatively simple, and just requires
 * some simple pointer mechanics, but the gist is straightforward.
 * Basically the main edge cases we want to watch out for are when both
 * input lists are NULL, or one of them is. In these cases, we want to return
 * NULL, or the other-non-NULL list respectively. Beyond this, we can consider
 * the more general case. Going through an example or two helps see exactly what
 * steps are required, and what work must be done. Consider the following lists:
 *
 * 2 -> 4 -> 6 -> x
 * 1 -> 3 -> 5 -> x
 *
 * We of course want to start from the head of both lists, and since we're merging
 * these lists, ultimately we'll end up with only one head. This head will be the
 * smaller of the two heads, value-wise. So we start looking at `1` and `2`. `1` Since
 * `1` is the "smaller" head in this case, we'll want to "choose" this node at this point,
 * but we have to figure out which node will come next. We have two candidates for the next
 * node:
 *  1.) 1->next, or `3`
 *  2.) The other node, or `2`
 *
 * We can compare these nodes and choose which one will take the position of 1->next. In this
 * case, the other node `2` is the smaller one, so we'll want to set 1->next = `2`, but before
 * doing this, we need to make sure we save a reference to the node currently at 1->next, so we
 * don't lose the rest of our list. So we'll save a reference to the rest of the list in some
 * temporary variable, and then set 1->next = 2. Now we have a list that looks like this:
 *
 * `head1`
 * 2 -> 4 -> 6 -> x
 * ^
 * |   `head2`
 * 1    3 -> 5 -> x
 *
 * I've put `head1` and `head2` to illustrate that we'll need some extra pointer variables to
 * use as temporary heads that we'll keep updated as we iterate through the list. After we perform
 * an operation like we did above, we want to update the pointer to the node that we worked, to the
 * pointer we stored in our temporary variable. Now, the two nodes we'll be comparing during our next
 * iteration will be the new "heads" of the two lists. Above, we ran into the situation where we compare
 * two nodes, and the "smallest" one is the head of the other list. The other situation, (1) above, is even
 * more simple. If the smallest of the two nodes we're looking at's next value is smaller than the other node,
 * we simple increment its pointer to that next, and go head with the next iteration, considering the next pair
 * of nodes. Work through a few examples like this to see that this works correctly. Of course we're eventually
 * going to run out of nodes in our lists, so lets see what happens when some of the nodes we want to compare are
 * NULL:
 *
 * 1 -> x
 * 2 -> 3
 *
 * Here, we start with comparing `1` and `2`. `1` is obviously the smaller node. We would normally compare 1->next
 * with `2` to find the next smallest node, however since 1->next is NULL, and we still have nodes in the other list,
 * we can never choose 1->next as the "smallest". How about the situation in which a node we wish to compare is NULL?
 *
 * 1 -> 2 -> x
 * x
 *
 * In this situation, we'd normally compare `1` with the other node, to find the smallest at this frame, however the
 * other node is NULL. Clearly, the only thing worth doing here is stopping. You might think "oh this is an edge case
 * we'd catch before we even start any of our fancy logic", and that's true in this specific situation, but it is still
 * (50% likely?) possible that we run into this situation towards the end of our fancy logic! Consider the case that before
 * `x`, was 0. We'd set 0->next = `1`, and then increment `0` to `x`. Now since 0->next = 1, which contains the rest of the
 * possible elements we could include, we don't need to do anything here but stop. We can actually avoid getting into this
 * useless place by ensuring that our loop of logic only runs when _both_ current list heads that we maintain are non-NULL,
 * and if either becomes NULL, we can stop. At the end of all of our logic, we'll want to look at the original input list
 * nodes we've gotten, and return the one with the smallest value, as that is the one we would have chosen in the very
 * beginning of our logic.
 *
 * Complexity analysis:
 * Time complexity: O(n + m), where n & m are the sizes of the two input lists
 * Space complexity: O(1)
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
Node<T>* mergeTwoLists(Node<T> *l1, Node<T> *l2) {
  Node<T> *curr1 = l1, *curr2 = l2, *tmp, *potentialNext;
  if (!l1 && !l2) return NULL;
  if (!l1 || !l2) return (l1) ? l1 : l2;

  while (curr1 && curr2) {
    if (curr1->val <= curr2->val) {
      potentialNext = curr1->next;
      if (potentialNext && potentialNext->val <= curr2->val) {
        curr1 = curr1->next;
      } else {
        tmp = curr1->next;
        curr1->next = curr2;
        curr1 = tmp;
      }
    } else {
      potentialNext = curr2->next;
      if (potentialNext && potentialNext->val < curr1->val) {
        curr2 = curr2->next;
      } else {
        tmp = curr2->next;
        curr2->next = curr1;
        curr2 = tmp;
      }
    }
  }

  return (l1->val <= l2->val) ? l1 : l2;
}

int main() {
  Node<int> *head1 = new Node<int>(2);
  head1->next = new Node<int>(4);

  Node<int> *head2 = new Node<int>(1);
  head2->next = new Node<int>(3);

  head1 = mergeTwoLists(head1, head2);
  printList(head1);

  deleteList(head1);
  return 0;
}

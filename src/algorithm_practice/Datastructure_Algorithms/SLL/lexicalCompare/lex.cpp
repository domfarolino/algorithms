#include <iostream>

using namespace std;

// Source: http://www.geeksforgeeks.org/compare-two-strings-represented-as-linked-lists/

/**
 * The goal is to write a function that takes in the heads
 * to two linked lists that represent strings and determine which
 * string if any is lexicographically greater than the other. Each
 * node in the list represents a single character. If string `a` is
 * lexicographically greater than string `b` return 1, if string b is
 * lexicographically greater than string a return -1 and if they are both
 * lexicographically identical return 0.
 *
 * This should be a fairly simple algorithm we can write both iteratively and
 * recursively. The idea is to keep traversing both linked lists until the characters
 * we analyzing in each string are not equal. If both characters are NULL at some point
 * then the strings are equal. This will be the base case for our recursive algorithm, and
 * the while-loop condition for our iterative algorithm. If both characters are equal we need
 * to keep moving forward. In the iterative algorithm this means we advance both list pointers
 * forward and re-evaluate. In the recursive case, the analagous operation is to call the function
 * again with the next node from each list. Note the recursive algorithm will be tail recursive so
 * we will not see any accumulating stack frames. We'll see this in our space complexity analysis.
 * a.)
 *    keep on traversing if chars are equal
 * b.)
 *    if one char is lexicographically greater than other, return appropriate integer
 *
 * Note in the recursive case b
 *
 * Complexity analysis:
 * Time complexity: O(n) where n is length of the shortest list
 * Space complexity: O(1) (iterative & tail recursive)
 */

struct Node {
  char val;
  Node *next;
  Node(char inVal, Node *inNext = NULL): val(inVal), next(inNext) {}
};

int compareStringsIterative(Node *a, Node *b) {
  Node *currA = a, *currB = b;

  while (currA && currB) {
    if (currA->val > currB->val) return 1;
    else if (currB->val > currA->val) return -1;
    else {
      currA = currA->next;
      currB = currB->next;
    }
  }

  if (currA) return 1;
  else if (currB) return -1;
  else return 0;
}

int compareStringsRecursive(Node *a, Node *b) {
  if (!a || !b) {
    if (a) return 1;
    if (b) return -1;
    else return 0;
  } else {
    if (a->val > b->val) return 1;
    if (a->val < b->val) return -1;
    else return compareStringsRecursive(a->next, b->next);
  }
}

void deleteList(Node *head) {
  Node *tmp;

  while (head) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}

int main() {
  Node *a = new Node('d');
  a->next = new Node('f');
  a->next->next = new Node('f');
  a->next->next->next = new Node('g');

  Node *b = new Node('d');
  b->next = new Node('f');
  b->next->next = new Node('f');
  b->next->next->next = new Node('g');

  cout << compareStringsIterative(a, b) << endl;
  cout << compareStringsRecursive(a, b) << endl;

  deleteList(a);
  deleteList(b);
  return 0;
}

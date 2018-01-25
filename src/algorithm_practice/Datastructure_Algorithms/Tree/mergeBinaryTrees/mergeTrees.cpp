#include <iostream>

// Source: https://leetcode.com/problems/merge-two-binary-trees/

/**
 * Merge two binary trees
 * This problem can be written as a fairly simple DFS algorithm.
 * In this algorithm I'm opting to build and return a completely
 * new tree so that we're not modifying any preexisting pointers.
 *
 * Basically if the two tree roots passed in are NULL we want to
 * return NULL, this will be our base case. If both roots are non-NULL
 * then we want to return a new node whose internal data is the sum of
 * both of the passed-in roots data. The left child of this new node should
 * be set to the result of the function called recursively on the two roots'
 * left children. The same goes for the right. The final case we have to cater
 * for is where only one of the roots is NULL. In this case, the internal data
 * of the newly created node we'll return is obvious (will be set to the data of
 * the existing node). It's left and right children however should be set to the
 * result of the function called recursively on the existing root's left and right
 * child respectively, and NULL for the non-existing root (since a NULL node doesn't
 * have any children so we can't attempt to dereference it etc).
 *
 * Time complexity: O(n), where n = size in nodes, of the larger tree
 * Space complexity: O(n), as we may recurse n times in the case of a linear tree
 */

template <typename T>
struct Node {
  T data;
  Node *left, *right;
  Node(int inData): data(inData), left(NULL), right(NULL) {}
};

template <typename T>
Node<T>* mergeTrees(Node<T> *a, Node<T> *b) {
  if (!a && !b) return NULL;
  Node<T> *newNode = new Node<T>(0);
  if (a && b) {
    newNode->data = a->data + b->data;
    newNode->left = mergeTrees(a->left, b->left);
    newNode->right = mergeTrees(a->right, b->right);
  } else if (a) {
    newNode->data = a->data;
    newNode->left = mergeTrees(a->left, b);
    newNode->right = mergeTrees(a->right, b);
  } else if (b) {
    newNode->data = b->data;
    newNode->left = mergeTrees(a, b->left);
    newNode->right = mergeTrees(a, b->right);
  }

  return newNode;
}

template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

template <typename T>
void printTree(Node<T> *root) {
  if (!root) return;
  printTree(root->left);
  printTree(root->right);
  std::cout << root->data << std::endl;
}

int main() {
  Node<int> *head = new Node<int>(3);
  head->left = new Node<int>(1);
  head->right = new Node<int>(1);

  Node<int> *head2 = new Node<int>(2);

  Node<int> *newRoot = mergeTrees(head, head2);
  printTree(newRoot);
  deleteTree(newRoot);
  deleteTree(head);
  deleteTree(head2);
  return 0;
}

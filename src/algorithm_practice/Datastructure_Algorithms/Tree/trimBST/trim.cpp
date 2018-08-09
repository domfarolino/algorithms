#include <iostream>

// Source: https://leetcode.com/problems/trim-a-binary-search-tree/

/**
 * The goal of this algorithm is to take in a binary search tree, and
 * a lower and upper bound (integers), and trim the BST such that all
 * nodes in the remaining tree are within (inclusive) the given bounds.
 * TODO(domfarolino): Finish docs.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inVal): val(inVal), left(NULL), right(NULL) {}
};

template <typename T>
Node<T>* trimBST(Node<T>* root, int L, int R) {
  if (!root) return nullptr;
  Node<T> *nextRoot;
  if (root->val < L) {
    nextRoot = root->right;
    deleteSelfAndLeft(root);
    return trimBST(nextRoot, L, R);
  } else if (root->val > R) {
    nextRoot = root->left;
    deleteSelfAndRight(root);
    return trimBST(nextRoot, L, R);
  } else {
    root->left = trimBST(root->left, L, R);
    root->right = trimBST(root->right, L, R);
    return root;
  }
}

/**
 * Utility functions to delete binary trees and/or branches
 */
template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

template <typename T>
void deleteSelfAndLeft(Node<T> *root) {
  if (!root) return;
  deleteSelfAndLeft(root->left);
  delete root;
}

template <typename T>
void deleteSelfAndRight(Node<T>* root) {
  if (!root) return;
  deleteSelfAndRight(root->right);
  delete root;
}

int main() {
  Node<int> *root = new Node<int>(3);
  root->left = new Node<int>(0);
  root->right = new Node<int>(4);

  root->left->right = new Node<int>(2);
  root->left->right->left = new Node<int>(1);

  root = trimBST(root, 2, 4);
  
  // TODO(domfarolino): OJ is correct, but it would be
  // nice to provide some sort of verification here too
  deleteTree(root);
  return 0;
}

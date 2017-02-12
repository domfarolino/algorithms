#include <iostream>
#include <climits>

using namespace std;

// Source: https://www.hackerrank.com/challenges/ctci-is-binary-search-tree

/**
 * Write an algorithm to determine whether or not a binary tree
 * starting at a given root pointer is also a binary search tree.
 * In this case a binary search tree may not contain any duplicates.
 * It is all too easy to simply perform a single check on each node to
 * make sure left child < root and right child > root however this is not
 * sufficient. The value of a BST node does not only depend on the value of
 * its immediate parent but all of its previous ancestors. This means we'll
 * have to maintain some boundaries that a given node must exist within so we
 * can perform a valid check. As we go further and further down the tree the min
 * and max bounds for each node should tighten. Starting with the base case the root
 * node's value can be anywhere between INT_MIN and INT_MAX assuming the nodes have integer
 * values. It is convenient to consider an empty tree a valid BST, especially for our base case.
 * If the root doesn't exist we can return true. If it does, we'll simply need to compare its value
 * to the given min and max bounds. Note we'll need to pass in the proper min and max bounds to each
 * frame instead of letting the frames determine them, because the min and max bounds are determined
 * based on whether we go left or right from some node and we only know that information before we make
 * the move. In other words, a given node doesn't know whether or not it is its parent's left or right
 * child. The rest is a basic in order DFS traversal.
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

bool isBST(Node<int> *root, int min = INT_MIN, int max = INT_MAX) {
  if (!root) return true;
  if (root->val > min && root->val < max) {
    return isBST(root->left, min, root->val) && isBST(root->right, root->val, max);
  }

  return false;
}

template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

int main() {
  Node<int> *root = new Node<int>(5);
  root->left = new Node<int>(3);
  root->right = new Node<int>(60);

  cout << isBST(root) << endl;

  deleteTree(root);
  return 0;
}

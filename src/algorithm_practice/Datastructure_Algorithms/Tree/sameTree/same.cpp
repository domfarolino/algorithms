#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/same-tree/

/**
 * The goal of this algorithm is to determine whether two
 * given trees are the "same", meaning all values at all positions
 * are equivalent in both trees. The algorithm is relatively straight-forward
 * in that we basically need to compare the root values, and recurse with the two
 * subtrees incurred at each node. At each frame we should check for symmetric null
 * pointer existence as our base case. The basic idea of breaking the problem down to
 * equivalene checks and subtrees is very similar to `symmetricTree`.
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
bool isSameTree(Node<T> *root1, Node<T> *root2) {
  if (!root1 && !root2) return true;
  if (!root1 || !root2) return false;
  return (root1->val == root2->val) && isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right);
}

/**
 * Utility function to delete binary tree
 */
template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

int main() {
  Node<int> *root1 = new Node<int>(0);
  root1->left = new Node<int>(1);

  Node<int> *root2 = new Node<int>(0);
  root1->right = new Node<int>(2);
  root2->left = new Node<int>(1);
  root2->right = new Node<int>(2);

  cout << isSameTree(root1, root2) << endl;

  deleteTree(root1);
  deleteTree(root2);
  return 0;
}

#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/invert-binary-tree/

/**
 * The recursive version of this algorithm is very simple.
 * Basically for every single node, we want to swap the node's
 * left and right child pointers, invert the child subtrees and
 * then return the original node.
 * Time complexity: O(n) - since we have to touch all of the nodes
 * Space complexity: O(h) - where h is the height of the tree. This
 * value could be O(log(n)) if the tree is complete or perfect.
 */

template <typename T>
struct TreeNode {
  T val;
  TreeNode<T> *left, *right;
  TreeNode(T inputVal, TreeNode<T> *inputLeft = NULL, TreeNode<T> *inputRight = NULL): val(inputVal), left(inputLeft), right(inputRight) {}
};

// Utility function to delete a binary tree
template <typename T>
void deleteTree(TreeNode<T>* node) {
  if (!node) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
  node = NULL;
}

// Time complexity: O(n)
// Space complexity: O(h) where h = height of tree
template <typename T>
void invertHelper(TreeNode<T>* node) {
  if (!node) return;
  TreeNode<T>* tmpNode = node->left;
  node->left = node->right;
  node->right = tmpNode;
  invertHelper(node->left);
  invertHelper(node->right);
}

// Function to call recursive helper
template <typename T>
TreeNode<T>* invertBinaryTree(TreeNode<T>* root) {
  if (!root) return NULL;
  invertHelper(root);
  return root;
}

int main() {
  TreeNode<int> *root = new TreeNode<int>(1);
  root->left = new TreeNode<int>(2);
  root->right = new TreeNode<int>(3);

  cout << "root: " << root->val << "\nleft: " << root->left->val << "\nright: " << root->right->val << endl;

  root = invertBinaryTree(root);

  cout << "root: " << root->val << "\nleft: " << root->left->val << "\nright: " << root->right->val << endl;

  deleteTree(root);
  return 0;
}

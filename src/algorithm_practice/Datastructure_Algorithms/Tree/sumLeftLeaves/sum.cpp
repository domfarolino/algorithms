#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/sum-of-left-leaves/

/**
 * Often a regular DFS algorithm will call itself on both
 * root->left and root->right. Finally when we hit some NULL
 * root, we return 0 or something like that. In this case, we're
 * only interested in left-leaves. This means we need to know that
 * some leaf was a left child of its parent, and we can only know this
 * if we catch it before we hit our base case. So every time root->left
 * exists, we need to check if it is a leaf. If so, take its value and add
 * it to recursiveAlgorithm(root->right). If not, we call the algorithm in
 * a regular DFS in-order fashion. Note that we're not doing any checking for
 * right leaves. This means the only leaves that we'll call our algorithm on will
 * be right leaves, which will eventually trigger out base case and return 0.
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int sumOfLeftLeaves(TreeNode* root) {
  if (!root) return 0;

  if (root->left && !root->left->left && !root->left->right) {
    return root->left->val + sumOfLeftLeaves(root->right);
  } else {
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
  }
}

int main() {
  // Simple example. See OJ for better cases
  TreeNode* root = new TreeNode(4);
  root->left = new TreeNode(5);
  root->right = new TreeNode(6);

  cout << sumOfLeftLeaves(root) << endl;

  delete root->left;
  delete root->right;
  delete root;
  return 0;
}

// Source: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
TreeNode* findValue(TreeNode* root, int val) {
  if (!root) return nullptr;

  if (root->val > val)
    return findValue(root->left, val);
  else if (root->val < val)
    return findValue(root->right, val);
  else return root;
}

bool findTarget(TreeNode* root, int val) {
  return findTarget(root, val, root);
}

bool findTarget(TreeNode* root, int val, TreeNode *realRoot) {
  if (!root) return false;
  int complement = val - root->val;

  TreeNode *complementNode = findValue(realRoot, complement);
  if (complementNode && complementNode != root)
    return true;
  else return findTarget(root->left, val, realRoot) || findTarget(root->right, val, realRoot);
}
};

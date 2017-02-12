// Source: https://leetcode.com/problems/same-tree/
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
    bool isSameTree(TreeNode *root1, TreeNode *root2) {
      if (!root1 && !root2) return true;
      if (!root1 || !root2) return false;
      return (root1->val == root2->val) && isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right);
    }
};

// Source: https://leetcode.com/problems/symmetric-tree/
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
    bool isSymmetric(TreeNode *root) {
      if (!root) return true;
      if (!root->left && !root->right) return true;
      if (!root->left || !root->right) return false;

      return subtreesSymmetric(root->left, root->right);
    }

    bool subtreesSymmetric(TreeNode *left, TreeNode *right) {
      if (!left && !right) return true;
      if (!left || !right) return false;
      return (left->val == right->val) && subtreesSymmetric(left->left, right->right) && subtreesSymmetric(left->right, right->left);
    }
};

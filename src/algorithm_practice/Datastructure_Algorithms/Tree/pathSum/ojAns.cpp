// Source: https://leetcode.com/problems/path-sum/
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
    bool hasPathSum(TreeNode *root, int k, int sum = 0) {
      if (!root) return false;
      if (!root->left && !root->right) {
        return k == (sum + root->val);
      } else return hasPathSum(root->left, k, sum + root->val) || hasPathSum(root->right, k, sum + root->val);
    }
};

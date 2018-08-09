// Source: https://leetcode.com/problems/trim-a-binary-search-tree/

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
TreeNode* trimBST(TreeNode* root, int L, int R) {
  if (!root) return nullptr;
  TreeNode *nextRoot;
  if (root->val < L) {
    nextRoot = root->right;
    return trimBST(nextRoot, L, R);
  } else if (root->val > R) {
    nextRoot = root->left;
    return trimBST(nextRoot, L, R);
  } else {
    root->left = trimBST(root->left, L, R);
    root->right = trimBST(root->right, L, R);
    return root;
  }
}
};

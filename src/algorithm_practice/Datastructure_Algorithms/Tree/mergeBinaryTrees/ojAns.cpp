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
    TreeNode* mergeTrees(TreeNode* a, TreeNode* b) {
        if (!a && !b) return NULL;
        TreeNode *newNode = new TreeNode(0);
        if (a && b) {
            newNode->val = a->val + b->val;
            newNode->left = mergeTrees(a->left, b->left);
            newNode->right = mergeTrees(a->right, b->right);
        } else if (a) {
            newNode->val = a->val;
            newNode->left = mergeTrees(a->left, b);
            newNode->right = mergeTrees(a->right, b);
        } else if (b) {
            newNode->val = b->val;
            newNode->left = mergeTrees(a, b->left);
            newNode->right = mergeTrees(a, b->right);
        }

        return newNode;
    }
};

// Source: https://leetcode.com/problems/binary-tree-paths/
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
    void allPathsTraversal(TreeNode *root, vector<string>& paths, string base) {
      string newBase = base + to_string(root->val);
      if (!root->left && !root->right) paths.push_back(newBase);
      if (root->left) allPathsTraversal(root->left, paths, newBase + "->");
      if (root->right) allPathsTraversal(root->right, paths, newBase + "->");
    }

    vector<string> binaryTreePaths(TreeNode *root) {
      vector<string> returnVec;
      if (!root) return returnVec;

      allPathsTraversal(root, returnVec, "");

      return returnVec;
    }
};

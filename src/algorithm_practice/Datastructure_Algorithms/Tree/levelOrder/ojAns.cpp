// Source: https://leetcode.com/problems/binary-tree-level-order-traversal/
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
    vector<vector<int> > levelOrder(TreeNode *root) {
      vector<vector<int> > returnVec;
      if (!root) return returnVec;

      queue<TreeNode* > q;
      q.push(root);
      int count;

      while (q.size()) {
        count = q.size();
        vector<int> currentLevel;

        while (count) {
          currentLevel.push_back(q.front()->val);
          if (q.front()->left) q.push(q.front()->left);
          if (q.front()->right) q.push(q.front()->right);
          q.pop();
          count--;
        }

        returnVec.push_back(currentLevel);
      }

      return returnVec;
    }
};

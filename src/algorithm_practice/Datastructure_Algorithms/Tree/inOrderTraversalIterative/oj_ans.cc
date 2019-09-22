// This was my original approach to the problem. In some ways it is more
// intuitive to me, though introduces an extra stack unnecessarily.
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
  vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> visited;
    if (!root) return visited;
    std::stack<TreeNode*> untouched, right_child_to_visit;
    untouched.push(root);

    TreeNode* top;
    while (untouched.size() || right_child_to_visit.size()) {
      if (untouched.size()) {
        top = untouched.top();
        untouched.pop();
        if (top->left)
          untouched.push(top->left);
        right_child_to_visit.push(top);
      } else {
        // Assert |right_child_to_visit.size()|.
        top = right_child_to_visit.top();
        visited.push_back(top->val);
        if (top->right)
          untouched.push(top->right);
        right_child_to_visit.pop();
      }
    }

    return visited;
  }
};

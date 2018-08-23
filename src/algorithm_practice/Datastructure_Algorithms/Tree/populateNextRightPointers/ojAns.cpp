// Source: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode *curr = root, *tmp = curr;
        while (curr && curr->left) { // # of levels
            tmp = curr;
            while (tmp) { // # of nodes in given level
                tmp->left->next = tmp->right;
                if (tmp->next) tmp->right->next = tmp->next->left;
                tmp = tmp->next;
            }
            curr = curr->left;
        }
    }
};

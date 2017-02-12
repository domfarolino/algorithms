// Source: https://www.hackerrank.com/challenges/ctci-is-binary-search-tree
/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/

#include <climits>

   bool checkBST(Node* root, int min = INT_MIN, int max = INT_MAX) {
     if (!root) return true;
     if (root->data > min && root->data < max) {
       return checkBST(root->left, min, root->data) && checkBST(root->right, root->data, max);
     }

     return false;
   }

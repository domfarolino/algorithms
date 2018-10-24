#include <iostream>

// Source: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inVal): val(inVal), left(NULL), right(NULL) {}
};

/**
 * Utility function to delete a binary tree
 */
template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

template <typename T>
Node<T>* findValue(Node<T>* root, T val) {
  if (!root) return nullptr;

  if (root->val > val)
    return findValue(root->left, val);
  else if (root->val < val)
    return findValue(root->right, val);
  else return root;
}

template <typename T>
bool twoSum(Node<T>* root, Node<T>* realRoot, T val) {
  if (!root) return false;
  int complement = val - root->val;

  Node<T> *complementNode = findValue(realRoot, complement);
  if (complementNode && complementNode != root)
    return true;
  else return twoSum(root->left, realRoot, val) || twoSum(root->right, realRoot, val);
}

int main() {
/*
      5
    /   \
   4     6
          \
           8
*/

  Node<int> *root = new Node<int>(5);
  root->left = new Node<int>(4);
  root->right = new Node<int>(6);
  root->right->right = new Node<int>(8);

  std::cout << twoSum(root, root, 14) << std::endl;
  std::cout << twoSum(root, root, 12) << std::endl;
  std::cout << twoSum(root, root, 10) << std::endl;
  std::cout << twoSum(root, root, 9) << std::endl;
  std::cout << twoSum(root, root, 48) << std::endl;
  delete(root);
  return 0;
}

#include <iostream>
#include <vector>

// Source: https://leetcode.com/problems/leaf-similar-trees/description/

/**
 * Leaf-Similar Trees
 * This problem is relatively straight-forward, so not much description
 * is included here.
 *
 * Complexity analysis:
 * Time complexity: O(n + m); n = sizeOfTree1, m = sizeOfTree2
 * Space complexity: O(n + m); // imagine the case where our stack frames get as long as the trees
 */

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inVal): val(inVal), left(NULL), right(NULL) {}
};

template <typename T>
void getLeaves(Node<T> *root, std::vector<T>& leaves) {
  if (!root) return;
  getLeaves(root->left, leaves);
  getLeaves(root->right, leaves);
  if (!root->left && !root->right) leaves.push_back(root->val);
}

template <typename T>
bool leafSimilar(Node<T> *root1, Node<T> *root2) {
  std::vector<T> leaves1, leaves2;
  getLeaves(root1, leaves1);
  getLeaves(root2, leaves2);
  if (leaves1.size() != leaves2.size()) return false;

  for (int i = 0; i < leaves1.size(); ++i) {
    if (leaves1[i] != leaves2[i]) return false;
  }

  return true;
}

/**
 * Utility function to delete binary tree
 */
template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

int main() {
  Node<int> *root1 = new Node<int>(9);
  root1->left = new Node<int>(9);
  root1->left->left = new Node<int>(1);
  root1->left->right = new Node<int>(2);

  Node<int> *root2 = new Node<int>(9);
  root2->right = new Node<int>(9);
  root2->right->left = new Node<int>(1);
  root2->right->right = new Node<int>(2);

  std::cout << leafSimilar(root1, root2) << std::endl;

  deleteTree(root1);
  deleteTree(root2);
  return 0;
}

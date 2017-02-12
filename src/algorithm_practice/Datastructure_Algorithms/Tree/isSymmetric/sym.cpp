#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/symmetric-tree/

/**
 * The goal of this algorithm is to write an algorithm that determines whether
 * or not a tree is symmetric. We'll be taking in a tree root pointer and returning
 * a boolean. We'll be calling the equal operator on the value inside each node so an
 * assumption we'd be making is that the given type of data can has an equal operator.
 * With recursive binary tree problems I've found it helpul to visualize the algorithm
 * running on a tree with zero nodes and a tree whose root has exactly two immediate
 * children. We can say a tree consisting of zero nodes is symmetric. Given a tree with
 * two immediate children we need to make sure
 *    1.) The subtree root values are equivalent
 *    2.) The next two subtrees are symmetric.
 *
 * It is clear that two subtrees can only be symmetric if their root values are equal. Once
 * we pass this we must of course compare left->left with right->right and left->right with right->left.
 * We know the first thing (besides base case null pointer checks) we do is compare the values of two subtree
 * roots so we can just re-use our function for the two new subtrees we incurre at each level. This recursion allows
 * us to perform the necessary breadth expansion we need in order to check symmetry!
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n) - technically ~(n/2) I believe?
 */

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inVal): val(inVal), left(NULL), right(NULL) {}
};

/**
 * Only responsibility of this function
 * is to take in a single root node and determine
 * whether we can even try and tell whether its subtrees
 * are both symmetric with each other.
 */
template <typename T>
bool isSymmetric(Node<T> *root) {
  if (!root) return true;
  return subtreesSymmetric(root->left, root->right);
}

template <typename T>
bool subtreesSymmetric(Node<T> *left, Node<T> *right) {
  if (!left && !right) return true;
  if (!left || !right) return false;
  return (left->val == right->val) && subtreesSymmetric(left->left, right->right) && subtreesSymmetric(left->right, right->left);
}

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

int main() {
  Node<int> *root = new Node<int>(0);
  root->left = new Node<int>(1);
  root->right = new Node<int>(1);
  // root->left->left = new Node<int>(2); not symmetric

  cout << isSymmetric(root) << endl;

  deleteTree(root);
  return 0;
}

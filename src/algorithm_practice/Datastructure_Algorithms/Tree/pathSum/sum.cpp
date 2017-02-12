#include <iostream>

using namespace std;

// Source: https://leetcode.com/problems/path-sum/

/**
 * The goal of this algorithm is to determine whether or not a tree has
 * at least one root-to-leaf path such that the sum of all node values on
 * the path is equal to some integer `k`. We'll be given a root pointer and
 * int `k`, and must return a boolean. Note the node values may be negative so
 * it is not possible to stop part-way through a path if the sum > k. The algorithm
 * requires us to pass in a running `sum` to each recursive frame keeping track of the
 * current path sum. When we reach a leaf node we'll want to evaluate the "final" sum. This
 * pretty much carves out our base case and recursion calls. Evaluating the order of things is
 * where I first screwed up. I first assumed we could consider our running sum = 0 in the first
 * call and check to see if the root exists. If it doesn't we'd return whether the sum == k or not.
 * This made sense to me because we could of course get the function called with a NULL root, so it
 * would be redundant to check for root existence AND isLeaf (check if both children are NULL too) since
 * we'd be duplicating conditionals as we recurse through the tree. So my first totally naive thought was
 * to only check root existence however the issue is that being called with NULL root does NOT guarantee that
 * the parent node is a leaf, since we know NOTHING about its other child! My solution was to have two functions
 * one of which checked initial root existence, and then another function that would only get called if the root was
 * gauranteed not NULL. This allowed me to not duplicate root and leaf NULL checking at each level. The rest of the logic
 * is pretty straight forward. Note it is easy to see once the function is written that the duplicate conditionals are techinically
 * still duplicated. This is because I have to check leaf status (left && right), but also have to check to see if I can even call
 * my recursive helper on the children (since we have a contract that the root of any call will always exist). This is why I decided
 * to go with the duplicated logic anyways and simplify the solution to one function.
 *
 * The above sequence of thoughts I found interesting because it is similar to "off by one" errors, in that it can be confusing
 * in a repetitive process to figure out how to initialize some things and when to check others. If we try to make determinations
 * too late as I initially did above, a given frame does not know enough about its sibling frame to make the correct call. This is
 * why we had to shift some of the logic "up" a frame figuratively speaking. This means the running sum at any given point is only
 * as up to date as the last frame, so if the current node is a leaf we have to check whether the sum (init 0) + root->val == k.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inVal): val(inVal), left(NULL), right(NULL) {}
};

bool pathSum(Node<int> *root, int k, int sum = 0) {
  if (!root) return false;
  if (!root->left && !root->right) {
    return k == (sum + root->val);
  } else return pathSum(root->left, k, sum + root->val) || pathSum(root->right, k, sum + root->val);
}

template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

int main() {
  Node<int> *root = new Node<int>(1);
  root->left = new Node<int>(5);
  root->right = new Node<int>(4);
  root->left->left = new Node<int>(3);
  root->right->left = new Node<int>(-1);

  cout << pathSum(root, 4) << endl;

  deleteTree(root);
  return 0;
}

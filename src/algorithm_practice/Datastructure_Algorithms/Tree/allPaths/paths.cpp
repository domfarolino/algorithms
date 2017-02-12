#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Source: https://leetcode.com/problems/binary-tree-paths/

/**
 * Write an algorithm to return a vector of strings which denote
 * all root->leaf paths given some binary tree. This can easily be
 * seen with examples.
 *
 *
 *        1
 *      2   3
 *    4  5
 *
 * The algorithm run on the above tree would return ["1->2->4", "1->2->5", "1->3"].
 * Note that whenever we come across a node that is not a leaf, that node's value becomes
 * the next node in the string for ALL paths under it. This means it might nake sense to carry
 * some sort of base string with us at each frame denoting the current string "base". We keep adding
 * to it and when we come across a node who is a leaf, we add once more and push the string onto our
 * vector. This tells me that we'll need two functions. One function will maintain a vector which gets
 * passed by reference into another function which is responsible for recursing and pushing completed
 * bases to the vector. When recursing ceases we can return the finished vector.
 *
 * Complexity analysis:
 * Time complexity: O(n) - basic DFS traversal with some string memory
 * Space complexity: O(n)
 */

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inVal): val(inVal), left(NULL), right(NULL) {}
};

void allPathsTraversal(Node<int> *root, vector<string>& paths, string base) {
  string newBase = base + to_string(root->val);
  if (!root->left && !root->right) {
    paths.push_back(newBase);
    return;
  }

  if (root->left) allPathsTraversal(root->left, paths, newBase + "->");
  if (root->right) allPathsTraversal(root->right, paths, newBase + "->");
}

vector<string> allPaths(Node<int> *root) {
  vector<string> returnVec;
  if (!root) return returnVec;

  allPathsTraversal(root, returnVec, "");
  return returnVec;
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
  root->left = new Node<int>(2);
  root->right = new Node<int>(3);
  root->left->left = new Node<int>(4);
  root->left->right = new Node<int>(5);

  vector<string> paths = allPaths(root);

  for (int i = 0; i < paths.size(); ++i) {
    cout << paths[i] << endl;
  }

  deleteTree(root);
  return 0;
}

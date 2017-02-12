#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Source: https://leetcode.com/problems/binary-tree-level-order-traversal/

/**
 * Given a binary tree return a vector of vectors where each nested
 * vector contains the values of each node at a particular level. The
 * process we want to follow is just like a regular breadth first search
 * with the exception that we want to keep track of where each level starts
 * and stops. This can be done from the very beginning by keeping a "count" of
 * how many nodes exist at each level. The algorithm is very similar to the one
 * in the following write-up: https://blog.domfarolino.com/Leetcode-Binary-Tree-Right-Side-View-Algorithm/.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(n) - technically ~(n/2)
 */

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inVal): val(inVal), left(NULL), right(NULL) {}
};

template <typename T>
vector<vector<T> > levelOrder(Node<T> *root) {
  vector<vector<T> > returnVec;
  if (!root) return returnVec;

  queue<Node<T>* > q;
  q.push(root);
  int count;

  while (q.size()) {
    count = q.size();
    vector<T> currentLevel;

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
  root->left->left = new Node<int>(2);
  root->left->right = new Node<int>(2);

  vector<vector<int> > levelVec = levelOrder(root);

  for (int i = 0; i < levelVec.size(); ++i) {
    for (int j = 0; j < levelVec[i].size(); ++j) {
      cout << levelVec[i][j] << endl;
    }

    cout << endl;
  }

  deleteTree(root);
  return 0;
}

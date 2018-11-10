#include <iostream>
#include <vector>
#include <map>

// Source: https://careercup.com/question?id=5709428993556480

/**
 * Documentation can be found for this problem in the README in
 * this directory.
 */

template <typename T>
struct Node {
  T data;
  Node<T> *left, *right;
  Node(T inData): data(inData), left(nullptr), right(nullptr) {}
};

template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);

  delete root;
}

template <typename T>
void columnWise(Node<T> *root, std::map<int, std::vector<T>>& columns, int column = 0) {
  if (!root) return;

  // Visit root.
  columns[column].push_back(root->data);

  // Recurse on children.
  columnWise(root->left, columns, column - 1);
  columnWise(root->right, columns, column + 1);
}

int main() {
  // This algirithm has also been tested with other trees and edge cases, this
  // is just a simple example.
  Node<int> *root = new Node<int>(6);
  root->left = new Node<int>(9);
  root->right = new Node<int>(4);

  root->left->left = new Node<int>(5);
  root->left->right = new Node<int>(1);
  root->left->left->right = new Node<int>(0);

  root->right->right = new Node<int>(3);
  root->right->right->left = new Node<int>(7);

  std::map<int, std::vector<int>> columns;
  columnWise(root, columns);

  std::map<int, std::vector<int>>::const_iterator it = columns.begin();
  while (it != columns.end()) {
    std::cout << "Col: " << it->first << std::endl;
    for (int nodeVal: it->second) {
      std::cout << nodeVal << ", ";
    }

    std::cout << std::endl;
    it++;
  }

  deleteTree(root);
  return 0;
}

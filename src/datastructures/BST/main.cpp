#include <iostream>
#include <vector>
#include <cstdlib>
#include <assert.h>

#include "BST.h"

void addAndSize() {
  BST<int> tree;

  for (int i = 0; i < 50; ++i) {
    assert(tree.size() == i);
    tree.add(rand());
  }
}

void addAndEmpty() {
  BST<int> tree;
  assert(tree.empty());
  tree.add(1);
  assert(!tree.empty());
  tree.add(2);
  assert(!tree.empty());
}

void removeAndSize() {
  BST<int> tree1;
  BST<int> tree2;
  std::vector<int> vec;
  const int treeSize = 200;

  for (int i = 0; i < treeSize; ++i) {
    vec.push_back(rand() % 2000);
    tree1.add(vec[vec.size() - 1]);
    tree2.add(vec[vec.size() - 1]);
  }

  int indexToRemove;
  for (int i = treeSize - 1; i >= 0; --i) {
    indexToRemove = rand() % vec.size();

    tree1.remove(vec[indexToRemove]);
    tree2.removeIterative(vec[indexToRemove]);
    vec.erase(vec.begin() + indexToRemove);

    assert(tree1.size() == i);
    assert(tree2.size() == i);
  }
}

void removeAndEmpty() {
  BST<int> tree1;
  BST<int> tree2;
  tree1.add(1);
  tree2.add(1);
  tree1.add(2);
  tree2.add(2);

  assert(!tree1.empty());
  assert(!tree2.empty());
  tree1.remove(1);
  tree2.remove(1);
  assert(!tree1.empty());
  assert(!tree2.empty());
  tree1.remove(2);
  tree2.remove(2);
  assert(tree1.empty());
  assert(tree2.empty());
  tree1.remove(2);
  tree2.remove(2);
  assert(tree1.empty());
  assert(tree2.empty());
}

void inorder() {
  BST<int> tree;

  for (int i = 0; i < 100; ++i) {
    tree.add(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();
  int curr = inorder[0];

  assert(tree.size() == inorder.size());

  for (int i = 0; i < inorder.size(); ++i) {
    assert(inorder[i] >= curr);
    curr = inorder[i];
  }
}

void inorderExists() {
  BST<int> tree;

  for (int i = 0; i < 100; ++i) {
    tree.add(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();

  for (int i = 0; i < inorder.size(); ++i) {
    assert(tree.exists(inorder[i]));
  }
}

void minAndMax() {
  BST<int> tree;

  for (int i = 0; i < 100; ++i) {
    tree.add(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();

  assert(tree.min()->val == inorder[0]);
  assert(tree.max()->val == inorder[inorder.size() - 1]);
}

void bfs() {
  BST<int> tree;

  std::vector<int> nodesToAdd = {5, 3, 7, 2, 4, 6, 8};

  for (int i = 0; i < nodesToAdd.size(); ++i) {
    tree.add(nodesToAdd[i]);
  }

  assert(tree.bfs() == nodesToAdd);
}

int main() {
  srand(time(NULL));

  addAndSize();
  addAndEmpty();
  removeAndSize();
  removeAndEmpty();
  inorder();
  inorderExists();
  minAndMax();
  bfs();

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

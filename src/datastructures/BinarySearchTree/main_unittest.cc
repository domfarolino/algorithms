#include <cstdlib> // rand()

#include "gtest/gtest.h"
#include "BinarySearchTree.h"

class BinarySearchTreeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    srand(time(NULL));
  }

  BinarySearchTree<int> tree;
};

TEST_F(BinarySearchTreeTest, InitiallyEmpty) {
  ASSERT_TRUE(tree.empty());
}

TEST_F(BinarySearchTreeTest, AddAndNotEmpty) {
  tree.Insert(10);
  ASSERT_FALSE(tree.empty());
  tree.Insert(20);
  ASSERT_FALSE(tree.empty());
}

TEST_F(BinarySearchTreeTest, AddAndSize) {
  for (int i = 0; i < 50; ++i) {
    ASSERT_EQ(tree.size(), i);
    tree.Insert(rand());
  }
}

TEST_F(BinarySearchTreeTest, RemoveAndSize) {
  const int tree_size = 200;

  // |tree| will be used to test BinarySearchTree::Remove and |tree_iterative|
  // will be used to test BinarySearchTree::RemoveIterative.
  BinarySearchTree<int> tree_iterative;

  std::vector<int> vec;

  for (int i = 0; i < tree_size; ++i) {
    vec.push_back(rand() % 2000);
    tree.Insert(vec[vec.size() - 1]);
    tree_iterative.Insert(vec[vec.size() - 1]);
  }

  int indexToRemove;
  for (int i = tree_size - 1; i >= 0; --i) {
    indexToRemove = rand() % vec.size();

    tree.remove(vec[indexToRemove]);
    tree_iterative.removeIterative(vec[indexToRemove]);
    vec.erase(vec.begin() + indexToRemove);

    ASSERT_EQ(tree.size(), i);
    ASSERT_EQ(tree_iterative.size(), i);
  }
}

TEST_F(BinarySearchTreeTest, RemoveAndEmpty) {
  tree.Insert(1);
  tree.Insert(2);

  ASSERT_TRUE(!tree.empty());
  tree.remove(1);
  ASSERT_TRUE(!tree.empty());
  tree.remove(2);
  ASSERT_TRUE(tree.empty());
  tree.remove(2);
  ASSERT_TRUE(tree.empty());
}

TEST_F(BinarySearchTreeTest, InOrder) {
  const int tree_size = 100;

  for (int i = 0; i < tree_size; ++i) {
    tree.Insert(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();
  ASSERT_EQ(tree.size(), tree_size);
  ASSERT_EQ(inorder.size(), tree_size);

  for (int i = 1; i < inorder.size(); ++i) {
    ASSERT_GE(inorder[i], inorder[i - 1]);
  }
}

TEST_F(BinarySearchTreeTest, InOrderExists) {
  const int tree_size = 100;

  for (int i = 0; i < tree_size; ++i) {
    tree.Insert(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();

  for (int i = 0; i < inorder.size(); ++i) {
    ASSERT_TRUE(tree.Exists(inorder[i]));
  }
}

TEST_F(BinarySearchTreeTest, MinAndMax) {
  const int tree_size = 100;

  for (int i = 0; i < tree_size; ++i) {
    tree.Insert(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();

  ASSERT_EQ(tree.min()->val, inorder[0]);
  ASSERT_EQ(tree.max()->val, inorder[inorder.size() - 1]);
}

TEST_F(BinarySearchTreeTest, BFS) {
  // TODO: This test could be stronger...
  std::vector<int> nodes_to_insert = {5, 3, 7, 2, 4, 6, 8};

  for (const int& node : nodes_to_insert) {
    tree.Insert(node);
  }

  ASSERT_EQ(tree.bfs(), nodes_to_insert);
}

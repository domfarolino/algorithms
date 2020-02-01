#include <algorithm> // std::swap, std::iter_swap.
#include <cstdlib> // rand().
#include <numeric> // std::accumulate.

#include "gtest/gtest.h"
#include "binary_search_tree.h"

class BinarySearchTreeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    srand(time(NULL));
  }

  binary_search_tree<int> tree;
};

TEST_F(BinarySearchTreeTest, InitiallyEmpty) {
  ASSERT_TRUE(tree.empty());
}

TEST_F(BinarySearchTreeTest, AddAndNotEmpty) {
  tree.insert(10);
  ASSERT_FALSE(tree.empty());
  tree.insert(20);
  ASSERT_FALSE(tree.empty());
}

TEST_F(BinarySearchTreeTest, AddAndSize) {
  for (int i = 0; i < 50; ++i) {
    ASSERT_EQ(tree.size(), i);
    tree.insert(rand());
  }
}

TEST_F(BinarySearchTreeTest, RemoveAndSize) {
  const int tree_size = 200;

  // |tree| will be used to test BinarySearchTree::Remove and |tree_iterative|
  // will be used to test BinarySearchTree::RemoveIterative.
  binary_search_tree<int> tree_iterative;

  std::vector<int> vec;

  for (int i = 0; i < tree_size; ++i) {
    vec.push_back(rand() % 2000);
    tree.insert(vec[vec.size() - 1]);
    tree_iterative.insert(vec[vec.size() - 1]);
  }

  int index_to_remove;
  for (int i = tree_size - 1; i >= 0; --i) {
    index_to_remove = rand() % vec.size();

    tree.remove(vec[index_to_remove]);
    tree_iterative.remove_iterative(vec[index_to_remove]);
    vec.erase(vec.begin() + index_to_remove);

    ASSERT_EQ(tree.size(), i);
    ASSERT_EQ(tree_iterative.size(), i);
  }
}

TEST_F(BinarySearchTreeTest, RemoveAndEmpty) {
  tree.insert(1);
  tree.insert(2);

  ASSERT_TRUE(!tree.empty());
  tree.remove(1);
  ASSERT_TRUE(!tree.empty());
  tree.remove(2);
  ASSERT_TRUE(tree.empty());
  tree.remove(2);
  ASSERT_TRUE(tree.empty());
}

TEST_F(BinarySearchTreeTest, Inorder) {
  const int tree_size = 100;

  for (int i = 0; i < tree_size; ++i) {
    tree.insert(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();
  ASSERT_EQ(tree.size(), tree_size);
  ASSERT_EQ(inorder.size(), tree_size);

  for (int i = 1; i < inorder.size(); ++i) {
    ASSERT_GE(inorder[i], inorder[i - 1]);
  }
}

TEST_F(BinarySearchTreeTest, MinAndMax) {
  const int tree_size = 100;

  for (int i = 0; i < tree_size; ++i) {
    tree.insert(rand() % 2000);
  }

  std::vector<int> inorder = tree.inorder();

  ASSERT_EQ(*tree.min(), inorder[0]);
  ASSERT_EQ(*tree.max(), inorder[inorder.size() - 1]);
}

TEST_F(BinarySearchTreeTest, BreadthFirstSearch) {
  // TODO: This test could be stronger...
  std::vector<int> nodes_to_insert = {5, 3, 7, 2, 4, 6, 8};

  for (const int& node : nodes_to_insert) {
    tree.insert(node);
  }

  ASSERT_EQ(tree.bfs(), nodes_to_insert);
}

// Iterator tests.
TEST_F(BinarySearchTreeTest, IteratorIncrementDuplicates_01) {
  tree.insert(7);
  tree.insert(6);
  tree.insert(6);
  tree.insert(6);
  tree.insert(5);
  auto it = tree.min();
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 7);
  ASSERT_EQ(it, tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorIncrementDuplicates_02) {
  tree.insert(7);
  tree.insert(8);
  tree.insert(8);
  tree.insert(8);
  tree.insert(9);
  tree.insert(5);
  auto it = tree.min();
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it++, 7);
  ASSERT_EQ(*it++, 8);
  ASSERT_EQ(*it++, 8);
  ASSERT_EQ(*it++, 8);
  ASSERT_EQ(*it++, 9);
  ASSERT_EQ(it, tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorIncrementDuplicates_03) {
  tree.insert(1);
  tree.insert(1);
  tree.insert(1);
  tree.insert(1);
  tree.insert(1);
  auto it = tree.min();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(it, tree.max());
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(it, tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorDecrementDuplicates_01) {
  tree.insert(7);
  tree.insert(6);
  tree.insert(6);
  tree.insert(6);
  tree.insert(5);
  auto it = tree.max();
  ASSERT_EQ(*it--, 7);
  ASSERT_EQ(*it--, 6);
  ASSERT_EQ(*it--, 6);
  ASSERT_EQ(*it--, 6);
  ASSERT_EQ(it, tree.begin());
  ASSERT_EQ(*it, 5);
}

TEST_F(BinarySearchTreeTest, IteratorDecrementDuplicates_02) {
  tree.insert(7);
  tree.insert(8);
  tree.insert(8);
  tree.insert(8);
  tree.insert(9);
  tree.insert(5);
  auto it = tree.max();
  ASSERT_EQ(*it--, 9);
  ASSERT_EQ(*it--, 8);
  ASSERT_EQ(*it--, 8);
  ASSERT_EQ(*it--, 8);
  ASSERT_EQ(*it--, 7);
  ASSERT_EQ(it, tree.begin());
  ASSERT_EQ(*it, 5);
}

TEST_F(BinarySearchTreeTest, IteratorDecrementDuplicates_03) {
  tree.insert(0);
  tree.insert(3);
  tree.insert(6);
  tree.insert(4);
  tree.insert(6);
  auto it = tree.max();
  ASSERT_EQ(*it--, 6);
  ASSERT_EQ(*it--, 6);
  ASSERT_EQ(*it--, 4);
  ASSERT_EQ(*it--, 3);
  ASSERT_EQ(it, tree.begin());
  ASSERT_EQ(*it, 0);
}

TEST_F(BinarySearchTreeTest, IteratorDecrementDuplicates_04) {
  tree.insert(1);
  tree.insert(1);
  tree.insert(1);
  tree.insert(1);
  tree.insert(1);
  auto it = tree.max();
  ASSERT_EQ(*it--, 1);
  ASSERT_EQ(*it--, 1);
  ASSERT_EQ(*it--, 1);
  ASSERT_EQ(*it--, 1);
  ASSERT_EQ(it, tree.begin());
  ASSERT_EQ(*it, 1);
}

TEST_F(BinarySearchTreeTest, IteratorIncrement_01) {
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  auto it = tree.min();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 3);
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(it, tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorIncrement_02) {
  tree.insert(7);
  tree.insert(4);
  tree.insert(6);
  auto it = tree.min();
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 7);
  ASSERT_EQ(it, tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorIncrement_03) {
  tree.insert(1000);
  tree.insert(4);
  tree.insert(999);
  tree.insert(5);
  tree.insert(998);
  tree.insert(6);
  auto it = tree.min();
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 998);
  ASSERT_EQ(*it++, 999);
  ASSERT_EQ(*it++, 1000);
  ASSERT_EQ(it, tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorDecrement_01) {
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  auto it = tree.max();
  ASSERT_EQ(*it--, 4);
  ASSERT_EQ(*it--, 3);
  ASSERT_EQ(*it--, 2);
  ASSERT_EQ(it, tree.begin());
  ASSERT_EQ(*it--, 1);
}

TEST_F(BinarySearchTreeTest, IteratorDecrement_02) {
  tree.insert(7);
  tree.insert(4);
  tree.insert(6);
  auto it = tree.max();
  ASSERT_EQ(*it--, 7);
  ASSERT_EQ(*it--, 6);
  ASSERT_EQ(it, tree.begin());
  ASSERT_EQ(*it--, 4);
}

TEST_F(BinarySearchTreeTest, IteratorDecrement_03) {
  tree.insert(1000);
  tree.insert(4);
  tree.insert(999);
  tree.insert(5);
  tree.insert(998);
  tree.insert(6);
  auto it = tree.max();
  ASSERT_EQ(*it--, 1000);
  ASSERT_EQ(*it--, 999);
  ASSERT_EQ(*it--, 998);
  ASSERT_EQ(*it--, 6);
  ASSERT_EQ(*it--, 5);
  ASSERT_EQ(it, tree.begin());
  ASSERT_EQ(*it--, 4);
}

TEST_F(BinarySearchTreeTest, IteratorBeginEnd) {
  ASSERT_EQ(tree.begin(), tree.end());
  tree.insert(10);
  tree.insert(11);
  ASSERT_NE(tree.begin(), tree.end());

  ASSERT_EQ(*tree.begin(), 10);
  ASSERT_EQ(tree.begin(), tree.min());

  ASSERT_EQ(tree.end(), ++tree.max());
  binary_search_tree<int>::iterator end_it = tree.max();
  end_it++;
  ASSERT_EQ(end_it, tree.end());

  binary_search_tree<int>::iterator it = tree.begin();
  ASSERT_NE(it, tree.end());
  it++;
  ASSERT_NE(it, tree.end());
  it++;
  ASSERT_EQ(it, tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorValueEquality) {
  const int tree_size = 500;

  for (int i = 0; i < tree_size; ++i) {
    tree.insert(rand() % 600);
  }

  std::vector<int> inorder = tree.inorder();
  std::vector<int>::iterator inorder_it = inorder.begin();
  binary_search_tree<int>::iterator it = tree.begin();
  while (inorder_it != inorder.end()) {
    ASSERT_EQ(*it, *inorder_it);
    ++it;
    ++inorder_it;
  }

  std::vector<int>::reverse_iterator inorder_rev = inorder.rbegin();
  it = tree.max();
  while (inorder_rev != inorder.rend()) {
    ASSERT_EQ(*it, *inorder_rev);
    --it;
    ++inorder_rev;
  }
}

TEST_F(BinarySearchTreeTest, IteratorFindEquality) {
  const int tree_size = 500;

  for (int i = 0; i < tree_size; ++i) {
    tree.insert(rand() % 600);
  }

  std::vector<int> inorder = tree.inorder();
  for (int val: inorder) {
    ASSERT_NE(tree.find(val), tree.end());
    ASSERT_EQ(*tree.find(val), val);
  }

  // 600 is guaranteed to not be in the tree.
  ASSERT_EQ(tree.find(600), tree.end());
}

TEST_F(BinarySearchTreeTest, IteratorPopulateVector) {
  const int tree_size = 500;

  for (int i = 0; i < tree_size; ++i) {
    tree.insert(rand() % 600);
  }

  std::vector<int> inorder = tree.inorder(),
                   populated(tree.begin(), tree.end());
  ASSERT_EQ(inorder.size(), tree.size());
  ASSERT_EQ(inorder, populated);
}

TEST_F(BinarySearchTreeTest, IteratorSTDAccumulate) {
  const int tree_size = 500;

  for (int i = 0; i < tree_size; ++i) {
    tree.insert(rand() % 600);
  }

  std::vector<int> inorder = tree.inorder();
  ASSERT_EQ(inorder.size(), tree.size());

  int actual_sum = std::accumulate(tree.begin(), tree.end(), 0),
      expected_sum = std::accumulate(inorder.begin(), inorder.end(), 0);
  ASSERT_EQ(actual_sum, expected_sum);
}

TEST_F(BinarySearchTreeTest, SwapBreakTreeVariant) {
  tree.insert(10);
  tree.insert(12);

  std::swap(*tree.min(), *tree.max());
  // Swapping the min and the max should work with the iterators, though it
  // breaks the invariant of the tree.
  ASSERT_GE(*tree.min(), *tree.max());
}

TEST_F(BinarySearchTreeTest, IterSwapBreakTreeVariant) {
  tree.insert(10);
  tree.insert(12);

  std::iter_swap(tree.min(), tree.max());
  // Swapping the min and the max should work with the iterators, though it
  // breaks the invariant of the tree.
  ASSERT_GE(*tree.min(), *tree.max());
}
// TODO: Add more tests (BinarySearchTree::Clear, etc).

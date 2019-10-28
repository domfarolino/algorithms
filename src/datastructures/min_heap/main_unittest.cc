#include <cstdlib> // rand().

#include "min_heap.h"
#include "gtest/gtest.h"

class MinHeapTest : public ::testing::Test {
 protected:
  void SetUp() override {
    srand(time(NULL));
  }

  min_heap<int> heap;
};

TEST_F(MinHeapTest, InsertAndSize) {
  ASSERT_EQ(heap.size(), 0);
  heap.insert(0);
  ASSERT_EQ(heap.size(), 1);
  heap.insert(0);
  ASSERT_EQ(heap.size(), 2);
}

TEST_F(MinHeapTest, InsertAndEmpty) {
  ASSERT_TRUE(heap.empty());
  heap.insert(0);
  ASSERT_TRUE(!heap.empty());
  heap.insert(0);
  ASSERT_TRUE(!heap.empty());
}

TEST_F(MinHeapTest, RemoveAndSize) {
  heap.insert(0);
  heap.insert(1);
  heap.insert(2);
  ASSERT_EQ(heap.size(), 3);

  heap.remove();
  ASSERT_EQ(heap.size(), 2);

  heap.remove();
  ASSERT_EQ(heap.size(), 1);

  heap.remove();
  ASSERT_EQ(heap.size(), 0);

  heap.remove();
  ASSERT_EQ(heap.size(), 0);
}

TEST_F(MinHeapTest, RemoveAndEmpty) {
  heap.insert(0);
  heap.insert(1);
  heap.insert(2);
  ASSERT_TRUE(!heap.empty());

  heap.remove();
  ASSERT_TRUE(!heap.empty());

  heap.remove();
  ASSERT_TRUE(!heap.empty());

  heap.remove();
  ASSERT_TRUE(heap.empty());

  heap.remove();
  ASSERT_TRUE(heap.empty());
}

TEST_F(MinHeapTest, Peek) {
  for (int i = 0; i < 20; ++i) {
    heap.insert(rand() % 31);
  }

  int min_thus_far = -1;

  while (!heap.empty()) {
    ASSERT_GE(heap.peek(), min_thus_far);
    min_thus_far = heap.peek();
    heap.remove();
  }
}

TEST(MinHeapSingleTest, CopyConstructor) {
  min_heap<int> right;
  right.insert(1);
  right.insert(2);
  right.insert(3);

  min_heap<int> left = right;
  right.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(left.peek(), 1);
}

TEST(MinHeapSingleTest, CopyAssignment) {
  min_heap<int> left, center, right;
  right.insert(1);
  right.insert(2);
  right.insert(3);

  left = center = right;
  right.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(center.size(), 3);
  ASSERT_EQ(left.peek(), 1);
  ASSERT_EQ(center.peek(), 1);

  center.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(center.size(), 0);
  ASSERT_TRUE(center.empty());
}

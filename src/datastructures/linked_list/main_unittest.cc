#include "gtest/gtest.h"
#include "linked_list.h"

class LinkedListTest : public ::testing::Test {
 protected:
  linked_list<int> list;
};

TEST_F(LinkedListTest, SizeAndEmpty) {
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());

  list.add_to_tail(1);
  ASSERT_EQ(list.size(), 1);
  ASSERT_TRUE(!list.empty());

  list.add_to_head(2);
  ASSERT_EQ(list.size(), 2);
  ASSERT_TRUE(!list.empty());

  list.clear();
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());
}

TEST_F(LinkedListTest, AddToHead) {
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);

  list.add_to_head(1);
  ASSERT_EQ(list.to_string(), "1,");
  ASSERT_EQ(list.size(), 1);

  list.add_to_head(2);
  ASSERT_EQ(list.to_string(), "2,1,");
  ASSERT_EQ(list.size(), 2);

  list.add_to_head(-1);
  ASSERT_EQ(list.to_string(), "-1,2,1,");
  ASSERT_EQ(list.size(), 3);
}

TEST_F(LinkedListTest, AddToTail) {
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);

  list.add_to_tail(1);
  ASSERT_EQ(list.to_string(), "1,");
  ASSERT_EQ(list.size(), 1);

  list.add_to_tail(2);
  ASSERT_EQ(list.to_string(), "1,2,");
  ASSERT_EQ(list.size(), 2);

  list.add_to_tail(-1);
  ASSERT_EQ(list.to_string(), "1,2,-1,");
  ASSERT_EQ(list.size(), 3);
}

TEST_F(LinkedListTest, AddToMix) {
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);

  list.add_to_tail(1);
  ASSERT_EQ(list.to_string(), "1,");
  ASSERT_EQ(list.size(), 1);

  list.add_to_head(2);
  ASSERT_EQ(list.to_string(), "2,1,");
  ASSERT_EQ(list.size(), 2);

  list.add_to_head(3);
  ASSERT_EQ(list.to_string(), "3,2,1,");
  ASSERT_EQ(list.size(), 3);

  list.add_to_tail(4);
  ASSERT_EQ(list.to_string(), "3,2,1,4,");
  ASSERT_EQ(list.size(), 4);

  list.add_to_head(5);
  ASSERT_EQ(list.to_string(), "5,3,2,1,4,");
  ASSERT_EQ(list.size(), 5);
}

TEST_F(LinkedListTest, RemoveFromHead) {
  list.add_to_head(1);
  list.add_to_head(2);
  list.add_to_head(3);
  list.add_to_head(4);
  ASSERT_EQ(list.to_string(), "4,3,2,1,");
  ASSERT_EQ(list.size(), 4);

  list.remove_from_head();
  ASSERT_EQ(list.to_string(), "3,2,1,");
  ASSERT_EQ(list.size(), 3);

  list.remove_from_head();
  ASSERT_EQ(list.to_string(), "2,1,");
  ASSERT_EQ(list.size(), 2);

  list.remove_from_head();
  ASSERT_EQ(list.to_string(), "1,");
  ASSERT_EQ(list.size(), 1);

  list.remove_from_head();
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);

  list.remove_from_head();
  list.remove_from_head();
  list.remove_from_head();
  list.remove_from_head();
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);
}

TEST_F(LinkedListTest, RemoveFromTail) {
  list.add_to_head(1);
  list.add_to_head(2);
  list.add_to_head(3);
  list.add_to_head(4);
  ASSERT_EQ(list.to_string(), "4,3,2,1,");
  ASSERT_EQ(list.size(), 4);

  list.remove_from_tail();
  ASSERT_EQ(list.to_string(), "4,3,2,");
  ASSERT_EQ(list.size(), 3);

  list.remove_from_tail();
  ASSERT_EQ(list.to_string(), "4,3,");
  ASSERT_EQ(list.size(), 2);

  list.remove_from_tail();
  ASSERT_EQ(list.to_string(), "4,");
  ASSERT_EQ(list.size(), 1);

  list.remove_from_tail();
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);

  list.remove_from_tail();
  list.remove_from_tail();
  list.remove_from_tail();
  list.remove_from_tail();
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);
}

TEST_F(LinkedListTest, Remove) {
  list.add_to_head(3);
  list.add_to_head(2);
  list.add_to_head(1);
  list.remove(4);
  ASSERT_EQ(list.to_string(), "1,2,3,");
  ASSERT_EQ(list.size(), 3);

  list.remove(2);
  ASSERT_EQ(list.to_string(), "1,3,");
  ASSERT_EQ(list.size(), 2);

  list.remove(1);
  ASSERT_EQ(list.to_string(), "3,");
  ASSERT_EQ(list.size(), 1);

  list.remove(3);
  list.remove(2);
  list.remove(2);
  list.remove(2);
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());
}

TEST_F(LinkedListTest, Clear) {
  list.add_to_head(1);
  list.add_to_head(2);
  list.add_to_head(3);

  list.clear();
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());

  list.clear();
  ASSERT_EQ(list.to_string(), "");
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());

  list.add_to_head(1);
  ASSERT_EQ(list.size(), 1);
  ASSERT_TRUE(!list.empty());
}

TEST(LinkedListSingleTest, CopyConstructor) {
  linked_list<int> right;
  right.add_to_tail(1);
  right.add_to_tail(2);

  linked_list<int> left = right;

  right.clear();
  right.add_to_head(3);
  ASSERT_EQ(left.to_string(), "1,2,");
  ASSERT_EQ(left.size(), 2);

  ASSERT_EQ(right.to_string(), "3,");
  ASSERT_EQ(right.size(), 1);
}

TEST(LinkedListSingleTest, CopyAssignment) {
  linked_list<int> left, center, right;

  for (int i = 0; i < 5; ++i) right.add_to_tail(i);

  left = center = right;

  ASSERT_EQ(left.to_string(), center.to_string());
  ASSERT_EQ(left.size(), center.size());

  ASSERT_EQ(center.to_string(), right.to_string());
  ASSERT_EQ(center.size(), right.size());

  right.clear();
  center.add_to_head(49);

  ASSERT_EQ(left.to_string(), "0,1,2,3,4,");
  ASSERT_EQ(center.to_string(), "49,0,1,2,3,4,");
  ASSERT_EQ(right.to_string(), "");
}

TEST_F(LinkedListTest, IteratorIncrement) {
  for (int i = 0; i < 20; ++i) {
    list.add_to_head(20 - i - 1);
  }

  linked_list<int>::iterator a = list.begin();
  linked_list<int>::iterator b = list.begin();

  for (int i = 0; i < 19; ++i) {
    ASSERT_EQ(*a++, *++b - 1);
  }
}

TEST_F(LinkedListTest, IteratorTraversal) {
  for (int i = 0; i < 20; ++i) {
    list.add_to_head(20 - i - 1);
  }

  linked_list<int>::iterator it = list.begin();
  int i = 0;

  while (it != list.end()) {
    ASSERT_EQ(*it++, i++);
  }

  ASSERT_EQ(i, 20);
}

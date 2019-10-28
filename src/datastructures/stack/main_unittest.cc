#include "stack.h"
#include "gtest/gtest.h"

class StackTest : public ::testing::Test {
protected:
  stack<int> stck;
};

TEST_F(StackTest, PushAndSize) {
  ASSERT_EQ(stck.size(), 0);
  stck.push(1);
  ASSERT_EQ(stck.size(), 1);
  stck.push(1);
  ASSERT_EQ(stck.size(), 2);
}

TEST_F(StackTest, PushAndEmpty) {
  ASSERT_TRUE(stck.empty());
  stck.push(1);
  ASSERT_TRUE(!stck.empty());
  stck.push(1);
  ASSERT_TRUE(!stck.empty());
}

TEST_F(StackTest, PopAndSize) {
  stck.push(1);
  stck.push(2);
  stck.push(3);
  ASSERT_EQ(stck.size(), 3);

  stck.pop();
  ASSERT_EQ(stck.size(), 2);

  stck.pop();
  ASSERT_EQ(stck.size(), 1);

  stck.pop();
  ASSERT_EQ(stck.size(), 0);

  stck.pop();
  ASSERT_EQ(stck.size(), 0);
}

TEST_F(StackTest, PopAndEmpty) {
  stck.push(1);
  stck.push(2);
  stck.push(3);
  ASSERT_TRUE(!stck.empty());

  stck.pop();
  ASSERT_TRUE(!stck.empty());

  stck.pop();
  ASSERT_TRUE(!stck.empty());

  stck.pop();
  ASSERT_TRUE(stck.empty());

  stck.pop();
  ASSERT_TRUE(stck.empty());
}

TEST_F(StackTest, Top) {
  stck.push(1);
  stck.push(2);
  stck.push(3);
  ASSERT_EQ(stck.top(), 3);
  ASSERT_EQ(stck.top(), 3); // make sure stack::top() doesn't pop.

  stck.pop();
  ASSERT_EQ(stck.top(), 2);

  stck.pop();
  ASSERT_EQ(stck.top(), 1);
  stck.pop();

  bool threw_error = false;

  try {
    stck.top();
  } catch (std::exception &e) {
    threw_error = true;
  }

  ASSERT_TRUE(threw_error);
}

TEST_F(StackTest, Clear) {
  stck.push(1);
  stck.push(2);
  stck.push(3);

  stck.clear();
  stck.clear(); // Calling clear() again shouldn't break anything.

  ASSERT_EQ(stck.size(), 0);
  ASSERT_TRUE(stck.empty());

  bool threw_error = false;

  try {
    stck.top();
  } catch (std::logic_error e) {
    threw_error = true;
  }

  ASSERT_TRUE(threw_error);
}

TEST(StackSingleTest, CopyConstructor) {
  stack<int> right;
  right.push(1);
  right.push(2);
  right.push(3);

  stack<int> left = right;
  right.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(left.top(), 3);
}

TEST(StackSingleTest, CopyAssignment) {
  stack<int> left, center, right;
  right.push(1);
  right.push(2);
  right.push(3);

  left = center = right;
  right.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(center.size(), 3);
  ASSERT_EQ(left.top(), 3);
  ASSERT_EQ(center.top(), 3);

  center.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(center.size(), 0);
  ASSERT_TRUE(center.empty());
}

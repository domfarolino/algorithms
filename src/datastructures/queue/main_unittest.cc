#include "queue.h" // To test this implementation.
// #include "queue_from_stacks/queue.h" // to test the queue from stacks implementation.
#include "gtest/gtest.h"

class QueueTest : public ::testing::Test {
 protected:
  queue<int> q;
};

TEST_F(QueueTest, EnqueueAndSize) {
  ASSERT_EQ(q.size(), 0);
  q.enqueue(1);
  ASSERT_EQ(q.size(), 1);
  q.enqueue(2);
  ASSERT_EQ(q.size(), 2);
  q.enqueue(3);
}

TEST_F(QueueTest, EnqueueAndEmpty) {
  ASSERT_TRUE(q.empty());
  q.enqueue(1);
  ASSERT_TRUE(!q.empty());
  q.enqueue(2);
  ASSERT_TRUE(!q.empty());
}

TEST_F(QueueTest, DequeueAndSize) {
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  ASSERT_EQ(q.size(), 3);

  q.dequeue();
  ASSERT_EQ(q.size(), 2);

  q.dequeue();
  ASSERT_EQ(q.size(), 1);

  q.dequeue();
  ASSERT_EQ(q.size(), 0);

  q.dequeue();
  ASSERT_EQ(q.size(), 0);
}

TEST_F(QueueTest, DequeueAndEmpty) {
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  ASSERT_TRUE(!q.empty());

  q.dequeue();
  ASSERT_TRUE(!q.empty());

  q.dequeue();
  ASSERT_TRUE(!q.empty());

  q.dequeue();
  ASSERT_TRUE(q.empty());

  q.dequeue();
  ASSERT_TRUE(q.empty());
}

TEST_F(QueueTest, Front) {
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  ASSERT_EQ(q.front(), 1);
  ASSERT_EQ(q.front(), 1); // Make sure queue.front() doesn't dequeue.

  q.dequeue();
  ASSERT_EQ(q.front(), 2);

  q.dequeue();
  ASSERT_EQ(q.front(), 3);
  q.dequeue();

  bool threw_error = false;

  try {
    q.front();
  } catch (std::exception &e) {
    threw_error = true;
  }

  ASSERT_TRUE(threw_error);
}

TEST_F(QueueTest, Clear) {
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  q.clear();
  q.clear(); // Calling clear() again shouldn't break anything.

  ASSERT_EQ(q.size(), 0);
  ASSERT_TRUE(q.empty());

  bool threw_error = false;

  try {
    q.front();
  } catch (std::logic_error e) {
    threw_error = true;
  }

  ASSERT_TRUE(threw_error);
}

TEST(QueueSingleTest, CopyConstructor) {
  queue<int> right;
  right.enqueue(1);
  right.enqueue(2);
  right.enqueue(3);

  queue<int> left = right;
  right.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(left.front(), 1);
}

TEST(QueueSingleTest, CopyAssignment) {
  queue<int> left, center, right;
  right.enqueue(1);
  right.enqueue(2);
  right.enqueue(3);

  left = center = right;
  right.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(center.size(), 3);
  ASSERT_EQ(left.front(), 1);
  ASSERT_EQ(center.front(), 1);

  center.clear();

  ASSERT_EQ(left.size(), 3);
  ASSERT_EQ(center.size(), 0);
  ASSERT_TRUE(center.empty());
}

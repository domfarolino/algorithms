#include <math.h> // pow(), ceil(), log2().

#include "gtest/gtest.h"
#include "vector.h"

class VectorTest : public ::testing::Test {
 protected:
  vector<int> vec;
};

TEST_F(VectorTest, PushBackSize) {
  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
    ASSERT_EQ(vec.size(), i + 1);
  }
}

TEST_F(VectorTest, PopBackSize) {
  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  for (int i = 99; i >= 0; --i) {
    ASSERT_EQ(vec.size(), i + 1);
    vec.pop_back();
    ASSERT_EQ(vec.size(), i);
  }
}

TEST_F(VectorTest, PushBackIndex) {
  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(vec[i], i);
  }
}

TEST_F(VectorTest, PopBackIndex) {
  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  for (int i = 99; i >= 0; --i) {
    ASSERT_EQ(vec[i], i);
    ASSERT_EQ(vec[vec.size() - 1], i);
    vec.pop_back();
  }
}

TEST_F(VectorTest, PushFrontSize) {
  for (int i = 0; i < 100; ++i) {
    vec.push_front(i);
    ASSERT_EQ(vec.size(), i + 1);
  }
}

TEST_F(VectorTest, PopFrontSize) {
  for (int i = 0; i < 100; ++i) {
    vec.push_front(i);
  }

  for (int i = 99; i >= 0; --i) {
    ASSERT_EQ(vec.size(), i + 1);
    vec.pop_front();
    ASSERT_EQ(vec.size(), i);
  }
}

TEST_F(VectorTest, PushFrontIndex) {
  for (int i = 0; i < 100; ++i) {
    vec.push_front(i);
  }

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(vec[i], 99 - i);
  }
}

TEST_F(VectorTest, Size) {
  for (int i = 0; i < 100; ++i) {
    vec.push_back(10);
    vec.push_front(11);
  }

  for (int i = 0; i < 100; ++i) {
    vec.pop_back();
    vec.pop_front();
    vec.pop_back();
    vec.pop_front();
  }

  ASSERT_EQ(vec.size(), 0);
}

TEST_F(VectorTest, CapacityDoubling) {
  int exponent;
  for (int i = 0; i < 256; ++i) {
    vec.push_back(0);
    exponent = ceil(log2(vec.size()));

    // Capacity should be equal to the next power of two >= log2 of the current
    // size. This is because the vector implementation only doubles in size when
    // our size is about to exceed the capacity.
    ASSERT_EQ(vec.capacity(), pow(2, exponent));
  }
}

TEST_F(VectorTest, Reverse) {
  const int size = 100;

  for (int i = 0; i < size; ++i) {
    vec.push_back(i);
  }

  vec.reverse();

  for (int i = 0; i < size; ++i) {
    ASSERT_EQ(vec[i], size - 1 - i);
  }
}

TEST_F(VectorTest, Clear) {
  for (int i = 0; i < 20; ++i) {
    vec.push_back(i);
  }

  vec.clear();

  ASSERT_EQ(vec.size(), 0);
  ASSERT_TRUE(vec.empty());

  // Should reset vec to a fresh, usable form
  ASSERT_EQ(vec.capacity(), 1);

  // Clearing again shouldn't do anything.
  vec.clear();

  ASSERT_EQ(vec.size(), 0);
  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.capacity(), 1);
}

TEST(VectorSingleTest, OverloadedConstructorSizeAndCapacity) {
  vector<int> vec(100);
  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 100);
}

TEST(VectorSingleTest, OverloadedConstructor) {
  vector<int> vec(-100);

  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 1);

  vec.push_back(1);

  ASSERT_TRUE(!vec.empty());
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 1);

  vec.push_back(1);

  ASSERT_TRUE(!vec.empty());
  ASSERT_TRUE(vec.size() == 2);
  ASSERT_TRUE(vec.capacity() == 2);

  vector<int> vec2(10);
  ASSERT_TRUE(vec2.empty());
  ASSERT_EQ(vec2.size(), 0);
  ASSERT_EQ(vec2.capacity(), 10);

  for (int i = 0; i < 15; ++i) {
    vec2.push_back(i);
  }

  ASSERT_EQ(vec2.size(), 15);
  // Once capacity is met, it doubles
  ASSERT_EQ(vec2.capacity(), 20);
}

TEST(VectorSingleTest, CopyConstructor) {
  vector<int> right;

  for (int i = 0; i < 1000; ++i) {
    right.push_back(i);
  }

  vector<int> left = right;

  ASSERT_EQ(left.size(), right.size());
  ASSERT_EQ(left.capacity(), right.capacity());

  for (int i = 0; i < left.size(); ++i) {
    ASSERT_EQ(left[i], i);
  }

  right[1] = 100;
  right.pop_front();

  ASSERT_NE(left.size(), right.size());
  ASSERT_NE(left[0], right[0]);
}

TEST(VectorSingleTest, CopyAssignment) {
  vector<int> left, center, right(100);

  for (int i = 0; i < 1000; ++i) {
    right.push_back(i);
  }

  left = center = right;

  ASSERT_EQ(left.size(), center.size());
  ASSERT_EQ(center.size(), right.size());
  ASSERT_EQ(left.capacity(), center.capacity());
  ASSERT_EQ(center.capacity(), right.capacity());

  for (int i = 0; i < left.size(); ++i) {
    ASSERT_EQ(left[i], center[i]);
    ASSERT_EQ(center[i], right[i]);
  }

  right.pop_front();
  center[0] = 666;

  ASSERT_NE(left.size(), right.size());
  ASSERT_NE(center.size(), right.size());

  ASSERT_NE(left[0], center[0]);
  ASSERT_NE(left[0], right[0]);
}

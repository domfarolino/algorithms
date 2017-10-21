#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "Queue.h"

TEST_CASE("Enqueue + Size", "[Queue]") {
  Queue<int> q;
  REQUIRE(q.size() == 0);
  q.enqueue(1);
  REQUIRE(q.size() == 1);
  q.enqueue(2);
  REQUIRE(q.size() == 2);
  q.enqueue(3);
}

TEST_CASE("Enqueue + Empty", "[Queue]") {
  Queue<int> q;
  REQUIRE(q.empty());
  q.enqueue(1);
  REQUIRE(!q.empty());
  q.enqueue(2);
  REQUIRE(!q.empty());
}

TEST_CASE("Dequeue + Size", "[Queue]") {
  Queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  REQUIRE(q.size() == 3);
  q.dequeue();
  REQUIRE(q.size() == 2);
  q.dequeue();
  REQUIRE(q.size() == 1);
  q.dequeue();
  REQUIRE(q.size() == 0);
  q.dequeue();
  REQUIRE(q.size() == 0);
}

TEST_CASE ("Dequeue + Empty", "[Queue]") {
  Queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  REQUIRE(!q.empty());
  q.dequeue();
  REQUIRE(!q.empty());
  q.dequeue();
  REQUIRE(!q.empty());
  q.dequeue();
  REQUIRE(q.empty());
  q.dequeue();
  REQUIRE(q.empty());
}

TEST_CASE ("Front", "[Queue]") {
  Queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  REQUIRE(q.front() == 1);
  REQUIRE(q.front() == 1); // make sure queue.front() doesn't dequeue
  q.dequeue();
  REQUIRE(q.front() == 2);
  q.dequeue();
  REQUIRE(q.front() == 3);
  q.dequeue();

  bool threwError = false;

  try {
    q.front();
  } catch (std::exception &e) {
    threwError = true;
  }

  REQUIRE(threwError);
}

TEST_CASE("Clear", "[Queue]") {
  Queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  q.clear();
  q.clear();

  REQUIRE(q.size() == 0);
  REQUIRE(q.empty());

  bool threwError = false;

  try {
    q.front();
  } catch (std::logic_error e) {
    threwError = true;
  }

  REQUIRE(threwError);
}

TEST_CASE("Copy Constructor", "[Queue]") {
  Queue<int> right;
  right.enqueue(1);
  right.enqueue(2);
  right.enqueue(3);

  Queue<int> left = right;
  right.clear();

  REQUIRE(left.size() == 3);
  REQUIRE(left.front() == 1);
}

void copyAssignment() {
  Queue<int> left, center, right;
  right.enqueue(1);
  right.enqueue(2);
  right.enqueue(3);

  left = center = right;
  right.clear();

  REQUIRE(left.size() == 3);
  REQUIRE(center.size() == 3);
  REQUIRE(left.front() == 1);
  REQUIRE(center.front() == 1);

  center.clear();

  REQUIRE(left.size() == 3);
  REQUIRE(center.size() == 0);
  REQUIRE(center.empty());
}

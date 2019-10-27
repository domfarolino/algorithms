#include <iostream>
#include <assert.h>

#include "linked_list.h"

void sizeAndEmpty() {
  linked_list<int> list;

  assert(list.size() == 0);
  assert(list.empty());

  list.add_to_tail(1);
  assert(list.size() == 1);
  assert(!list.empty());

  list.add_to_head(2);
  assert(list.size() == 2);
  assert(!list.empty());

  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
}

void add_to_head() {
  linked_list<int> list;
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.add_to_head(1);
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.add_to_head(2);
  assert(list.to_string() == "2,1,");
  assert(list.size() == 2);
  list.add_to_head(-1);
  assert(list.to_string() == "-1,2,1,");
  assert(list.size() == 3);
}

void add_to_tail() {
  linked_list<int> list;
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.add_to_tail(1);
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.add_to_tail(2);
  assert(list.to_string() == "1,2,");
  assert(list.size() == 2);
  list.add_to_tail(-1);
  assert(list.to_string() == "1,2,-1,");
  assert(list.size() == 3);
}

void addToMix() {
  linked_list<int> list;
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.add_to_tail(1);
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.add_to_head(2);
  assert(list.to_string() == "2,1,");
  assert(list.size() == 2);
  list.add_to_head(3);
  assert(list.to_string() == "3,2,1,");
  assert(list.size() == 3);
  list.add_to_tail(4);
  assert(list.to_string() == "3,2,1,4,");
  assert(list.size() == 4);
  list.add_to_head(5);
  assert(list.to_string() == "5,3,2,1,4,");
  assert(list.size() == 5);
}

void remove_from_head() {
  linked_list<int> list;
  list.add_to_head(1);
  list.add_to_head(2);
  list.add_to_head(3);
  list.add_to_head(4);
  assert(list.to_string() == "4,3,2,1,");
  assert(list.size() == 4);
  list.remove_from_head();
  assert(list.to_string() == "3,2,1,");
  assert(list.size() == 3);
  list.remove_from_head();
  assert(list.to_string() == "2,1,");
  assert(list.size() == 2);
  list.remove_from_head();
  assert(list.to_string() == "1,");
  assert(list.size() == 1);
  list.remove_from_head();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.remove_from_head();
  list.remove_from_head();
  list.remove_from_head();
  list.remove_from_head();
  assert(list.to_string() == "");
  assert(list.size() == 0);
}

void remove_from_tail() {
  linked_list<int> list;
  list.add_to_head(1);
  list.add_to_head(2);
  list.add_to_head(3);
  list.add_to_head(4);
  assert(list.to_string() == "4,3,2,1,");
  assert(list.size() == 4);
  list.remove_from_tail();
  assert(list.to_string() == "4,3,2,");
  assert(list.size() == 3);
  list.remove_from_tail();
  assert(list.to_string() == "4,3,");
  assert(list.size() == 2);
  list.remove_from_tail();
  assert(list.to_string() == "4,");
  assert(list.size() == 1);
  list.remove_from_tail();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  list.remove_from_tail();
  list.remove_from_tail();
  list.remove_from_tail();
  list.remove_from_tail();
  assert(list.to_string() == "");
  assert(list.size() == 0);
}

void remove() {
  linked_list<int> list;
  list.add_to_head(3);
  list.add_to_head(2);
  list.add_to_head(1);

  list.remove(4);
  assert(list.to_string() == "1,2,3,");
  assert(list.size() == 3);
  list.remove(2);
  assert(list.to_string() == "1,3,");
  assert(list.size() == 2);
  list.remove(1);
  assert(list.to_string() == "3,");
  assert(list.size() == 1);
  list.remove(3);
  list.remove(2);
  list.remove(2);
  list.remove(2);
  assert(list.to_string() == "");
  assert(list.size() == 0);
  assert(list.empty());
}

void clear() {
  linked_list<int> list;
  list.add_to_head(1);
  list.add_to_head(2);
  list.add_to_head(3);

  list.clear();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  assert(list.empty());
  list.clear();
  assert(list.to_string() == "");
  assert(list.size() == 0);
  assert(list.empty());

  list.add_to_head(1);
  assert(list.size() == 1);
  assert(!list.empty());
}

void copyConstructor() {
  linked_list<int> right;
  right.add_to_tail(1);
  right.add_to_tail(2);

  linked_list<int> left = right;

  right.clear();
  right.add_to_head(3);
  assert(left.to_string() == "1,2,");
  assert(left.size() == 2);

  assert(right.to_string() == "3,");
  assert(right.size() == 1);
}

void copyAssignment() {
  linked_list<int> left, center, right;

  for (int i = 0; i < 5; ++i) right.add_to_tail(i);

  left = center = right;

  assert(left.to_string() == center.to_string());
  assert(left.size() == center.size());

  assert(center.to_string() == right.to_string());
  assert(center.size() == right.size());

  right.clear();
  center.add_to_head(49);

  assert(left.to_string() == "0,1,2,3,4,");
  assert(center.to_string() == "49,0,1,2,3,4,");
  assert(right.to_string() == "");
}

int main() {
  sizeAndEmpty();
  add_to_head();
  add_to_tail();
  addToMix();
  remove_from_head();
  remove_from_tail();
  remove();
  clear();

  copyConstructor();
  copyAssignment();

  std::cout << "\x1B[32m✔ All tests pass\x1B[00m" << std::endl;
  return 0;
}

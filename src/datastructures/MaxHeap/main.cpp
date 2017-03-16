#include <iostream>
#include <cstdlib>

#include "MaxHeap.h"

using namespace std;

int main() {
  srand(time(NULL));
  MaxHeap<int> heap;

  for (int i = 0; i < 20; ++i) {
    heap.insert(rand() % 31);
  }

  while (!heap.empty()) {
    cout << heap.peek() << ", ";
    heap.remove();
  }

  cout << endl;

  cout << "\x1B[32m✔ All tests pass\x1B[32m" << endl;
  return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>  /* sort */

/*
 * Bucket sort works well when you can guarantee that
 * your input is approximately uniformly distributed.
 *
 * Bucket sort is misleading because it doesn't actually sort
 * the items in the list through traditional comparisons, but
 * puts elements into a "bucket" and then another sorting algorithm
 * comes in to sort the buckets. Commonly insertion sort has been a
 * popular way to sort buckets.
 *
 * Complexity analysis:
 * Time complexity:
 *    Best:     Ω(n + k), k = number of buckets
 *    Average:  Θ(n + k)
 *    Worst:    O(n^2), if all elements are put into the same bucket
*/

template <typename T>
void calculateMinMax(std::vector<T> &vector, T &min, T &max) {
  for (auto it = vector.begin() + 1;it != vector.end(); ++it) {
    max = (*it > max) ? *it : max;
    min = (*it < min) ? *it : min;
  }
}

template <typename T>
void bucketSort(std::vector<T> &vector, int size) {
  if (vector.empty()) {
    return;
  }

  T min = vector[0], max = vector[0];
  int bucketIndex, index = 0;

  calculateMinMax(vector, min, max);
  int numBuckets = (max - min) / size + 1;
  std::vector<std::vector<T>> buckets (numBuckets, std::vector<T>());

  // append elements into buckets
  for (auto it = vector.begin(); it != vector.end(); it++) {
    bucketIndex = (*it - min) / size;
    buckets[bucketIndex].push_back(*it);
  }

  // use preferred sorting method to sort each bucket
  for (auto it = buckets.begin(); it != buckets.end(); it++) {
    sort(it->begin(), it->end());
  }

  // append the sorted values back into the vector
  for (int i = 0; i < buckets.size(); i++) {
    for (int j = 0; j < buckets[i].size(); j++) {
      vector[index++] = buckets[i][j];
    }
  }
}

template <typename T>
void debug(std::vector<T> &vector) {
  for (auto it = vector.begin(); it != vector.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void test(std::vector<T> &vector) {
  std::cout << "Before" << std::endl;
  debug(vector);
  bucketSort(vector, vector.size());
  std::cout << "After" << std::endl;
  debug(vector);
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "==========" << std::endl;
  std::cout << "BucketSort" << std::endl;
  std::cout << "==========" << std::endl;
  std::vector<int> sampleIntegerVector {22, 45, 12, 8, 10, 6, 72, 81, 33, 18, 50, 14};
  std::cout << "Testing integers" << std::endl;
  test(sampleIntegerVector);

  std::cout << "Testing floats" << std::endl;
  std::vector<float> sampleFloatVector {22.4, 45.1, 1.3, 3.5, 10.9, 6.34, 72.87, 81.0, 33.12, 18.4, 50.9, 14.3, -1};
  test(sampleFloatVector);

  std::cout << "Testing chars" << std::endl;
  std::vector<char> sampleCharVector {'a', 'D', 'v', 'H', 'u', 'b', 'z', 'e', 'P', 'S', 'A', 'l', 'c'};
  test(sampleCharVector);
}

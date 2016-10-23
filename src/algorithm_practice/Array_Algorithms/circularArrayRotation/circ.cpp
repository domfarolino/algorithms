#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Source: https://www.hackerrank.com/challenges/circular-array-rotation

/**
 * Circular Array Rotation
 * The setup for this one is relatively
 * easy because you only have to program for
 * a single input (given its in the warmup problems).
 * We don't actually have to rotate the array, instead we
 * can just index using k as our offset. If we use k as our
 * offset, this means given some query we need to look at index
 * query - k to go backwards in our array.
 * For example:
 * arr = 1 2 3 4
 * Consider query = 2, k = 0. arr[2] = 3.
 * Consider query = 2, k = 1. arr[2 - 1] = 2.
 * Consider query = 2, k = 2. arr[2 - 2] = 0.
 * Consider query = 2, k = 3. arr[2 - 3] = 4. // need to wrap back around
 *
 * We need to realize our query - k can be negative. In this case we want
 * to be able to wrap around to the other end of the array. We can do so using
 * modulo. In this case we'll need to handle modulo for negative numbers properly.
 * In C++, % is not the modulo operator, it is the division remainder operator which
 * is almost the same thing. In mathematics, -7mod6 will give us 5, however C++ gives us
 * -1. -13%6 in C++ also gives us -1, so we can see a trend here. In this case we just need
 * to add 6 after our % operation in C++ to get the right answer. -7%6 + 6 = 5 which is the right
 * answer. We need to observe one special case however, where we take -6%6. This returns 0 in C++
 * however if we add 6 to this, we'll be prompted to look at the 6th index which will not exist in
 * an array of length 6. In this case, to calculate the real index given a negative index we need to
 * do (negIndex % arrSize + arrSize) % arrSize. Note that this of course works for positive numbers too.
 */

long realIndex(long negIndex, long arrSize) {
  return (negIndex % arrSize + arrSize) % arrSize;
}

int main() {
  long n, k;
  int queries, singleQuery; // ints to hold total # of queries, and each individual query
  vector<long> arr;
  cin >> n >> k >> queries;
  arr.resize(n);

  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  for (int i = 0; i < queries; ++i) {
    cin >> singleQuery;
    cout << arr[realIndex(singleQuery - k, arr.size())] << endl;
  }

  return 0;
}

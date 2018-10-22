#include <iostream>
#include <vector>

// Source: https://math.stackexchange.com/questions/2965187/how-many-different-tournament-orderings-are-there
// Source: https://math.stackexchange.com/questions/382174/ways-of-merging-two-incomparable-sorted-lists-of-elements-keeping-their-relative

/**
 * Complete documentation for this file and algorithm
 * is in the README file in this directory.
 */

// Helper function to print each valid index mapping.
void printIndices(const std::vector<int>& indices) {
  for (int index: indices) {
    std::cout << index;
  }

  std::cout << std::endl;
}

/**
 * This function is responsible for taking in a list of indices, and two lists
 * a and b. It returns a combined list of size |a| + |b|, where the elements at
 * `indices` are occupied by the elements of list a.
 */
std::vector<int> combineLists(const std::vector<int>& indices, const std::vector<int>& a, const std::vector<int>& b) {
  // Assert: indices is a valid index mapping of size |a.size()|
  std::vector<int> returnVec(a.size() + b.size());

  int indexPtr = 0, aPtr = 0, bPtr = 0;
  for (int i = 0; i < returnVec.size(); ++i) {
    if (aPtr < a.size() && indices[indexPtr] == i) {
      returnVec[i] = a[aPtr++];
      indexPtr++;
    } else {
      returnVec[i] = b[bPtr++];
    }
  }

  return returnVec;
}

/**
 * Recursive helper function where all of the work is done. This function
 * generates all of the valid index mappings for elements in list a, and calls
 * combineLists, for all index mappings.
 */
void incrementIndices(std::vector<int>& indices, int i, int n, const std::vector<int>& a, const std::vector<int>& b, std::vector<std::vector<int>>& returnVec) {
  if (i >= indices.size()) {
    returnVec.push_back(combineLists(indices, a, b));
    return;
  }

  int maxIndex = n - indices.size() + i;
  if (i && n) indices[i] = indices[i - 1] + 1; // Reset this index value to the last one + 1.
  while (indices[i] <= maxIndex) {
    incrementIndices(indices, i + 1, n, a, b, returnVec);
    indices[i]++;
  }
}

// Outer function called with just the two input lists.
std::vector<std::vector<int>> interleaveLists(const std::vector<int>& a, const std::vector<int>& b) {
  int n = a.size() + b.size();
  std::vector<std::vector<int>> returnVec;
  std::vector<int> indices(a.size(), 0);

  incrementIndices(indices, 0, n, a, b, returnVec);
  return returnVec;
}

int main() {
  int n, m;
  std::vector<int> a, b;
  std::cout << "Enter the size of list a: ";
  std::cin >> n;
  a.resize(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  std::cout << "Enter the size of list b: ";
  std::cin >> m;
  b.resize(m);
  for (int i = 0; i < m; ++i)
    std::cin >> b[i];

  std::vector<std::vector<int>> result = interleaveLists(a, b);

  std::cout << "The total number of relative-order interleavings is " << a.size() + b.size() << " choose " << a.size() << ": " << result.size() << std::endl;
  for (int i = 0; i < result.size(); ++i) {
    for (int item: result[i]) {
      std::cout << item << ", ";
    }

    std::cout << std::endl;
  }

  return 0;
}

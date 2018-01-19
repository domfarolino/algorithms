#include <iostream>
#include <vector>
#include <unordered_map>

// Source: https://leetcode.com/problems/find-anagram-mappings

/**
 * Find Anagram Mappings
 * The problem description can be found above, but basically
 * given two anagrams presented as lists: write a function that
 * returns the index mapping from list A => list B, where the index
 * mapping is defined as an array such that arr[i] is the index in B
 * in which A[i] appears.
 *
 * Good questions to clarify assumptions:
 *    Can the list have duplicates? Yes
 *    Are the lists equal size? Yes, by extension of them being anagrams
 *    What do the lists contain? Integers
 *    What is the largest integer a list can contain? 10^5
 *    What is the maximum length of the input lists? 100
 *    If the anagrams contain duplicates, does the index mapping array
 *      have to contain unique values, or can I repeat indices that A[i]
 *      appear at. For example, if I was given A: [1, 1, 2], B: [1, 2, 1]
 *      can I return [0, 0, 1] or must I return [0, 2, 1]? You can return
 *      [0, 0, 1] (repeating indices if you'd like).
 *
 *    Note that the last question there makes the solution a little easier
 *    since we don't have to find EACH index that a duplicate A[i] appears
 *    at if we've already used one of the indices, instead we can just always
 *    reuse its first appearance (I'm not sure why, because then it is possible
 *    for this solution to work on As and Bs that are not anagrams, but oh well!
 *
 * The solution for this problem is relatively simple, after going through some
 * examples manually, the algorithm practically writes itself. More or less, for
 * each item in list `a`, we need to find an appearance of `a` in `b`. We can do
 * this naively by looping through each item in `b` for each item in `a`, and stopping
 * at the first occurrence we find in `b`. This solution has a time complexity of O(n^2)
 * with O(1) space, and is trivial to implement.
 *
 * We can optimize this algorithm by finding a way to come up with the index in `b`, of a
 * given `a` element faster. In fact, by using a hash table we can retrieve this value in
 * O(1), making the overall algorithm O(n).
 */

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
std::vector<int> anagramMappings(const std::vector<int>& a, const std::vector<int>& b) {
  std::vector<int> returnVec;
  std::unordered_map<int, int> uMap;

  // Initialize uMap with the indices all `b` values are at
  for (int i = 0; i < b.size(); i++) {
    uMap[b[i]] = i;
  }

  for (int i = 0; i < a.size(); i++) {
    returnVec.push_back(uMap[a[i]]);
  }

  return returnVec;
}

int main() {
  std::vector<int> a = {33, 55, 26, 85, 5, 11}; // -std=c++0x
  std::vector<int> b = {55, 5, 11, 33, 26, 85};
  std::vector<int> p = anagramMappings(a, b);

  std::cout << "[";
  for (std::vector<int>::const_iterator i = p.begin(); i != p.end(); i++) {
    std::cout << *i;
    if (i + 1 != p.end()) std::cout << ", ";
  }

  std::cout << "]" << std::endl;

  return 0;
}

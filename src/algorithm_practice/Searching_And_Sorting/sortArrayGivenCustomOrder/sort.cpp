#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

// Source: http://www.geeksforgeeks.org/sort-array-according-order-defined-another-array/

/**
 * Sort an array according to the order defined by another array
 *
 * This problem can be very similar to sorting an array based
 * off of the natural number ordering. Normally we can tell if a pair
 * of numbers are inverted by checking their values, because their values
 * happen to directly correspond to their indices in the order of natural integers.
 * This means we can easily tell that 1 < 2, however given the custom orders array
 * [2, 1, 8, 3] we cannot trivially tell that 2 < 8 without knowing the indices of both
 * of those numbers in the custom orders array. We can keep a hash table to store these values.
 * Storing these values will take O(m) where m = the length of the custom orders array, and retrieval
 * is O(1) given we have a O(1) hashing algorithm. So we can turn [2, 1, 8, 3] into the unordered map:
 *
 * u_map[2] = 0
 * u_map[1] = 1
 * u_map[8] = 2
 * u_map[3] = 3
 *
 * Then when we come across 2 and one in our array, we can tell that 2 should be less than 1 because
 * u_map[2] < u_map[1]. The rest is a basic implementation of mergeSort with a small modification to accept
 * the unordered_map. This is the same as writing a custom comparator to index the array that defines our custom
 * order.
 *
 * We could also use a strictly hashing method. This could be done by taking all of the numbers in our array to sort
 * and in a hashmap, inserting {number: count}, and for every number in our custom order array, output some number the
 * number of times it appears in our hash map given it exists, and remove it from the hashmap. For all numbers left over
 * in our source array (still existing in our hashmap), we can do one of two things. If we want them in sorted order given
 * their natural indices, all we have to do is sort the remaining numbers in the hashmap which takes O(plog(p)) time where p
 * is the number of elements left in our map. If we want them in the order they came in then we can maintain some vector alongside
 * our hash map to push_back() each value as we come across. Then at the very end for each value in the vector that does exist in
 * the hmap, put it at the back of our sorted array. This method demonstrates the classical tradeoff between speed and time. The time
 * complexity of the ending portion of this method is O(p) however we must keep double the space. However since our space complexity
 * increases from O(n) to O(n) + O(n) = O(2n), its asymptotic complexity does not actually increase.
 *
 * The below algorithm implements mergesort using the unordered_map as a custom comparator. Again, we could use a strictly hashing
 * method, or actually abstract our usage of the unordered_map in the below merge() routine to a custom comparator.
 * Complexity analysis of the following solution:
 * Time complexity: O(mlog(m) + n) m = size of source array, n = size of order array - note we have to hash each value in the array indicating element order
 * Space complexity: O(m)
 */

/**
 * Utility function for mergeSort
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
void merge(vector<int>& nums, int l, int m, int r, unordered_map<int, int>& uMap) {
  int n1 = m-l+1;
  int n2 = r-m;

  vector<int> left(n1), right(n2);

  for (int i = 0; i < n1; ++i) left[i] = nums[l+i];
  for (int i = 0; i < n2; ++i) right[i] = nums[m+1+i];

  left.push_back(INT_MAX);
  right.push_back(INT_MAX);

  int j = 0, k = 0, compare1, compare2;
  for (int i = 0; i < n1+n2; ++i) {

    // Both left[j] and right[k] do not exist in map, use natural values
    if (uMap.find(left[j]) == uMap.end() && uMap.find(right[k]) == uMap.end()) {
      compare1 = left[j];
      compare2 = right[k];
    } else if (uMap.find(left[j]) == uMap.end()) {
      compare1 = INT_MAX;
      compare2 = right[k];
    } else if (uMap.find(right[k]) == uMap.end()) {
      compare1 = left[j];
      compare2 = INT_MAX;
    } else {
      compare1 = uMap[left[j]];
      compare2 = uMap[right[k]];
    }

    if (compare1 < compare2) {
      nums[l+i] = left[j++];
    } else {
      nums[l+i] = right[k++];
    }
  }

}

/**
 * Mergesort using an unordered_map as a custom comparator
 * Time complexity: O(mlog(m) + n)
 * Space complexity: O(m)
 */
void mergeSortWithCustomOrder(vector<int>& nums, int l, int r, unordered_map<int, int>& uMap) {
  if (l < r) {
    int m = (l + r)/2;

    mergeSortWithCustomOrder(nums, l, m, uMap);
    mergeSortWithCustomOrder(nums, m+1, r, uMap);
    merge(nums, l, m, r, uMap);
  }
}

int main() {
  int total, l1, l2, tmp;
  vector<int> nums, customOrder;
  unordered_map<int, int> uMap;

  cin >> total;
  for (int i = 0; i < total; ++i) {

    cin >> l1 >> l2;
    nums.reserve(l1);
    customOrder.reserve(l2);
    
    for (int j = 0; j < l1; ++j) {
      cin >> tmp;
      nums.push_back(tmp);
    }

    for (int j = 0; j < l2; ++j) {
      cin >> tmp;
      customOrder.push_back(tmp);
    }

    for (int i = 0; i < customOrder.size(); ++i) uMap[customOrder[i]] = i;

    mergeSortWithCustomOrder(nums, 0, nums.size()-1, uMap);

    for (int i = 0; i < nums.size(); ++i) {
      cout << nums[i] << " ";
    }

    nums.clear();
    customOrder.clear();
    uMap.clear();
    cout << endl;
  }

  return 0;
}
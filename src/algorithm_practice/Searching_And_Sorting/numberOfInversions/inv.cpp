#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Source: CLRS and others
// OJ Source: http://www.geeksforgeeks.org/counting-inversions/

/**
 * Return the number of inversions in an array.
 *
 * We know in the worst case (reverse sorted array) there is at most Theta(n^2)
 * inversions, therefore it is natural to think that the optimal algorithm musttouch
 * all unordered pairs of elements in the array to determine the inversion count. There
 * are nChoose2, (n^2 - n)/2, or Theta(n^2) of these pairs. This makes it seem like the
 * optimal algorithm must touch all Theta(n^2) of these pairs to get the inversion count
 * however we can make an observation to prove the optimal algorithm is not Theta(n^2).
 *
 * We know that merge sort can turn an array containing Theta(n^2) inversions into an array with 0 inversions
 * (sorted) in only Theta(nlog(n)) steps thus proving it is a more optimal solution than our naive one. This is
 * true because we do not actually have to look at every single pair of elements. With two sorted arrays, we can
 * infer that one inversion implies many others. You can see this in the merge function below. For example, if we
 * the two sorted arrays [5, 6, 7, 8] and [1, 2, 3, 4] we can know that since the pair (1, 5) is inverted, then the
 * pairs (1, 6), (1, 7), and (1, 8) must also be inverted. Therefore from one inversion, we can infer 3 others in O(1).
 *
 * It is important to note that if we actually needed to print each inverted pair we would have to touch every pair thus
 * making the optimal solution Theta(n^2). This is a common pattern in algorithms, where returning the number of times some
 * quality appears in some structure can be cheaper than returning all of the instances in which that quality appears.
 *
 * Since we're working with a modified mergesort algorithm, the complexity breakdown is as follows:
 * Time complexity: O(nlog(n))
 * Space complexity: O(n)
 */

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 * Modified merge algorithm which returns
 * the number of inversions and merges two sorted
 * arrays.
 */
int merge(vector<int>& nums, int l, int m, int r) {
  int n1 = m-l+1;
  int n2 = r-m;

  vector<int> left(n1), right(n2);

  for (int i = 0; i < n1; ++i) left[i] = nums[l+i];
  for (int i = 0; i < n2; ++i) right[i] = nums[i+m+1];

  left.push_back(INT_MAX);
  right.push_back(INT_MAX);

  int j = 0, k = 0, inversions = 0; // j = left index, k = right index
  for (int i = l; i <= r; ++i) {
    if (left[j] <= right[k]) nums[i] = left[j++];
    else {
      inversions += (n1-j);
      nums[i] = right[k++];
    }
  }

  return inversions;
}

/**
 * Time complexity: O(nlog(n))
 * Space complexity: O(n)
 */
int mergeSort(vector<int>& nums, int l, int r) {
  if (l < r) {
    int m = (l + r)/2, inversions = 0;
    inversions += mergeSort(nums, l, m);
    inversions += mergeSort(nums, m+1, r);
    inversions += merge(nums, l, m, r);
    return inversions;
  } else {
    return 0;
  }
}

int main() {
  int total, length, tmpNum;
  vector<int> nums;

  cin >> total;

  for (int i = 0; i < total; ++i) {
    cin >> length;

    for (int j = 0; j < length; ++j) {
      cin >> tmpNum;
      nums.push_back(tmpNum);
    }

    int inversions = mergeSort(nums, 0, nums.size()-1);

    cout << inversions << endl;

    nums.clear();
  }

  return 0;
}

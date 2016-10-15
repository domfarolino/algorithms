#include <iostream>
#include <climits>

using namespace std;

// My blog post on merging two sorted lists: https://chinocode.com/Merging-K-Sorted-Arrays-and-Linked-Lists/

/**
 * Merge Sort
 * Divide and conquer sorting routine
 * Time complexity: O(nlog(n))
 * Space complexity: O(n)
 *
 * The idea is simple. If we want to sort
 * an entire array, we first sort the left
 * half, then sort the right half, then merge
 * both arrays together. This yields a divide and
 * conquer algorithm because we first divide the
 * input in half, recursively solving each subproblem
 * and then merge the result. In short this means we'll
 * be merging all n elements once, n/2 elements twice,
 * n/4 four times, and so on. This gives us the following
 * sum: n + 2*(n/2) + 4*(n/4) + 8*(n/8) + ... + n*(n/n). It
 * should be clear that we're always doing n amount of work
 * at each level, and we're doing n amount of work exactly the
 * number of times we can split n in half. This number is log(n)
 * therefore the time complexity of this routine is O(nlog(n)).
 *
 * Merging two sorted contiguous arrays can be done in O(n) time.
 * Full documentation on this algorithm can be found in the above
 * linked blog post however we basically want to look at the first
 * values of each array and copy the smallest of the two into the
 * final array. We then need to make sure we're looking at the next
 * value of the array we took the smaller value from on our next iteration.
 * We can stop once we exhaust one array. Then we want to copy all of
 * the contents of the non-exhausted array into our final array. Below
 * I have two slightly different merge algorithms. They differ in the way
 * they exhaust one of the lists.
 *
 * Performing the merge operation in constant space turns
 * out to be very difficult. It is an area of research
 * still under study. Konrod's method of internal buffering
 * and block partitioning is one known way to do it. More information:
 * http://stackoverflow.com/questions/2126219/
 */

// Utility function to print array given size
void printArray(int arr[], int size) {
  cout << "{ ";

  for (int i = 0; i < size; ++i) {
    cout << arr[i];

    if (i < size - 1) {
      cout << ", ";
    }
  }

  cout << " }" << endl;
}

/**
 * This merge method will exhaust one array and then
 * copy the contents of the other to our final array.
 * We do this by going into a while loop while each
 * array has elements to contribute to our final array.
 * When we break out we simply run a different while
 * loop on the array that still has elements left to
 * contribute. This last while loop will copy all of
 * the elements from the non-exhausted array to the final
 * ouput array.
 */
void mergeNoSentinel(int list[], int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int *L = new int[n1];
  int *R = new int[n2];
  for (int i = 0; i < n1; i++)
    L[i] = list[l + i];
  for (int j = 0; j < n2; j++)
    R[j] = list[m + 1 + j];

  int i = 0;
  int j = 0;
  int k = l;

  while (i < n1 && j < n2) list[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

  while (i < n1) list[k++] = L[i++];

  while (j < n2) list[k++] = R[j++];

  delete [] L;
  delete [] R;
}

/**
 * This merge method adds a sentinel value
 * INT_MAX to the end of each sorted array.
 * Then for as many values that exist in each
 * sorted array not including our sentinel value
 * we take the smallest of the two elements appearing
 * at the beginning of each array. We then increment
 * the index value we used to get this smaller element.
 * Eventually when one array is exhausted we'll be looking
 * at the sentinel value INT_MAX from it, and this will
 * force us to always take values from the non-exhausted
 * array until it too becomes exhausted. At this point we've
 * used all of our elements and our loop will stop.
 */
void merge(int arr[], int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int *a1 = new int[n1+1];
  int *a2 = new int[n2+1];

  for (int i = 0; i < n1; ++i)
    a1[i] = arr[l + i];
  for (int j = 0; j < n2; ++j)
    a2[j] = arr[m + 1 + j];

  a1[n1] = INT_MAX;
  a2[n2] = INT_MAX;

  int j = 0, k = 0;

  /**
   * One loop since we used sentinel
   * values designed to pull values from
   * the non-exhausted array once one
   * becomes exhausted.
   */
  for (int i = l; i <= r; ++i) {
    if (a1[j] < a2[k]) arr[i] = a1[j++];
    else arr[i] = a2[k++];
  }

  delete[] a1;
  delete[] a2;
}

void mergeSort(int list[], int l, int r){

  /**
   * We only want to sort the array if
   * the right index is greater than
   * the left index. If they are equal
   * we have a single element array which
   * is by definition sorted. To walk through
   * our next edge case, when an input array
   * contains two values i.e. when r = l+1, we
   * can see our m will be calculated as l after
   * floor division, thus splitting the array into
   * halves consisting of the first element and the
   * second element. Since this is a basic demonstration
   * of floor division, we can be sure that this will work
   * for all r > l.
   */
  if (r > l) {
    int m = (r - l)/2 + l; // integer overflow-safe way of doing int m = (l + r)/2;
    mergeSort(list, l, m);
    mergeSort(list, m+1, r);
    merge(list, l, m, r);
  }

}

int main() {
  int a[] = {5, 4, 3, 2, 1};
  mergeSort(a, 0, 4);
  printArray(a, 5);

  return 0;
}

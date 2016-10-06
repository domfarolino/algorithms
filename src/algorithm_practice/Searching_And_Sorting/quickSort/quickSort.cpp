#include <iostream>

using namespace std;

/**
 * Implementation of quicksort algorithm.
 *
 * It works by choosing a midpoint in the array
 * and recursively calls itself on each half.
 *
 * Time Complexity
 * ---------------
 * Ω(n log(n))   Best case
 * Θ(n log(n))   Average
 * O(n^2)        Worst case
 *
 * Space Complexity
 * ----------------
 * O(log(n))    Worst case
 */


void quicksort(int array[], int left, int right) {
  int i = left;
  int j = right;
  int tmp;
  int pivot = array[left + ((right - left) / 2)]; // safely calculate middle element

  while (i <= j) {
    
    while (array[i] < pivot) {
      i++;
    }
    
    while (array[j] > pivot) {
      j--;
    }
    
    if (i <= j) {
      tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
      i++;
      j--;
    }
  
  }

  if (left < j) {
    quicksort(array, left, j);
  }
  
  if (i < right) {
    quicksort(array, i, right);
  }

}

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

int main(int argc, char **argv) {
  
  int arr[14] = {9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -33};
  int size = sizeof(arr)/sizeof(arr[0]);
  
  printArray(arr, size);
  quicksort(arr, 0, size-1);
  printArray(arr, size);

  return 0;
}
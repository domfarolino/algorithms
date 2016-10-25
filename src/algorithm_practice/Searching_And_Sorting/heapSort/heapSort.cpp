#include <iostream>
#include <climits>

using namespace std;
/*
    Heap Sort:
    Time complexity: o(n(log(n)))
    Space Complexity: o(n)
    Heap sort is a comparison based sorting technique based on Binary Heap data structure.

    And Binary Heap is a Complete Binary Tree where items are stored in a
    special order such that value in a parent node is greater(or smaller) than
    the values in its two children nodes. The former is called as max heap and the latter is called min heap.
    The heap can be represented by binary tree or array.
    Since a Binary Heap is a Complete Binary Tree, it can be easily represented as array and array based
    representation is space efficient.
    If the parent node is stored at index i, the left child can be calculated by (2*i + 1) and right child by (2*i + 2)
    (assuming the indexing starts at 0).
    see the following example for more clarification.
            max Heap                                          min heap
               14                                                 1
              /  \                                              /   \
            10    8                                            5     7
           /  \    \                                          / \     \
          1    7     5                                      10   8     14
*/

/*
    To heapify a subtree rooted with node pos which is an
    index in arr[]. heap_size is the size of the current heap.
*/
void Max_Heapify (int arr[], int pos, int heap_size) {
    int larger = pos;
    int left = (pos << 1) + 1;                              // similar to (pos * 2 + 1)
    int right = (pos << 1) + 2;                             // similar to (pos * 2 + 2)
    if (left < heap_size && arr[left] > arr[larger])
        larger = left;
    if (right < heap_size && arr[right] > arr[larger])
        larger = right;
    if (larger != pos) {
        swap(arr[pos], arr[larger]);                         // violate max-heap property
        Max_Heapify(arr, larger, heap_size);                 // Recursively heapify the affected sub-tree
    }
}


// Build heap (rearrange array)
void Build_Max_Heap (int arr[], int size) {
    for (int pos = size-1; pos >= 0; pos--) {
        Max_Heapify (arr, pos, size);
    }
}

// main methos of heap sort
void heapSort (int arr[], int size) {
    int heapSize = size;
    Build_Max_Heap (arr, size);                       // build heap

    for (int pos = size-1; pos >= 1; pos--) {           // One by one extract an element from heap
        swap (arr[0], arr[pos]);                        // move current root to end to make it sorted
        --heapSize;                                     // reducing the heap size
        Max_Heapify (arr, 0, heapSize);                 // call max-heapify in the reduced heap
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


int main () {
    int size;
    cin >> size;
    int arr[size];
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    heapSort(arr, size);
    printArray(arr, size);              // print array after sorting
    return 0;
}

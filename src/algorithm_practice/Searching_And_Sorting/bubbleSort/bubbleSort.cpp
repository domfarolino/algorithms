#include<iostream>
/**
*Bubble sort
*Sometimes referred to as sinking sort, is a simple sorting algorithm that
*repeatedly steps through the list to be sorted, compares each pair of 
*adjacent items and swaps them if they are in the wrong order.
*Complexity for this algorithm will be O(n^2)
*/
 using namespace std;
 

/* Function for bubble sort*/

template<typename T>

 void bubble_sort (T arr[], int length) {
  int i, j;
  T temp;
  for (i = 0; i < length; ++i) 
    for (j = 0; j < length - i - 1; ++j) 
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr [j + 1];
        arr[j + 1] = temp;
      }
   }		

  /*End of function*/

  int main () {
    int length;
    cout << "Enter the number of elements you want to sort \n";
    cin >> length;
    int arr[length];   //Defining an array of specific length
    for (int i = 0; i < length; ++i) {
      cout << "Enter element number " << i+1 << endl;
      cin >> arr[i];
    }
   	bubble_sort(arr, length);   //Sorting the entered array
   	cout << " { ";
    for (int i = 0; i < length; ++i) {
   	  
   		cout << arr[i] ;
      if (i != length-1)
      {
        cout << ", " ;
      }
  	}
    cout << " }";
   	return 0;
  }

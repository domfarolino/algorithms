#include<bits/stdc++.h>
/*Bubble sort, sometimes referred to as sinking sort, is a simple sorting algorithm that
repeatedly steps through the list to be sorted, compares each pair of adjacent items and
 swaps them if they are in the wrong order.*/
 using namespace std;
 

/* Function for bubble sort*/

 void bubble_sort (int arr[], int n)
 {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n - i - 1; ++j)
      if (arr[j] > arr[j + 1])
     {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
  }		

  /*End of function*/

  int main ()
  {
  	int a[10]={1,3,6,7,8,9,5,4,2,10};
  	bubble_sort(a,10);
  	for (int i = 0; i < 10; ++i)
  	{
  		cout<<a[i]<<" ";
   	}
   	return 0;
  }

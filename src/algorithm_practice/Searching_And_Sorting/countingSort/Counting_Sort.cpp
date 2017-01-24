/*   
-Counting Sort is a linear time sorting algorithm (Mostly used to sort positive integer of known upper range) .
-The following algorithm works with one based indexing for 'a' and 'b'.
-An important property of counting sort is that it is stable: numbers with the same
  value appear in the output array in the same order as they do in the input array. That
  is, it breaks ties between two numbers by the rule that whichever number appears
  first in the input array appears first in the output array.
-'a' is my array storing the numbers to be sorted while 'b' is the sorted array that would be returned by the count function.(0 is added in front of 
  array 'a' for completeness as one based indexing is followed)
-'k' is the upper range of integers.

Explanation:(In count function)
 - The first for loop initializes the array C to all zeros, then the next for loop inspects each input element. If the
    value of an input element is i, we increment C[i]. Thus, after the second for loop, C[i] holds
    the number of input elements equal to i for each integer i=0,1,2....K.The third for loop
    determine for each i=0,1...k how many input elements are less than or equal to i by keeping a running sum of the array C.
    Finally, the last for loop of lines each element A[j]  into its correct sorted position in 
    the output array B. If all n elements are distinct, then when we
    first enter the last for loop, for each A[j], the value C[A[j]] is the correct 
    final position of A[j] in the output array, since there are C[A[j]]  elements less than or equal
    to A[j] . Because the elements might not be distinct, we decrement C[A[j]] each
    time we place a value A[j]  into the B array. Decrementing C[A[j]]  causes the
    next input element with a value equal to A[j] , if one exists, to go to the position
    immediately before A[j] in the output array.
    Source:CLRS
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>


void count(int *,int *,int);
int n;

int main()
{
    int k,i;
    n=10;
    k=54;
    int a[11]= {0,1,9,8,4,24,2,5,4,54,23};
    int b[11]= {0};
    for(i=1; i<=n; i++)
    count(a,b,k);
    for(i=1; i<=n; i++)
    {
        printf("%d ",b[i]);
    }
    return 0;
}
void count(int *a,int *b,int k)
{
    int c[k+1],i,j;

    for(i=0; i<k+1; i++)
    {
        c[i]=0;
    }

    for(i=1; i<=n; i++)
    {
        c[a[i]]=c[a[i]]+1;
    }

    for(i=1; i<=k; i++)
    {
        c[i]=c[i]+c[i-1];
    }
    for(j=n; j>=1; j--)
    {
        b[c[a[j]]]=a[j];
        c[a[j]]=c[a[j]]-1;
    }

}

/*

 quick sort is a sorting technique, which sorts the array(with almost diffrent values)
 in really quick time. 
{
	best case when numbers are random.
	worst case when number are nearlysorted.
}

the basic logic of quick sort is that it takes an element of the given array as a pivot and 
then puts all the elements less than pivot on its left side. in the similar manner, puts all 
the elements greter than the pivot on to its right. this algorithm is implemented in a 
recursive manner and finally the array is sorted.
cheers! 

*/
#include<iostream>
using namespace std;

void swape(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

int partition(int arr[],int pivot,int low,int high)
{
	int left=low+1,right=high;
	while(left<right)
	{
		while(arr[left]<=pivot&&left<=right)
		++left;
		while(arr[right]>=pivot&&left<=right)
		--right;
		if(left<right)
		swape(&arr[left],&arr[right]);
	}
	swape(&arr[low],&arr[right]);
	return right;
}

void quick_sort(int arr[],int low,int high)
{
	if(low<high)
	{
		int pos=partition(arr,arr[low],low,high);
		quick_sort(arr,low,pos-1);
		quick_sort(arr,pos+1,high);
	}
}

int main()
{
	int arr[10]={5,62,54,87,32,16,178,153,70,119};
	quick_sort(arr,0,9);
	for(int i=0;i<10;++i)
	{
		cout<<arr[i]<<" ";
	}
}

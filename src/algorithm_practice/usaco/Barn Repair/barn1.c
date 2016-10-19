/*
ID: caroltr1
LANG: C
TASK: barn1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int M, S, C;
int stall[200], stallGap[200], stallGapIndex[200];
void merge(int *arr, int left, int mid, int right);
void mergeSort(int *arr, int left, int right);
int main()
{
    FILE *fin = fopen("barn1.in","r");
    FILE *fout = fopen("barn1.out","w");
    fscanf(fin, "%d %d %d", &M, &S, &C);
    int i;
    for (i=0; i<C; i++)
        fscanf(fin,"%d", &stall[i]);
    mergeSort(stall, 0, C-1);
   // for (i=0; i<C; i++)
        //printf("%d ", stall[i]);
    for (i=0; i<C-1; i++)
        stallGap[i] = stall[i]-stall[i+1];
    mergeSort(stallGap, 0, C-2);
    int minStallCovered = stall[0] - stall[C-1] + 1;
    //printf("\nFirst minStallCovered %d\n", minStallCovered);
    int someNum = M;
    if (M>C) someNum = C;
    for (i=0; i<someNum-1; i++)
    {
        minStallCovered -= stallGap[i]-1;
        //printf("%d\n", minStallCovered);
    }
    //printf("Final minStallCovered %d\n", minStallCovered);
    fprintf(fout,"%d\n", minStallCovered);
    exit(0);

}

void merge(int *arr, int left, int mid, int right)
{
    int i, j, k;
    int leftLen = mid - left + 1;
    int rightLen = right - mid;

    //Create empty arrays
    int Left[leftLen]; int Right[rightLen]; int LeftIndex[leftLen]; int RightIndex[rightLen];
    //Copy data to temp arrays
    for (i=0; i<leftLen; i++)
    {
        Left[i]=arr[left+ i];
        LeftIndex[i] = left+i;
    }
    for (j=0; j<rightLen; j++)
    {
        Right[j]=arr[j+mid+1];
        RightIndex[j]=j+mid+1;
    }
    //Merge those arrays into one
    i=0; j=0; k=left;
    while(i<leftLen && j<rightLen)
    {
        if (Left[i] >= Right[j])
        {
            arr[k]=Left[i];
            stallGapIndex[k] = LeftIndex[i];
            i++;
        }
        else
        {
            arr[k]=Right[j];
            stallGapIndex[k] = RightIndex[j];
            j++;
        }
        k++;
    }
    //Copy the remaining elements of Left[], if there
    //are any
    while(i<leftLen)
    {
        arr[k]=Left[i];
        stallGapIndex[k] = LeftIndex[i];
        k++; i++;
    }

    //Copy the remaining elements of Right[], if there
    //are any
    while(j<rightLen)
    {
        arr[k]=Right[j];
        stallGapIndex[k] = RightIndex[j];
        k++; j++;
    }
}
//left is the left index and right is the right index
//of the sub-array
void mergeSort(int *arr, int left, int right)
{
    if (left<right)
    {
        int mid = left+(right-left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

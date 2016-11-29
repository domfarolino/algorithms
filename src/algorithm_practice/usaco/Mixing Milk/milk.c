/*
ID: caroltr1
LANG: C
TASK: milk
*/#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXN 2000000
#define MAXM 5000
void BubbleSort(int *arr, int *arr2, int len);
int Greedy(int *arr, int *arr2, int len);
int N, M;
int main()
{
    FILE *fin = fopen("milk.in","r");
    FILE *fout = fopen("milk.out","w");
    fscanf(fin, "%d %d", &N, &M);
    int i;
    int P[MAXM], A[MAXM];
    for (i=0; i<M; i++)
        fscanf(fin,"%d %d", &P[i], &A[i]);
    BubbleSort(P, A, i);
    fprintf(fout,"%d\n",Greedy(P, A, i));
    exit(0);
}

void BubbleSort(int *arr, int *arr2, int len)
{
    int i, j, temp, temp2;
    for (i=0; i<len-1; i++)
        for (j=i+1; j<len; j++)
        if (arr[i] > arr[j])
    {
        temp = arr[i]; temp2 = arr2[i];
        arr[i] = arr[j]; arr2[i]= arr2[j];
        arr[j]=temp; arr2[j]=temp2;
    }
}

int Greedy(int *arr, int *arr2, int len)
{
    int i, numMilk=0, money=0;
    for (i=0; numMilk<N-arr2[i]; i++)
    {
        numMilk+=arr2[i];
        money += arr2[i]*arr[i];
    }
    int remaining = N-numMilk;
    money+= remaining*arr[i];
    return money;
}

/*
ID: caroltr1
LANG: C
TASK: dualpal
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXNUM 10000
#define MAXLEN 100
int convertBase(int num, int base, int* arr);
bool isPalindrome(int* arr, int len);
int N, S;
int main()
{
    //FILE* fin = fopen("dualpalin.txt","r");
    //FILE* fout = fopen("dualpalout.txt","w");
    FILE* fin = fopen("dualpal.in","r");
    FILE* fout = fopen("dualpal.out","w");
    fscanf(fin,"%d", &N);
    fscanf(fin,"%d", &S);
    int palcount = 0; int num = S; int base=2; int paltime; int numlen;
    while(palcount < N)
    {
        num++;
        int arr[MAXLEN];
        for (base=2, paltime=0; base<=10; base++){
            numlen=convertBase(num,base,arr);
            if (isPalindrome(arr,numlen)){
                paltime++;
                if (paltime==2){
                    fprintf(fout, "%d\n",num);
                    palcount++;
                    break;
                }
            }
        }
    }
    exit(0);
}

int convertBase(int num, int base, int *arr)
{
    int i=0;
    while(num/base != 0)
    {
        arr[i++]=num%base;
        num/=base;
    }
    arr[i]=num;
    return i;
}

bool isPalindrome(int arr[], int len)
{
    int i;
    for (i=0; i<len; i++)
    {
        if (arr[i]!=arr[len-i])
            return false;
    }
    return true;
}

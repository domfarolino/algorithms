
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXLEN 20
int convertBase(int i, int *arr);
int square(int num, int ex, int *arr);
bool isPalindrome(int *arr, int j);
void arrcpy(int *one, int *two, int len);

char letter[25]={'0','1','2','3','4','5','6','7','8','9',
                 'A','B','C','D','E','F','G','H','I','K'};
int B;
int main()
{
    //FILE* fin = fopen("palsquarein.txt", "r");
    //FILE* fout = fopen("palsquareout.txt", "w");
    FILE* fin = fopen("palsquare.in", "r");
    FILE* fout = fopen("palsquare.out", "w");
    fscanf(fin,"%d",&B);
    int i, j, k, lenNum;
    fprintf(fout,"%d %d\n",1,1);
    for (i=2; i <=300; i++)
    {
        int arr[MAXLEN], num[MAXLEN];
        j = convertBase(i, arr);
        lenNum = j;
        arrcpy(arr, num, lenNum);
        j = square(i, j, arr);
        if (isPalindrome(arr, j))
        {
            for (k=lenNum; k>=0; k--)
                fprintf(fout,"%c", letter[num[k]]);
            fprintf(fout," ");
            for (k=j; k>=0; k--)
                fprintf(fout,"%c", letter[arr[k]]);
            fprintf(fout, "\n");
        }
    }
    exit(0);
}

int convertBase(int i, int *arr)
{
    int j=0;
    while(i/B != 0)
    {
        arr[j] = i%B;
        j++;
        i/=B;
    }
    arr[j]=i;
    return j;
}
int square(int num, int ex, int *arr)
{
    int temp[MAXLEN];
    int i,j,k;
    for (i=0; i<=ex*2; i++)
        temp[i]=0;
    for (i=0; i<=ex; i++)
        for (j=0; j<=ex; j++)
        temp[i+j]+=arr[i]*arr[j];
    for(i=0; i<2*ex; i++)
    {
        arr[i]=temp[i]%B;
        temp[i+1]+=temp[i]/B;
    }
    arr[i]=temp[i]%B;
    if (temp[i]>=B)
        {
            arr[i+1]=temp[i]/B;
            i++;
        }
    return i;
}
bool isPalindrome(int *arr, int j)
{
    int i,k;
    for (i=0; i<(j+1)/2; i++)
        if (arr[i] != arr[j-i])
        return false;
    return true;
}
void arrcpy(int *one, int *two, int len)
{
    int k;
    for (k=0; k<=len; k++)
        two[k]=one[k];
    return;
}


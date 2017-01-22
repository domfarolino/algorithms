/*
ID: caroltr1
LANG: C
TASK: transform
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define maxN 10
bool checkCases(bool isReflected, int caseNum);
int N;
int in[maxN][maxN], out[maxN][maxN];
int main()
{
    //FILE* fin = fopen("transformin.txt", "r");
    //FILE* fout; = fopen("transformout.txt", "w");
    FILE* fin = fopen("transform.in", "r");
    FILE* fout = fopen("transform.out", "w");
    fscanf(fin,"%d",&N);
    fgetc(fin);
    int i, j;
    for (i=0; i < N; i++)
    {
        for(j=0; j<N; j++)
           in[i][j] = fgetc(fin);
        fgetc(fin);
    }
    for (i=0; i < N; i++)
        for(j=0; j<N; j++)
        {
        for(j=0; j<N; j++)
           out[i][j] = fgetc(fin);
        fgetc(fin);
        }
    int caseNum = 7;
    for (i=1; i <= 3; i++)
    {
        if (checkCases(false,i))
        {
            caseNum = i;
            break;
        }
        if (checkCases(true,i))
        {
            caseNum = 5;
            break;
        }
    }
    if (caseNum == 7 && checkCases(false, 4))
        caseNum = 4;
    if (caseNum == 7 && checkCases(false, 6))
        caseNum = 6;
    fprintf(fout, "%d\n", caseNum);
    fclose(fin); fclose(fout);
    exit(0);

}
bool checkCases(bool isReflected, int caseNum)
{
    int i, inVal,outVal;
    for (i=0; i<N; i++)
    {
        int k;
        for (k=0; k<N; k++)
        {
            switch (caseNum)
            {
            case 1:
                outVal = out[k][N-i-1]; break;
            case 2:
                outVal = out[N-i-1][N-k-1]; break;
            case 3:
                outVal = out[N-k-1][i]; break;
            case 4:
                outVal = out[i][N-k-1]; break;
            case 6:
                outVal = out[i][k]; break;
            }
            if (!isReflected)
                inVal = in[i][k];
            else inVal = in[i][N-k-1];
            if (inVal!= outVal)
                return false;
        }
    }
    return true;
}


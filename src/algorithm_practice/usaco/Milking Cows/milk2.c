/*
ID: caroltr1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 5000
#define MAXTIME 1000000
int time[MAXLEN][2];
int N, endWork;
void insertionSort(int time_size);
int maxWork(int index);
int max(int a, int b);
int main()
{

	//FILE* fin = fopen("milk2in.txt","r");
	//FILE* fout = fopen("milk2out.txt","w");
	FILE* fin = fopen("milk2.in","r");
	FILE* fout = fopen("milk2.out","w");
	if (fin == NULL)
	{
		fprintf(stderr,"Can't open file\n");
		exit(1);
	}
	fscanf(fin,"%d",&N);
	int Work, Rest, startWork, startRest, endRest;
	int i;
	for (i = 0; i<N; i++)
		fscanf(fin,"%d %d", &time[i][0], &time[i][1]);
	insertionSort(N);
	Work = -1; startWork = time[0][0]; endWork = time[0][1]; Rest = 0;
	i = 0;
	while(i < N)
	{
		startWork =time[i][0];
		Rest = max(Rest, startWork - endWork);
		i = maxWork(i+1);
		Work = max(Work, endWork-startWork);
	}
	fprintf(fout,"%d %d\n",Work, Rest);
	exit(0);
}

int maxWork(int index)
{
	while(index < N)
	{
		endWork = max(endWork,time[index-1][1]);
		if (time[index][0] > endWork)
		break;
		index++;
	}
	return index;
}
int max(int a, int b)
{
	if (a > b)
	return a;
	else return b;
}

void insertionSort(int time_size)
{
	int i, j, val, endVal;
	for (i=1; i < time_size;i++)
	{
		val = time[i][0];
		endVal = time[i][1];
		for (j=i; j>0 && time[j-1][0]>val; j--)
		{
			time[j][0] = time[j-1][0];
			time[j][1] = time[j-1][1];
		}
		time[j][0] = val;
		time[j][1] = endVal;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXLEN 350

int maxFront(int pos, char color);
int maxEnd(int pos, char color);
int max(int a, int b);
bool theSame(char* N);
char N[MAXLEN];
int len = 0;
int maxFrontPos;
int main()
{
	//FILE* fin = fopen("beadsin.txt","r");
	//FILE* fout = fopen("beadsout.txt","w");
	FILE* fin = fopen("beads.in","r");
	FILE* fout = fopen("beads.out","w");
	if (fin == NULL)
	{
		fprintf(stderr,"Can't open file\n");
		exit(1);
	}
	int c, i = 0;
	fscanf(fin,"%d",&len);
	while((c = getc(fin)) != EOF)
		if (c != '\n' && c!= ' ')
			N[i++] = c;
	int maxlen = -1, pos = 0;
	if(theSame(N))
	{
		fprintf(fout,"%d\n",strlen(N));
		exit(0);
	}
	while(pos <= len)
	{
		int maxlenr = max(maxFront(pos,'r')+maxEnd(pos-1,'r'), maxFront(pos,'r')+maxEnd(pos-1,'b'));
		int maxlenb = max(maxFront(pos,'b')+maxEnd(pos-1,'r'), maxFront(pos,'b')+maxEnd(pos-1,'b'));

		if (maxlen < max(maxlenb, maxlenr))
		maxlen = max(maxlenb, maxlenr);
		pos++;
	}
	fprintf(fout,"%d\n",maxlen);
	exit(0);
}

int maxFront(int i, char color)
{
	if (i >= len) i = 0;
	if (N[i] != color && N[i] != 'w') return 0;
	int amount = 1;
	if (i == len-1) i= -1;
	while(N[i+1] == color || N[i+1] == 'w')
	{
		i++;
		if (i >= len-1) i = -1;
	 	amount++;
	}
	maxFrontPos = i;
 	return amount;
}

int maxEnd(int j, char color)
{
	if (j <= -1) j = len-1;
	if (N[j] != color && N[j] != 'w') return 0;
	int  amount = 1;
	if (j == 0) j= len;
	while(N[j-1] == color || N[j-1] == 'w' && j-1 != maxFrontPos)
	{
		j--;
		if(j <= 0) j = len;
		amount++;
	}
 	return amount;
}

int max(int a, int b)
{
	if (a < b)
	return b;
	else return a;
}
bool theSame(char* N)
{
	int i;
	for (i = 1; i < strlen(N); i++)
	if(N[i] != N[i-1])
	return 0;
	return 1;
}

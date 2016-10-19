/*
ID: caroltr1
LANG: C
TASK: namenum
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool checkName(char* name);
int num[10][3] =
{
    'A', 'B', 'C',
    'A', 'B', 'C',
    'A', 'B', 'C',
    'D', 'E', 'F',
    'G', 'H', 'I',
    'J', 'K', 'L',
    'M', 'N', 'O',
    'P', 'R', 'S',
    'T', 'U', 'V',
    'W', 'X', 'Y'
};
char numName[13];
int main()
{
    //FILE* fin = fopen("namenumin.txt","r");
    //FILE* fout = fopen("namenumout.txt","w");
    FILE* file = fopen("dict.txt","r");
    FILE* fin = fopen("namenum.in","r");
    FILE* fout = fopen("namenum.out","w");
    int i = 0, nameCount=0;
    char c;
    while((c=getc(fin))!=EOF)
        numName[i++]= c - '0';
    numName[--i]='\0';
    char first = num[numName[0]][0], second = num[numName[0]][1], third = num[numName[0]][2];
    char name[13];
    while (true)
    {
        if (name[0]>third)
            break;
        fscanf(file,"%s",name);
        if (name[0]==first || name[0]==second || name[0]==third)
        {
            if (checkName(name))
            {
                fprintf(fout,"%s\n",name);
                nameCount++;
            }
        }
    }
    if (nameCount==0)
        fprintf(fout,"NONE\n");
    fclose(fout);
    fclose(file);
    exit(0);
}
bool checkName(char* name)
{
    int lenNum = strlen(numName);
    int lenName = strlen(name);
    if (lenName!=lenNum) return false;
    int i;
    for (i=0; i<lenNum; i++)
        if(name[i]!=num[numName[i]][0] && name[i]!= num[numName[i]][1] && name[i]!=num[numName[i]][2])
            return false;
    return true;
}

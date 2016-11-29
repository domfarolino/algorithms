/*
ID: caroltr1
LANG: C
TASK: wormhole
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAXN 12
int N, total;
int findConnections(int outPoint, bool* visited);
void matchPair(int numMatches), check();
typedef struct
{
    int x, y, match;
} wormhole;
wormhole hole[MAXN+1];
int main()
{
    FILE *fin = fopen("wormhole.in", "r");
    FILE *fout = fopen("wormhole.out", "w");
    fscanf(fin, "%d", &N);
    int i;
    for (i=1; i<=N; i++)
        fscanf(fin, "%d %d", &(hole[i].x), &(hole[i].y));
    matchPair(0);
    fprintf(fout,"%d\n", total);
    exit(0);
}
void matchPair(int numMatches)
{
    int i, j;
    for (i=1; i<=N; i++)
        if (hole[i].match == 0)
        {
            for (j=i; j<=N; j++)
                if (hole[j].match == 0 && j!=i)
                {
                    hole[i].match=j; hole[j].match=i;
                    numMatches++;
                    if (numMatches==N/2)
                        check();
                    else matchPair(numMatches);
                    numMatches--;
                    hole[j].match=0;
                }
            hole[i].match=0;
            return;
        }
}

void check()
{
    bool visited[N+1];
    int i, j, outPoint, enterPoint;
    for (i=1; i<=N; i++)
    {
        for (j=0; j<=N; j++) visited[j]=false;
        visited[i]=true;
        outPoint=hole[i].match;
        while(outPoint!=0)
        {
            enterPoint=findConnections(outPoint, visited);
            if (visited[enterPoint]==true)
            {
                total++;
                return;
            }
            else visited[enterPoint]=true;
            outPoint=(enterPoint==0)? 0 : hole[enterPoint].match;
        }
    }

}

int findConnections(int outPoint, bool* visited)
{
    int minx=INT_MAX, i, index=0;
    for (i=1; i<=N; i++)
    {
        if ( hole[i].y==hole[outPoint].y && hole[i].x > hole[outPoint].x && hole[i].x<minx)
        {
            minx=hole[i].x;
            index=i;
        }
    }
    if (index!=0) return index;
    else return 0;
}


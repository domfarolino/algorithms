
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE* fin = fopen("ride.in","r");
	FILE* fout = fopen("ride.out","w");
	int i;
	char comet[6];
	char group[6];
	fscanf(fin,"%s",comet);
	fscanf(fin,"%s",group);
	int sumComet = 1;
	int sumGroup = 1;
	int lenComet = strlen(comet);
	int lenGroup = strlen(group);
	for (i = 0; i < lenComet; i++){
		sumComet *= comet[i] - 'A' + 1;
	}
	for (i = 0; i < lenGroup; i++){
		sumGroup *= group[i] - 'A' + 1;
	}
	sumComet = sumComet % 47;
	sumGroup = sumGroup % 47;
	if (sumComet == sumGroup)
	fprintf(fout, "GO\n");
	else
	fprintf(fout,"STAY\n");
	exit(0);
}

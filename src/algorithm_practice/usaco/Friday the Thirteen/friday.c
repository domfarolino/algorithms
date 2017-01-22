
#include <stdio.h>
#include <stdlib.h>

int days[][13] = {
       {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	   {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	   };
int week[8];
int main()
{
	FILE* fin = fopen("fridayin.txt","r");
	FILE* fout = fopen("fridayout.txt","w");
	if (fin == NULL)
	{
		fprintf(stderr,"Can't open file\n");
		exit(1);
	}
	int i, num, leap;
	fscanf(fin,"%d",&num);
	int weekDay = 2;
	for (i = 1900; i < 1900 + num; i++)
	{
		leap = (i % 4 == 0 && i % 100 != 0 || (i % 400) == 0);
		int j;
		for (j = 1; j < 13; j++)
		{
			int day13th = weekDay - 2;
			if ((day13th) <= 0) day13th += 7;
			week[day13th]++;
			int monthDay = (days[leap][j] / 7) * 7;
			weekDay += days[leap][j] - monthDay;
			if (weekDay >= 7) weekDay -= 7;
		}
	}
	fprintf(fout,"%d ",week[7]);
	for (i = 1; i < 6; i++)
	fprintf(fout,"%d ",week[i]);
	fprintf(fout,"%d\n",week[6]);
	exit(0);
}

#include <stdio.h.>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 1000

void save_before(int [],int);
void save_after(int[],int);
void sort(int [],int);
void swap(int *arr,int n);

double sec;
clock_t start, stop;



int main()
{
	int i,num;
	
	int *pf;

	scanf("%d", &num);
	pf = (int*)malloc(sizeof(int)*num);
	
	for (i = 0; i < num; i++) {
		pf[i] = rand();
	}
	save_before(pf,num);
	start = clock();
	sort(pf,num);
	stop = clock();
	sec = ((double)stop - start) / CLOCKS_PER_SEC;
	save_after(pf, num);

	printf("Time : %f \n",sec);
	free(pf);
	
	return 0;
}
void save_before(int pf[],int n)
{
	int i;
	FILE *fp;
	fp = fopen("unsorted.txt", "w");
	if (fp == NULL)
	{
		printf("파일 열기 오류");
		return;
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%d ", pf[i]);
	}

	fclose(fp);
}
void save_after(int pf[],int n)
{
	int i;
	FILE *fp;
	fp = fopen("sorted.txt", "w");
	if (fp == NULL)
	{
		printf("파일 열기 오류");
		return;
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%d ", pf[i]);
	}

	fclose(fp);
}
void swap(int *x, int *y)
{
	int temp;
		temp = *x;
		*x = *y;
		*y = temp;
}
void sort(int list[],int n)
{
	int i, j, max, temp;
	for (i = 0; i < n - 1; i++) {
		max = i;
		for (j = i + 1; j < n; j++)
			if (list[j] > list[max])
				max = j;
		swap((list+i),(list+max));
	}
}

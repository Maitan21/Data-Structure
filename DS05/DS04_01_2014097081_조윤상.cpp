#include <stdio.h>

#define MAX_TERMS 1001
#define MAX_COL 1001

typedef struct term {
	int col;
	int row;
	int value;
};
term a[MAX_TERMS];
term b[MAX_TERMS];
int  sum[MAX_TERMS][MAX_TERMS];
int  sum2[MAX_TERMS][MAX_TERMS];
int  m1[MAX_TERMS][MAX_TERMS];
int  m2[MAX_TERMS][MAX_TERMS];

void open();
void create(int sum[][MAX_TERMS], int row, int col, int cnt,term a[]);
void print(int cnt, term a[],term b[]);
void fastTranspose(term a[], term b[]);
int cnt = 0, row,col;

int main() 
{
	open();
	create(sum,row,col,cnt,a);
	fastTranspose(a, b);
	print(cnt,a,b);

	return 0;
	
}
void open()
{
	int temp1, temp2, tmp1, tmp2;
	FILE *mat1 = fopen("mat1.txt", "r");
	FILE *mat2 = fopen("mat2.txt", "r");


	fscanf(mat1, "%d %d\n", &temp1, &temp2);	fscanf(mat2, "%d %d\n", &tmp1, &tmp2);
	for (int i = 0; i < temp1; i++)
		for (int j = 0; j < temp2; j++)
		{
			m1[MAX_TERMS][MAX_TERMS] = 0;
			m2[MAX_TERMS][MAX_TERMS] = 0;
		}
	if (mat1 != NULL) {
		for (int i = 0; i < temp1; i++)
			for (int j = 0; j < temp2; j++)
			{
				fscanf(mat1, "%d", &m1[i][j]);
			}
	}
	if (mat2 != NULL) {
		for (int i = 0; i < tmp1; i++)
			for (int j = 0; j < tmp2; j++)
				fscanf(mat2, "%d", &m2[i][j]);
	}
	fclose(mat1);
	fclose(mat2);
	for (int i = 0; i < tmp1; i++)
		for (int j = 0; j < tmp2; j++)
		{
			sum[i][j] = m1[i][j] + m2[i][j];
			if (sum[i][j] != 0)
				cnt++;
		}
	row = tmp1;
	col = tmp2;

}
void create(int sum[][MAX_TERMS], int row, int col,int cnt,term a[])
{
	a[0].row = row;
	a[0].col = col;
	a[0].value = cnt;
	int idx = 1;

	for(int i=0;i<row;i++)
		for (int j = 0; j < col; j++)
		{
			if (sum[i][j] != 0)
			{
				a[idx].row = i;
				a[idx].col = j;
				a[idx++].value = sum[i][j];
			}
		}
}
void print(int cnt, term a[],term b[])
{
	printf("Matrix Addition:\n");
	for (int i = 0; i < cnt + 1; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	}
	printf("Transpose Matrix:\n");
	for (int i = 0; i < cnt + 1; i++)
	{
		printf("%d %d %d\n", b[i].row, b[i].col, b[i].value);
	}
}
void fastTranspose(term a[], term b[])
{
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols; b[0].col = a[0].row;
	b[0].value = numTerms;
	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++)
		{
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col; b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

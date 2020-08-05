#include <stdio.h.>

#define MAX_DEGREE 1001 

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}polynomial;
polynomial a, b, sum;

void open();
void Add();
void print();
int main()
{

	open();
	Add();
	print();

	return 0;
}
void open()
{
	int y, tmp1, tmp2;
	float x;
	FILE *fpa = fopen("a.txt", "r");
	FILE *fpb = fopen("b.txt", "r");


	for (int i = 0; i < 1001; i++)
	{
		a.coef[i] = b.coef[i] = sum.coef[i] = 0;
	}

	fscanf(fpa, "%d", &tmp1);
	fscanf(fpb, "%d", &tmp2);

	if (fpa != NULL) {
		while ((fscanf(fpa, "%f %d", &x, &y) != EOF))
			a.coef[y] = x;
	}
	if (fpb != NULL) {
		while ((fscanf(fpb, "%f %d", &x, &y) != EOF))
			b.coef[y] = x;
	}
	fclose(fpa);
	fclose(fpb);
}
void Add()
{
	for (int i = 1000; i >= 0; i--)
	{
		if (a.coef[i] == 0 && b.coef[i] != 0)
			sum.coef[i] = b.coef[i];
		else if (b.coef[i] == 0 && a.coef[i] != 0)
			sum.coef[i] = a.coef[i];
		else
			sum.coef[i] = a.coef[i] + b.coef[i];
	}
}
void print()
{
	for (int i = 1000; i >= 0; i--)
	{
		if (sum.coef[i] != 0) {
			printf("%.f", sum.coef[i]);
			if (i == 0)
				break;
			printf("x^%d+ ", i);
		}
	}
	printf("\n");
}

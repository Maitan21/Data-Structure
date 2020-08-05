#include <stdio.h>

#define MAX_TERMS 1000                         
typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS];

int sp, fp, sq, fq, sr, fr, avail;

void padd(int sp, int fp, int sq, int fq, int *sr, int *fr);
void attach(float a, int b);
void open();
void print();
int main()
{
	open();
	padd(sp, fp, sq, fq, &sr, &fr);
	print();

	return 0;
}
void open()
{
	avail = sp = 0;
	int y, tmp1, tmp2;
	float x;
	FILE *fpa = fopen("a.txt", "r");
	FILE *fpb = fopen("b.txt", "r");

	for (int i = 0; i < 1000; i++)
	{
		terms[i].coef = 0;
		terms[i].expon = 0;
	}
	fscanf(fpa, "%d", &tmp1);	fscanf(fpb, "%d", &tmp2);

	if (fpa != NULL) {
		while ((fscanf(fpa, "%f %d", &x, &y) != EOF))
		{
			terms[avail].coef = x;
			terms[avail].expon = y;
			avail++;
			if (y == 0)

			{

				fp = avail - 1;
				sq = avail;

				break;

			}
		}
	}
	if (fpb != NULL) {
		while ((fscanf(fpb, "%f %d", &x, &y) != EOF))
		{
			terms[avail].coef = x;
			terms[avail].expon = y;
			avail++;
			if (y == 0)
			{
				fq = avail - 1;
				break;

			}
		}
	}
	fclose(fpa);
	fclose(fpb);
}
void print()
{
	for (int i = sr; i <= fr; i++)
	{
		if (terms[i].expon == 0)

		{
			printf("%.f ", terms[i].coef);
			continue;
		}
		printf("%.fX^%d", terms[i].coef, terms[i].expon);
		if (i != fr)
			printf(" + ");
	}
	printf("\n");
}
void padd(int sp, int fp, int sq, int fq, int *sr, int *fr)
{
	float temp;
	*sr = avail;

	while (sp <= fp && sq <= fq)
	{
		if (terms[sp].expon > terms[sq].expon)
		{
			attach(terms[sp].coef, terms[sp].expon);
			sp++;
		}
		else if (terms[sp].expon < terms[sq].expon)
		{
			attach(terms[sq].coef, terms[sq].expon);
			sq++;
		}
		else
		{
			temp = terms[sp].coef + terms[sq].coef;
			if (temp)
			{
				attach(temp, terms[sp].expon);
				sp++;
				sq++;
			}
		}
	}
	for (; sp <= fp; sp++)
		attach(terms[sp].coef, terms[sp].expon);
	for (; sq <= fq; sq++)
		attach(terms[sq].coef, terms[sq].expon);
	*fr = avail - 1;
}
void attach(float a, int b)
{
	terms[avail].coef = a;
	terms[avail].expon = b;
	avail++;
}
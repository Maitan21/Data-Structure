#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define BUFFER_SIZE 256


void open();
int pmatch(char *string, char *pat);
void fail(char*);
int failure[BUFFER_SIZE];
char str[BUFFER_SIZE];
char pat[BUFFER_SIZE];
char temp[BUFFER_SIZE];
int  main()
{
	open();
	int n = strlen(pat);
	strcpy(temp, pat);
	fail(pat);
	printf("Failure function\n");
	printf("j     ");

	for (int i = 0; i < n; i++)
		printf("%3d ", i);
	printf("\n");
	printf("pat   ");
	for (int i = 0; i < n; i++)
		printf("%3c ", temp[i]);
	printf("\n");
	printf("f     ");
	for (int i = 0; i < n; i++)
		printf("%3d ", failure[i]);


	printf("\n");
	printf("The pattern %s is found at position %d\n", temp, pmatch(str, temp));

	return 0;
}
void open()
{
	int n = 0, k = 0;

	FILE *fp = fopen("input.txt", "r");
	if (fp != NULL)
	{
		fscanf(fp, "%[^\n]s", str);
		fscanf(fp, "%s", pat);
	}
	fclose(fp);
}
int pmatch(char *string, char *pat)
{
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i<lens && j<lenp)
	{

		if (string[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;

	}
	return ((j == lenp) ? (i - lenp) : -1);
}
void fail(char *pat)
{
	int i, j;
	int n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++)
	{
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1]) {
			failure[j] = i + 1;
		}
		else failure[j] = -1;
	}
}
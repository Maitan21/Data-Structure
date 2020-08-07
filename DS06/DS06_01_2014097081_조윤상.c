#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define BUFFER_SIZE 256

char str[BUFFER_SIZE];
char pat[BUFFER_SIZE];

void open();
int nfind(char *string, char *pat);

int  main()
{
	open();
	printf("The pattern %s is found at position %d\n",pat, nfind(str, pat));

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
int nfind(char *string, char *pat)
{
	int i, j=0, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	for (i = 0; endmatch <= lasts; endmatch++, start++)
	{
		if (string[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp&&string[i] == pat[j]; i++, j++);
		if (j == lastp)
			return start;
	}
	return -1;
}
*/

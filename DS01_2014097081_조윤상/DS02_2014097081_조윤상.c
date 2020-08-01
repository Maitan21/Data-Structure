#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 10

int main()
{

	FILE *fp;
	int data[BUFFER_SIZE];

	int i, n = 0;

	fp = fopen("input.txt", "r");
	if (fp != NULL) {

		while ((fscanf(fp, "%d", &data[n]) != EOF)) {
			n++;
		}
	}
	fclose(fp);

	int max = data[0], min = data[0];
	for (i = 0; i < n; i++) {

		if (data[i] > max) max = data[i];
		if (data[i] < min) min = data[i];
	}
	printf("\n");
	printf("Min : %d\n", min);
	printf("Max : %d\n", max);

	return 0;
}
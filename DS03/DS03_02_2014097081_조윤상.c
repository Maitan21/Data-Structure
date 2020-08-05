#include <stdio.h>
#include <string.h>
#define MAX 400

void add(char sum[], char *pf1, char *pf2, int len1, int len2);
void Sub(char sum[], char *pf1, char *pf2, int len1, int len2);
int main()
{
	int x, y, result;
	char *ptr1, *ptr2;
	char num1[MAX + 1], num2[MAX + 1], sum[MAX + 2];

	printf("First Number : ");
	gets_s(num1);
	printf("Second Number : ");
	gets_s(num2);
	if (strcmp(num1, num2)<0)
	{
		ptr1 = num2;
		ptr2 = num1;
	}

	else
	{
		ptr1 = num1;
		ptr2 = num2;
	}
	x = strlen(ptr1); y = strlen(ptr2);

	sum[0] = '0'; sum[x + 1] = 0x00;

	add(sum, ptr1, ptr2, x, y);
	Sub(sum, ptr1, ptr2, x, y);

	return 0;
}
void add(char sum[], char *pf1, char *pf2, int len1, int len2)
{
	int cnt;
	for (cnt = 0; cnt < len2; cnt++)
		sum[len1 - cnt] = pf1[len1 - cnt - 1] + (pf2[len2 - cnt - 1] - '0');
	for (; cnt < len1; cnt++)
		sum[len1 - cnt] = pf1[len1 - cnt - 1];
	for (cnt = len1; cnt > 0; cnt--)
		if (sum[cnt] > '9') { sum[cnt - 1]++; sum[cnt] -= 10; }

	if (sum[0] == '0')
	{
		printf("Addition: %s\n", &sum[1]);
	}
	else
		printf("Addition: %s\n", &sum[0]);
}

void Sub(char sum[], char *pf1, char *pf2, int len1, int len2)
{
	int count;
	for (count = 0; count < len2; count++)
		sum[len1 - count] = pf1[len1 - count - 1] - (pf2[len2 - count - 1] - '0');
	for (; count < len1; count++) sum[len1 - count] = pf1[len1 - count - 1];

	for (count = len1; count > 0; count--)
		if (sum[count] < '0')
		{
			sum[count - 1]--; sum[count] += 10;
		}
	if (strcmp(pf1, pf2) == 0)
		printf("Subtraction : 0\n");
	for (int i = 1; i < strlen(sum) - 1; i++)
	{
		if (sum[i] == '0') continue;

		printf("Subtraction : %s\n", &sum[i]);
		break;
	}
}
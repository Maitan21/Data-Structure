#include <stdio.h>

void operate(int a,int b)
{
printf("%d + %d = %d\n", a, b, a + b);
printf("%d - %d = %d\n", a, b, a - b);
printf("%d * %d = %d\n", a, b, a*b);
printf("%d / %d = %d\n", a, b, a / b);

}
int main()
{
int i, j;
scanf_s("%d %d", &i, &j);
operate(i, j);

}
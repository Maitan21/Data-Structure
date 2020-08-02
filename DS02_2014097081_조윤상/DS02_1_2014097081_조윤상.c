/*#include <stdio.h>

int getNumber();
int distinction(int n);

int main() {

	int n , i, check;
	
	i = check = 0;
	n = getNumber();
	check = distinction(n);
	if (check == 0)
		printf("Prime");
	else
		printf("Not Prime");

	return 0;

}
int getNumber() {
	int n = 0;

	printf("Number : ");
	scanf("%d", &n);
	
	return n;
}
int distinction(int n) {
	int i, check;
	i = check = 0;
	if (n == 1) {
		check = 1;
	}
	for (i = 2; i <= n / 2; ++i) {
		if (n%i == 0) {
			check = 1;
			break;
		}
	}
	return check;
}
*/
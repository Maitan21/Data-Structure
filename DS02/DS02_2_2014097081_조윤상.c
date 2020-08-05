#include <stdio.h>

int next(int n);

int main()
{
	int n;
	printf("River : ");
	scanf("%d", &n);
		
	int river1 = 1, river3 = 3, river9 = 9;
	while ((n != river1) && (n != river3) && (n != river9)) {
		while (river1 < n) river1 = next(river1);
		while (river3 < n) river3 = next(river3);
		while (river9 < n) river9 = next(river9);

		if ((n != river1) && (n != river3) && (n != river9))
			n = next(n);
	}
	if (river1 == n) printf("First meets river 1 at %d\n", n);
	if (river3 == n) printf("First meets river 3 at %d\n", n);
	if (river9 == n) printf("First meets river 9 at %d\n", n);

	return 0;
}
 int next( int n ) 
 {
        int i = n;
        while( i > 0 ) {
            n += (i % 10);
            i /= 10;
        }
        return n;
  }


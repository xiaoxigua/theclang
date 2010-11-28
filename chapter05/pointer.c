#include <stdio.h>

int main(void)
{
	double a[] = {0.0, 3.3, 2.3};
	double *dp;
	dp = a;
	printf("a = %d\n", dp);
	printf("a + 1 = %d\n", ++dp);
}

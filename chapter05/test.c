#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char (*array)[13];
	printf("array's value = %d\n", array);
	printf("array's size = %d\n", sizeof(array));
	printf("*array's value = %d\n", *array);
	printf("*array's size = %d\n", sizeof(*array));
	printf("(*array)[0]'s address = %d\n", &(*array)[0]);
	printf("(*array)[1]'s address = %d\n", &(*array)[1]);
	printf("(*array)[0] = %d\n", (*array)[0]);
	printf("(*array)[1] = %d\n", (*array)[1]);

	return 1;
}

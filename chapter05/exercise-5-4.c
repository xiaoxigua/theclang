/**
 * Write the function strend(s, t), which returns
 * 1 if the string t occurs at the end of the 
 * string s, and zero otherwise.
 *
 */

#include <stdio.h>

int strend(char *s, char *t)
{
	int buff;
	buff = 0;
	while(*s != '\0')
	{
		while(*s != *t)
			++s;
		while(*s == *t)
		{
			buff++;
			++s;
			++t;
		}
		if(*t != '\0')
		{
			t -= buff;
			continue;
		} else
		{
			return 1;
		}
	}

	return 0;
}

int main(void)
{
	char s[] = "this is a test.";
	char t[] = "test.";

	printf("The result = %d", strend(s, t));

	return 0;
}

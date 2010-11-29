/**
 * Write a pointer version of the function strcat
 * that we showed in chapter 2: strcat(s, t) copies
 * the string t to the end of s.
 *
 */

#include <stdio.h>

void strcpy(char *s, char *t)
{
	while(*s++ = *t++)
		;
}

void strcat(char *s, char *t)
{
	while(*s != '\0')
		++s;
	strcpy(s, t);
}

int main(void)
{
	char testbuf[128];

	char *test[] = 
	{
		"",
		"1",
		"12",
		"123",
		"1234"
	};

	size_t numtests = sizeof test / sizeof test[0];
	size_t thistest;
	size_t inner;

	for(thistest = 0; thistest < numtests; thistest++)
	{
		for(inner = 0; inner < numtests; inner++)
		{
			strcpy(testbuf, test[thistest]);
			strcat(testbuf, test[inner]);

			printf("[%s] + [%s] = [%s]\n", test[thistest], test[inner], testbuf);
		}
	}

	return 0;
}


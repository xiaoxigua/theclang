#include <stdio.h>
#include <ctype.h>
#include <string.h>

void strcopy(char *s, char *t)
{
	while(*s++ = *t++)
		;
}

int strcompare(char *s, char *t)
{
	for(; *s == *t; s++, t++)
		if(*s == '\0')
			return 0;
	return *s - *t;
}

int main(void)
{
	char *s;
	char *t;
	t = "this is a string.";

	//int res = strcompare(s, t);
	//printf("compare result = %d\n", res);
	
	strcopy(s, t);
	printf("string copied: %s", s);

	return 0;
}

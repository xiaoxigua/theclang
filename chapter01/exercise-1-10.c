#include <stdio.h>

/* To copy input to output,
 * replacing each tab by \t,
 * each backspace by \b,
 * and each backslash by \\.
 * This makes tabs and backspaces visible in an unambiguous way. */

main()
{
	int c;

	while((c = getchar()) != '\n')
	{
		if(c == '\t')
		{
			putchar('\\');
			putchar('t');
		} else if(c == '\b')
		{
			putchar('\\');
			putchar('b');
		} else if(c == '\\')
		{
			putchar('\\');
			putchar('\\');
		} else
		{
			putchar(c);
		}
	}

	putchar('\n');
}

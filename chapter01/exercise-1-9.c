#include <stdio.h>

/* To copy input to output,
 * replacing each string of one or more blanks by a single blank. */

main()
{
	int n = 0;
	int c;

	while((c = getchar()) != '\n')
	{
		if(c != ' ')
		{
			if(n > 1)
			{
				putchar(' ');
				n = 0;
			}
			putchar(c);
		}
		else
		{
			++n;
		}
	}

	putchar('\n');
}

#include <stdio.h>

/* To count blanks, tabs, and newlines. */

main()
{
	int countBlanks, countTabs, countLines;
	int c;
	
	countBlanks = 0;
	countTabs = 0;
	countLines = 0;

	while((c = getchar()) != '\n')
	{
		if(c == ' ')
			++countBlanks;
		if(c == '\t')
			++countTabs;
	}

	printf("Blanks: %d\tTabs: %d\n", countBlanks, countTabs);
}

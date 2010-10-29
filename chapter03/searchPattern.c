#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);
int getlen(char s[]);
int convertstr(char s[]);
int strRightIndex(char s[], char t[]);

char pattern[] = "ould";

/* find all lines matching pattern */

main()
{
	char line[MAXLINE];
	int found = 0;
	int p;

	while(getline(line, MAXLINE))
		if( (p = strRightIndex(line, pattern)) >= 0)
		{
			printf("%s", line);
			printf("the occurent position = %d\n", p);
			found++;
		}

	return found;
}

/* getline: get line into s, return length */

int getline(char s[], int lim)
{
	int c, i;
	
	i = 0;
	while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}

/* strindex: return index of t in s, -1 if none */

int strindex(char s[], char t[])
{
	int i, j, k;

	for(i = 0; s[i] != '\0'; i++)
	{
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if(k > 0 && t[k] == '\0')
			return i;
	}

	return -1;
}

/* strRightIndex: return the position of the rightmost occurence 
 * of t in s, or -1 if there is none. */

int strRightIndex(char s[], char t[])
{
	convertstr(s);
	convertstr(t);

	return strindex(s, t);
}

/* getlen: get the lenght of string. */

int getlen(char s[])
{
	int i, len;

	for(i = 0, len = 0; s[i] != '\0' && s[i] != '\n'; i++, len++)
		;

	return len;
}

/* convertstr: convert the position of letters in str. */

int convertstr(char s[])
{
	int len = getlen(s);
	int i, j;

	if(s[len - 1] == '\0' || s[len - 1] == '\n')
		len--;

	for(i = 0, j = len - 1; i != j; i++, j--)
	{
		char tmp;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}

	return 0;
}

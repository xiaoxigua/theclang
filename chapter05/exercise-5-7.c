#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /*max #lines to be stored */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void)
{
	int nlines; /* number of input lines read */

	if((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else
	{
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000 /* max length of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	void strcpy1(char *, char *);

	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
	{
		if(nlines >= maxlines || (p = alloc(len + 1)) == NULL) /* or use malloc to request memory */
			return -1;
		else
		{
			strcpy1(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

void strcpy1(char *s, char *t)
{
	while(*s++ = *t++)
		;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	for(i = 0; i < nlines; i++)
		printf("%s", lineptr[i]);
}

int getline(char *s, int maxlen)
{
	int i;

	for(i = 0; i < maxlen - 1 && (*s = getchar()) != EOF && *s != '\n'; i++, s++)
		;
	if(*s == EOF)
		return 0;
	if(*s == '\n')
		*(++s) = '\0';
	return ++i;
	
	/*
	char *p;
	int c;
	p = s;
	while(--maxlen > 0 && (c = getchar()) != EOF && c != '\n')
		*p++ = c;
	if(c == '\n')
		*p++ = c;
	*p = '\0';
	return (int)(p - s);
	*/
}

#define ALLOCSIZE 10000
char *alloc(int n)
{
	static char allocbuf[ALLOCSIZE];
	static char *allocp = allocbuf;
	if(allocbuf + MAXLINES - allocp >= n)
	{
		allocp += n;
		return allocp - n;
	} else
		return NULL;
}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if(left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for(i = left + 1; i <= right; i++)
		if(strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

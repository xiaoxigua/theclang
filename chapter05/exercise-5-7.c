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
	int getline(char *, int);
	char line[MAXLINES];
	int len;
	len = getline(line, MAXLINES);

	//int nlines; /* number of input lines read */

	//if((nlines = readlines(lineptr, MAXLINES)) >= 0)
	//{
	//	qsort(lineptr, 0, nlines - 1);
	//	writelines(lineptr, nlines);
	//	return 0;
	//} else
	//{
	//	printf("error: input too big to sort\n");
	//	return 1;
	//}
}

#define MAXLEN 1000 /* max length of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
	{
		printf("readline len: %d\n", len);
		printf("readline string: %s\n", line);
		if(nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else
		{
			line[len - 1] = '\0'; /* delete new line */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	for(i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

int getline(char *s, int maxlen)
{
	int i;

	for(i = 0; i < maxlen; i++)
	{
		*s = getchar();
		printf("charactor[%d]: %d\n", i, *s);
		if(*s == EOF || *s == '\n')
			break;
		s++;
	}
	if(*s == EOF)
		return 0;
	printf("Got string: %s (length = %d)\n", s, i);
	return i;
}


char *alloc(int n)
{
	static char allocbuf[MAXLINES];
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

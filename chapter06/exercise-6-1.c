#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum token
{
	TOK_ID = UCHAR_MAX + 1,
	TOK_STRING,
	TOK_CHAR,
	TOK_EOF
};

enum token getword(char *word, int lim);

static int skipws(void);
static int getstelem(char **, int *, int);
static int getch(void);
static void ungetch(int);
static void putch(char **, int *, int);

int main(void)
{
	ungetch('\n');

	for(;;)
	{
		char word[64];
		enum token token;

		token = getword(word, sizeof word);

		switch(token)
		{
			case TOK_ID:
				printf("id");
				break;
			case TOK_STRING:
				printf("string");
				break;
			case TOK_CHAR:
				printf("char");
				break;
			case TOK_EOF:
				printf("eof\n");
				return 0;

			default:
				printf("other");
				word[0] = token;
				word[1] = '\0';
				break;
		}

		{
			const char *s;

			printf("\t'");
			for(s = word; *s != '\0'; s++)
				if(isprint(*s) && *s != '\'')
					putchar(*s);
				else if(*s == '\'')
					printf("\\'");
				else
					printf("\\x%02x", *s);
			printf("'\n");
		}
	}
}

enum token getword(char *word, int lim)
{
	int beg_line, c;

	for(;;)
	{
		beg_line = skipws();
		c = getch();
		if(!beg_line || c != '#')
			break;

		do
		{
			c = getch();
			if(c == EOF)
				return TOK_EOF;
		} while(c != '\n');
		ungetch('\n');
	}

	if(c == EOF)
		return TOK_EOF;
	else if(c == '_' || isalpha((unsigned char) c))
	{
		do
		{
			putch(&word, &lim, c);
			c = getch();
		} while(isalnum((unsigned char) c) || c == '_');

		ungetch(c);
		return TOK_ID;
	} else if(c == '\'' || c == '"')
	{
		int quote = c;
		word[0] = '\0';
		while(getstelem(&word, &lim, quote))
			;
		return quote == '\'' ? TOK_CHAR : TOK_STRING;
	} else
		return (unsigned char) c;
}

static int skipws(void)
{
	enum class
	{
		CLS_WS = 0,
		CLS_BEG_CMT,
		CLS_END_CMT,
		CLS_OTHER,

		CLS_IN_CMT = 4
	};

	enum class in_comment = 0;

	int beg_line = 0;

	for(;;)
	{
		int c;
		enum class class;

		c = getch();
		switch(c)
		{
			case '\n':
				if(!in_comment)
					beg_line = 1;
			case ' ': case '\f': case '\r': case '\t': case '\v':
				class  = CLS_WS;
				break;
			case '/':
				if(!in_comment)
				{
					c = getch();
					if(c == '*')
						class = CLS_BEG_CMT;
					else
					{
						ungetch(c);
						c = '/';
						class = CLS_OTHER;
					}
				} else
					class = CLS_OTHER;
				break;
			case '*':
				if(in_comment)
				{
					c = getch();
					if(c == '/')
						class = CLS_END_CMT;
					else
					{
						ungetch(c);
						class = CLS_OTHER;
					}
				} else
					class = CLS_OTHER;
				break;

			default:
				if(c == EOF)
					return 0;
				class = CLS_OTHER;
		}

		switch(class | in_comment)
		{
			case CLS_WS:
			case CLS_WS | CLS_IN_CMT:
			case CLS_OTHER | CLS_IN_CMT:
				break;
			case CLS_BEG_CMT:
				in_comment = CLS_IN_CMT;
				break;
			case CLS_OTHER:
				ungetch(c);
				return beg_line;
			case CLS_END_CMT | CLS_IN_CMT:
				in_comment = 0;
				break;
			case CLS_BEG_CMT | CLS_IN_CMT:
			case CLS_END_CMT:
			default:
				printf("can't happen\n");
				break;
		}
	}
}

static int getstelem(char **wordp, int *limp, int quote)
{
	int c;

	c = getch();
	if(c == quote || c == EOF)
		return 0;

	if(c != '\\')
	{
		putch(wordp, limp, c);
		return 1;
	}
	c = getch();
	if(c == EOF)
		return 0;

	{
		static const char escapes[] = {"''??\"\"\\\\a\ab\bf\fn\nr\rt\tv\v"};
		const char *cp = strchr(escapes, c);
		if(cp != NULL)
		{
			putch(wordp, limp, cp[1]);
			return 1;
		}
	}

	{
		unsigned char v = 0;

		if(c == 'x' || c == 'X')
			for(;;)
			{
				static const char hexits[] = "0123456789abcdef";
				const char *p;

				c = getch();
				p = strchr(hexits, tolower((unsigned char) c));
				if(p == NULL)
					break;
				v = v * 16 + (p - hexits);
			}
		else
		{
			int i;

			for(i = 0; i < 3; i++)
			{
				v = v * 8 + (c - '0');
				c = getch();
				if(c < '0' || c > '7')
					break;
			}
		}

		putch(wordp, limp, v);
		ungetch(c);
	}

	return 1;
}

#define BUFSIZE 100

char buf[BUFSIZE];

int bufp = 0;

int getch(void)
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(c == EOF)
		return;

	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

static void putch(char **wordp, int *limp, int c)
{
	if(*limp > 1)
	{
		*(*wordp)++ = c;
		(*limp)--;
	}
	if(*limp > 0)
		**wordp = '\0';
}

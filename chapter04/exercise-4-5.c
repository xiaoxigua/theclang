/**
 * Add access to library functions like
 * sin, exp, and pow.
 *
 */


#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h> /* for fmod() */
#include <string.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define IDENTIFIER '1' /* signal that a function was found */

int getop(char []);
void push(double);
double pop(void);
void showTop(void);
void duplicate(void);
void swapItems(void);
void clearStack();
void dealWithName(char []);

/* reverse Polish calculator */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case IDENTIFIER:
				dealWithName(s);
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor.\n");
				break;
			case '%':
				op2 = pop();
				if(op2)
					push(fmod(op2, pop()));
				else
					printf("error: zero divisor.\n");
				break;
			case '?':
				showTop();
				break;
			case '#':
				duplicate();
				break;
			case '~':
				swapItems();
				break;
			case '!':
				clearStack();
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}

	return 0;
}

#define MAXVAL 100 /* maximun depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop()
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

void showTop(void)
{
	if(sp > 0)
		printf("Top of stack contains: %g\n", val[sp - 1]);
	else
		printf("The stack is empty!\n");
}

void duplicate(void)
{
	double temp = pop();

	push(temp);
	push(temp);
}

void swapItems(void)
{
	double item1 = pop();
	double item2 = pop();

	push(item1);
	push(item2);
}

/* pop only returns a value if sp is greater than zero.
 * So setting the stack pointer to zero will cause pop
 * to return its error. */

void clearStack(void)
{
	sp = 0;
}

/* deal with a string/name this may be either a maths function or for
 * future exercises: a variable */
void dealWithName(char s[])
{
	double op2;

	if(0 == strcmp(s, "sin"))
		push(sin(pop()));
	else if(0 == strcmp(s, "cos"))
		push(cos(pop()));
	else if(0 == strcmp(s, "exp"))
		push(exp(pop()));
	else if(!strcmp(s, "pow"))
	{
		op2 = pop();
		push(pow(pop(), op2));
	} else
		printf("%s is not a supported function.\n", s);
}

int getch(void);
void ungetch(int);

/* getop: get next character or numberic operand */
int getop(char s[])
{
	int i = 0;
	int c, next;
	
	/* skip white space */
	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if(isalpha(c))
	{
		while(isalpha(s[i++] = c))
			c = getch();
		s[i - 1] = '\0';
		if(c != EOF)
			ungetch(c);

		return IDENTIFIER;
	}

	/* not a number but may contain an unary minus. */
	if(!isdigit(c) && c != '.' && c != '-')
		return c; /* not a number */
	if(c == '-')
	{
		next = getch();
		if(!isdigit(next) && next != '.')
		{
			return c;
		}
		c = next;
	} else
	{
		c = getch();
	}
	while(isdigit(s[++i] = c))
		c = getch();
	if(c == '.') /* collect fraction part. */
		while(isdigit(s[++i]  = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

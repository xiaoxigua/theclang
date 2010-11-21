/**
 * Write a routine ungets(s) that will push back an entire
 * string onto the input. Should ungets know about buf and
 * bufp, or should it just use ungetch?
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
/* 4-6 new for this exercise */
#define ENDSTRING '2'
#define MAX_ID_LEN 32
#define MAXVARS 30
/* end of new stuff*/

/**
 * The new additions deal with adding variables to the calculator.
 *
 * If the identifier is recognised as one of the supported mathematical
 * functions than that function from the library is called. If the
 * identifier is not one of the supported functions, even if it is a
 * valid function from math.h it is ignored.
 *
 * The main changes are:
 *
 * 1. The introduction of one more difine value (ENDSTRING) along with
 * associated cases in the switch statement.
 * 2. getop has also been changed to deal with reading in alphabetical
 * characters and coping with the '=' sign.
 * 3. A structure to hold the variable name and value.
 * 4. Another case in the switch statement to deal with the '=' sign.
 * 5. Altering the clearStack function to clear the array of structs as
 * well as the stack.
 * 6. The '<' operator now prints the last accessed variable.
 *
 * Improvements:
 * The code could be made class 0 by the use of "parallel" arrays for the
 * names and values rather than a struct but this would be messy and is
 * the situation that stucts were made for.
 * The use of a binary tree together with dynamically allocated memory
 * would allow the arbitrary limit of 30 variables to be avoided. This
 * would still be a class 1 solution.
 *
 */

/* 4-6 this is new for the program */
struct varType
{
	char name[MAX_ID_LEN];
	double val;
};

int getop(char s[]);
void push(double);
double pop(void);
void showTop(void);
void duplicate(void);
void swapItems(void);

/* 4-6 this is new for the program */
/* Changed clearStack(void) to clearStacks(struct varType var[]) */
void clearStack(struct varType var[]);
void dealWithName(char s[], struct varType var[]);
void dealWithVar(char s[], struct varType var[]);

int pos = 0;
struct varType last;
/* end of new stuff*/

/* reverse Polish calculator */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	struct varType var[MAXVARS];

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case IDENTIFIER:
				dealWithName(s, var);
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
				clearStack(var);
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			/* 4-6 this is new for the program */
			case ENDSTRING:
				break;
			case '=':
				pop();
				var[pos].val = pop();
				last.val = var[pos].val;
				push(last.val);
				break;
			case '<':
				printf("The last variable used was: %s (value == %g)\n", last.name, last.val);
				break;
			/* 4-6 end of new stuff*/
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

/* 4-6 this is new for the program */
/* Altered to clear both the main stack and that of the variables structure */
/* pop only returns a value if sp is greater than zero.
 * So setting the stack pointer to zero will cause pop
 * to return its error. */

void clearStack(struct varType var[])
{
	int i;

	/* Clear the main stack by setting the pointer to the bottom */
	sp = 0;

	/* Clear the variables by setting the initial element of each name
	 * to the terminating character. */
	for(i = 0; i < MAXVARS; ++i)
	{
		var[i].name[0] = '\0';
		var[i].val = 0.0;
	}
}

/* deal with a string/name this may be either a maths function or for
 * future exercises: a variable */
void dealWithName(char s[], struct varType var[])
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
	}
	/* Finally if it isn't one of the supported maths functions
	 * we have a variable to deal with. */
	else
	{
		dealWithVar(s, var);
	}
}

/* Our identifier is not one of the supported maths function 
 * so we have to regard it as an identifier. */
void dealWithVar(char s[], struct varType var[])
{
	int i = 0;

	while(var[i].name[0] != '\0' && i < MAXVARS - 1)
	{
		if(!strcmp(s, var[i].name))
		{
			strcpy(last.name, s);
			last.val = var[i].val;
			push(var[i].val);
			pos = i;
			return;
		}
		i++;
	}

	/* variable name not found so add it */
	strcpy(var[i].name, s);
	push(var[i].val);
	pos = i;
}
/* 4-6 end of new stuff */

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
	{
		/* 4-6 Deal with assigning a variable */
		if('=' == c && '\n' == (next = getch()))
		{
			ungetch('\0');

			return c;
		}
		if('\0' == c)
			return ENDSTRING;

		return c;
	}
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

/*
 * 4-7
 *
 * ungets() actually taks a little bit of thought. Should the
 * first character in "s" be sent to ungetch() firtst, or should
 * it be sent last? I assumed that most code calling getch()
 * would be of this form:
 *
 * char array[...];
 * int i;
 *
 * while(...){
 *	array[i++] = getch();
 * }
 *
 * In such cases, the same code might call ungets() as:
 * ungets(array);
 * and expect to repeat the while loop to get the same string
 * back. This requires that the last character be sent first
 * to ungetch() first, because getch() and ungetch() work with
 * a stack.
 *
 * To answer K&R2's additional question for this problem,
 * it's usually preferable for something like ungets() to just
 * build itself on top of ungetch(). This allows us to change
 * ungetch() and getch() in the future, perhaps to use a linked
 * list instead, without affecting ungets().
 * */

void ungets(const char *s)
{
	size_t i = strlen(s);

	while(i > 0)
		ungetch(s[--i]);
}

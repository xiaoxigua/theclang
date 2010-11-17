#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000 

double atof(char s[])
{
	double val, power;
	int i, sign, psign, enumber;

	for(i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if(s[i] == 'e' || s[i] == 'E')
		i++;
	psign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '-' || s[i] == '+')
		i++;
	for(enumber = 0; isdigit(s[i]); i++)
	{
		enumber = 10 * enumber + (s[i] - '0');
	}
	for(i = 0; i < enumber; i++)
	{
		if(psign == 1)
			power /= 10;
		else
			power *= 10;
	}

	return sign * val / power;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	for(i = 0; i < lim - 1 && ( c = getchar() ) != EOF && c != '\n'; ++i)
	{
		s[i] = c;
	}

	if(c == '\n')
	{
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

int main(void)
{
	int len;
	char line[MAXLINE];

	while((len = getline(line, MAXLINE)) > 0)
		printf("The float number = %f\n", atof(line));

	return 0;
}

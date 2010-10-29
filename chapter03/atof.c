#include <stdio.h>
#include <ctype.h>

//int isdigit(char c)
//{
//	return c >= '0' && c <= '9';
//}
//
//int isspace(char c)
//{
//	return c == ' ';
//}

double atof(char s[])
{
	double val, power;
	int i, sign;

	for(i = 0; s[i] == ' '; i++)
		;

	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		val = 10.0 * val + (s[i] - '0');
	
	for(val = 0.0; s[i] >= '0' && s[i] <= '9'; i++)
		val = 10.0 * val + (s[i] - '0');

	if(s[i] == '.')
		i++;

	for(power = 1.0; s[i] >= '0' && s[i] <= '9'; i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}

	return sign * val / power;
}


int main(void)
{
	char s[] = " 23.123";
	printf("%f", atof(s));

	return 0;
}


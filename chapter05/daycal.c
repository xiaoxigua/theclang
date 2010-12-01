#include <stdio.h>

static char days[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
int day_of_year(int year, int month, int day)
{
	int leap, i, result;
	if(year < 0)
	{
		printf("Year cannot be nagtive.\n");
		return 0;
	} else if(month < 1 || month > 12)
	{
		printf("Month cannot be little than 1 or more than 12.\n");
		return 0;
	} 
	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if(day < 1 || day > days[leap][month])
	{
		printf("Days cannot match its month.\n");
		return 0;
	}
	result = 0;
	for(i = 0; i < month; ++i)
		result += days[leap][i];
	return result;
}

int day_of_month(int year, int num, int *pmonth, int *pday)
{
	int leap, i;
	if(year < 0)
	{
		printf("Year cannot be nagtive.\n");
		return 0;
	} 
	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if(num < 1 || (leap && num > 366) || (!leap && num > 365))
	{
		printf("Days number cannot be little than 1 or greater than the whole year days.\n");
		return 0;
	}
	for(i = 0; num > days[leap][i]; ++i)
		num -= days[leap][i];
	*pmonth = i;
	*pday = num;
	return 1;
}

char *month_name(int n)
{
	static char *name[] = {
		"Unknown Month",
		"Jan.",
		"Feb.",
		"Mar.",
		"Apr.",
		"May.",
		"Jun.",
		"Jul.",
		"Aug.",
		"Sep.",
		"Oct.",
		"Nov.",
		"Dec.",
		""
	};

	return n < 1 || n > 12 ? name[0] : name[n];
}

int main(void)
{
	int year = 1900;
	int month = 3;
	int day = 1;
	int days_of_year = day_of_year(year, month, day);
	printf("%d/%d/%d is the %d-th days of the year.\n", year, month, day, days_of_year);

	int num = 116;
	int result = day_of_month(year, num, &month, &day); /* Yeah, that's what we do and don't duplicately define *month and *day. */
	if(!result)
		return -1;
	printf("The %d-th day of year %d is %s %d.\n", num, year, month_name(month), day);

	return 0;
}

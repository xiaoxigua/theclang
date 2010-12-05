#include <stdio.h>

int main(void)
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
	enum class class;

	printf("in_comment = %d\n", in_comment);
	printf("sizeof(in_comment) = %d\n", sizeof(in_comment));
	printf("class = %d\n", class);

	return 1;
}

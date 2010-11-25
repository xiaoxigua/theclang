#include <stdio.h>
/* qsort: sort v[left]...v[right] into increasing order */

int len;

void qsort(int v[], int left, int right)
{

	int i, last;
	void swap(int v[], int i, int j);
	void printarr(int v[]);

	if(left >= right)
		return; /* do nothing if array contains fewer than two elements. */

	swap(v, left, (left + right) / 2); /* move partition elem to v[0] */
	last = left;
	for(i = left + 1; i <= right; i++)
	{
		if(v[i] < v[left])
		{
			swap(v, ++last, i);
		}
		printarr(v);
	}
	swap(v, left, last); /* restore partition elelm */
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */

void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void printarr(int v[])
{
	int i = 0;
	for(i = 0; i < len; i++)
		printf("%3d ", v[i]);
	printf("\n");
}

int main(void)
{
	int i;
	int v[] = {23, 5, 10, 78, 28, 37, 67, 19, 5, 98, 32, 46};
	len = 12;
	qsort(v, 0, 11);
	for(i = 0; i < 12; i++)
		printf("%3d ", v[i]);
	printf("\n");

	return 0;
}

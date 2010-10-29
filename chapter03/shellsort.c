#include <stdio.h>

int shellsort(int v[], int n);

int main(void)
{
	int v[16] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int count = shellsort(v, 16);
	printf("Total exchanges count = %d\n", count);

	return 0;
}

int shellsort(int v[], int n)
{
	int gap, i, j, k, temp, count = 1;

	for(gap = n / 2; gap > 0; gap /= 2)
	{
		for(i = gap; i < n; i++)
		{
			for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
			{
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
				printf("%3d ", count);
				for(k = 0; k < n; k++)
				{
					if(k != n - 1)
						printf("%2d ", v[k]);
					else
						printf("%2d\n", v[k]);
				}
				count++;
			}
		}
	}

	return count;
}


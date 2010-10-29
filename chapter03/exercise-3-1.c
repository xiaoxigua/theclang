int binsearch(int x, int v[], int n)
{
	int low, mid, high;

	low = 0; 
	high = n - 1;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(x < v[mid])
			high = mid - 1;
		else if(x > v[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

int binsearch2(int x, int v[], int n)
{
	int low, high, mid;

	low = -1;
	high = n;
	while(low + 1 < high)
	{
		mid = (low + high) / 2;
		if(v[mid] < x)
			low = mid;
		else
			high = mid;
	}
	if(high == n || v[high] != x)
		return -1;
	else
		return high;
}

int binsearch3(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	while(low <= high && x != v[mid])
	{
		if(x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
		mid = (low + high) / 2;
	}
	if(x == v[mid])
		return mid;
	else
		return -1;
}

int binsearch4(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while(low < high)
	{
		mid = (low + high) / 2;
		if(x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}

	return (x == v[low]) ? low : -1;
}

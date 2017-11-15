#include <stdlib.h>

void daxpy(size_t n, double x[n], double y[n], double a);

int main()
{
	size_t n = 10000;
	double x[n];
	double y[n];
	double a = 2.0;
	
	for (size_t i=0; i<n;i++)
	{
		x[i]=2.0;
		y[i]=3.0;
	}

	for (size_t i=0; i<100000;i++)
	{
		daxpy(n, x, y, a);
	}
	
	
	return 0;
}

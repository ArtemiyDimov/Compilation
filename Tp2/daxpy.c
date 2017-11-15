#include <stdlib.h>

void daxpy(size_t n, double x[n], double y[n], double a)
{
	for (size_t i =0; i<n; i++)
	{
			y[i]=y[i]+a*x[i];
	}
}

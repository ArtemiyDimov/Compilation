#include <stdlib.h>

void daxpy(size_t n, double x[n], double y[n], double a)
{	
	x=__builtin_assume_aligned(x,64);
	y=__builtin_assume_aligned(y,64);
	
	for (size_t i =0; i<n; i++)
	{
			y[i]=y[i]+a*x[i];
	}
}

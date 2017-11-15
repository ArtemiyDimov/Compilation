#include <stdlib.h>

void def_loc(size_t m, size_t n,double dst[n][m],double src[n][m])
{
	for (size_t j=0; j<m; j++)
		for (size_t i=0; i<n;i++)
			dst[i][j]=src[i][j];
	
}

void def_loc_vect(size_t m, size_t n,double dst[n][m],double src[n][m])
{
	for (size_t i=0; i<m; i++)
		for (size_t j=0; j<n;j++)
			dst[i][j]=src[i][j];
	
}

void boucle_test(size_t n, double x[n], double y[n], double z[n])
{
	for (size_t i=0; i<n; i++)
	{
		if (x[i]<y[i]) z[i]=x[i]*y[i];
		else z[i]=x[i]+y[i];
	}
	
}

void boucle_test_vect(size_t n, double x[n], double y[n], double z[n])
{
	for (size_t i=0; i<n; i++)
	{
		z[i]=(x[i]<y[i])*x[i]*y[i]+(x[i]>=y[i])*(x[i]+y[i]) ;
	}
	
}

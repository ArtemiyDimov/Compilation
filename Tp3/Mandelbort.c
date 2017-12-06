#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <complex.h>

#define ROWS 1024
#define COLS 1024

void fill_roworder_complex(size_t rows, size_t cols, double complex t[rows][cols])
{	
	
    for ( size_t i=0 ; i<rows ; i++ )
        for ( size_t j=0 ; j<cols ; j++ )
            t[i][j] = -1.5+1.0*i/rows+(-0.5+1.0*j/cols)*I;
}

void fill_roworder(size_t rows, size_t cols, int t[rows][cols])
{	
	
    for ( size_t i=0 ; i<rows ; i++ )
        for ( size_t j=0 ; j<cols ; j++ )
            t[i][j] = 0;
}

int main(){
	double complex (*t)[COLS] = malloc(sizeof(double complex [ROWS][COLS]));
	double complex (*init)[COLS] = malloc(sizeof(double complex [ROWS][COLS]));
	
	int (*res)[COLS] = malloc(sizeof(int[ROWS][COLS]));
	
	fill_roworder_complex(ROWS,COLS,t);
	fill_roworder_complex(ROWS,COLS,init);
	fill_roworder(ROWS,COLS,res);
	
	#pragma omp parallel for schedule(dynamic)
	for ( size_t i=0 ; i<ROWS ; i++ ){
		for ( size_t j=0 ; j<COLS ; j++ ){
			for (size_t iter=0;iter<255;iter++){ //possible de mettre cabs dans les conditions
					
				t[i][j] = t[i][j]*t[i][j]+init[i][j];
				if (cabs(t[i][j])>2){
					res[i][j]=iter;
					break;
				}
			}
		}
	}
	
	/*
	printf("P2 %d %d 255",ROWS, COLS );
	for ( size_t i=0 ; i<ROWS ; i++ ){
		for ( size_t j=0 ; j<COLS ; j++ ){
			printf(" %d", res[i][j]);
		}
	}
	*/
	
		
	return 0;	
}


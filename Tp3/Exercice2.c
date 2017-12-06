#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define ROWS 1024
#define COLS 8192

void fill_roworder(size_t rows, size_t cols, float t[rows][cols])
{
    for ( size_t i=0 ; i<rows ; i++ )
        for ( size_t j=0 ; j<cols ; j++ )
            t[i][j] = 3.1415f;
}

int main(){
	float (*t)[COLS] = malloc(sizeof(float[ROWS][COLS]));
	
	fill_roworder(ROWS,COLS,t);
	
	#pragma omp parallel for
	for (size_t i=1; i<ROWS; i++){
		for (size_t j=0; j< COLS; j++){
			double x = sqrt(t[i-1][j]);
			double y = pow(x, 1.999999);
			t[i][j]=y+1.0;
		}
	 }

	
	return 0;	
}

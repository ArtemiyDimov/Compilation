
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>



#define ROWS 1024
#define COLS 1024

void fill_roworder(size_t rows, size_t cols, float t[rows][cols])
{
    for ( size_t i=0 ; i<rows ; i++ )
        for ( size_t j=0 ; j<cols ; j++ )
            t[i][j] = 3.1415f;
}

void product_opt(size_t rows, size_t cols, float t1[rows][cols], float t2[rows][cols],float res[rows][cols]){
	
	for(size_t i=0;i<rows;i++){
		for (size_t j=0; j<cols;j++){
			res[i][j]=0.0f;
		}
	}
	
	
	for(size_t i=0;i<rows;i++){
		for (size_t k=0; k<cols;k++)
		{
			for (size_t j=0; j<cols;j++){
				res[i][j]+=t1[i][k]*t2[k][j];
			}
		}		
	}
}

int main(){
	float (*t1)[COLS] = malloc(sizeof(float[ROWS][COLS]));
	float (*t2)[COLS] = malloc(sizeof(float[ROWS][COLS]));
	float (*res)[COLS] = malloc(sizeof(float[ROWS][COLS]));
	
	fill_roworder(ROWS,COLS,t1);
	fill_roworder(ROWS,COLS,t2);
	
	for (size_t i=0; i<10; i++)
	{
		product_opt(ROWS, COLS, t1, t2, res);
	}

	return 0;	
}

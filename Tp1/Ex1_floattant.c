#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define BIG 1e10f
#define SMALL 1.0f

void somme(size_t raws, float tab[raws], bool first){
	
	if (first){
	
		tab[0]=BIG;
	
		for (size_t i=1;i<raws;i++){
				tab[i]=SMALL;
		}	
	}
	else
	{
		
	
		for (size_t i=0;i<raws-1;i++){
				tab[i]=SMALL;
		}	
		
		tab[raws-1]=BIG;

	}
	
	float somme = 0.0f;
	for (size_t i=0;i<raws;i++){
		somme+=tab[i];
	}
	
	printf("%f \n",somme);
	
}

int main(){
	float *tab = malloc(sizeof(float[1024]));
	
	somme(1024,tab,true);
	somme(1024,tab,false);
	
	free(tab);

	return 0;
} 

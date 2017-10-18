
#include <stdlib.h>
#include <stdio.h>

#define N 1*1000*1000*1000L

void f(unsigned long * p)
{
    printf("%p\n",p);
    for ( size_t i = 0; i<N ; i++ )
        *p += i;
}

#define TASKS 3

int main()
{
    unsigned long data[TASKS] = { 0 };
    /* unsigned long * data =  malloc(sizeof(unsigned long [3])); */
#pragma omp parallel
    {
#pragma omp single
        {
            for ( size_t i=0 ; i<TASKS ; i++ )
#pragma omp task
                f(data+i);
        }
    }
    for ( size_t i=0 ; i<TASKS ; i++ )
        printf(" %ld",data[i]);
    printf("\n");
    return 0;
}

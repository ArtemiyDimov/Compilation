
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <sys/syscall.h>

/* NOTE: ne touchez a rien à partir d'ici */

/* Stolen at https://stackoverflow.com/questions/42088515/perf-event-open-how-to-monitoring-multiple-events */
struct read_chunk {
    uint64_t nr; struct read_value{uint64_t value; uint64_t id;} values[2];
};
int fd1; uint64_t id1; uint64_t id2;
void perf_start()
{
    struct perf_event_attr pea; memset(&pea, 0, sizeof(pea));
    pea.type = PERF_TYPE_HW_CACHE; pea.size = sizeof(struct perf_event_attr);
    pea.config = (PERF_COUNT_HW_CACHE_L1D) | (PERF_COUNT_HW_CACHE_OP_READ << 8)
        | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
    pea.disabled = 1; pea.exclude_kernel = pea.exclude_hv = 1;
    pea.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    fd1 = syscall(__NR_perf_event_open, &pea, 0, -1, -1, 0);
    ioctl(fd1, PERF_EVENT_IOC_ID, &id1);

    memset(&pea, 0, sizeof(pea));
    pea.type = PERF_TYPE_HW_CACHE; pea.size = sizeof(struct perf_event_attr);
    pea.config = (PERF_COUNT_HW_CACHE_LL) | (PERF_COUNT_HW_CACHE_OP_READ << 8)
        | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
    pea.config = PERF_COUNT_SW_PAGE_FAULTS;
    pea.disabled = 0; pea.exclude_kernel = pea.exclude_hv = 1;
    pea.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    int fd2 = syscall(__NR_perf_event_open, &pea, 0, -1, fd1 /*!*/, 0);
    ioctl(fd2, PERF_EVENT_IOC_ID, &id2);

    ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
    ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
}
void perf_stop()
{
    ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
    struct read_chunk rf; uint64_t val1; uint64_t val2;
    read(fd1, &rf, sizeof(rf));
    for ( size_t i=0 ; i<rf.nr ; i++ ) {
        if (rf.values[i].id == id1) val1 = rf.values[i].value;
        else if (rf.values[i].id == id2) val2 = rf.values[i].value;
    }
    printf("L1D misses: %"PRIu64"\nLLC misses: %"PRIu64"\n", val1, val2);
}
/* NOTE: ne touchez à rien jusqu'ici */

#define ROWS 1024
#define COLS 1024

void fill_roworder(size_t rows, size_t cols, float t[rows][cols])
{
    for ( size_t i=0 ; i<rows ; i++ )
        for ( size_t j=0 ; j<cols ; j++ )
            t[i][j] = 3.1415f;
}

void product(size_t rows, size_t cols, float t1[rows][cols], float t2[rows][cols],float res[rows][cols]){

	for(size_t i=0;i<rows;i++){
		for (size_t j=0; j<cols;j++)
		{
			
			res[i][j]=0.0f;
			
			for (size_t k=0; k<rows;k++){
				res[i][j]+=t1[i][k]*t2[k][j];
			}
		}		
	}
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
	
	perf_start();
	
	product(ROWS, COLS, t1, t2, res);
	
	perf_stop();

	return 0;	
}

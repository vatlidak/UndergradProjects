#ifndef __BUFFERS__
#define __BUFFERS__
#include <signal.h>

int BuffSize;
static volatile sig_atomic_t runflag;
int MAPPERSOVER;

typedef struct BUFFERS
{
	char *block;
	int curbyte;
	int records;
	int full;
	int dirty;
	pthread_mutex_t mylock;
	pthread_cond_t mycond1, mycond2;
}BUFFERS;

int initialize(BUFFERS *buffers, int i, int BufSize);

#endif

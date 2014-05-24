#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "buffers.h"
#define  perror2(s, e) fprintf(stderr, "%s: %s\n", s, strerror(e))

int initialize(BUFFERS *buffers, int i, int BufSize) 
{
	int err; 

	buffers[i].curbyte=0;
	buffers[i].records=0;
	buffers[i].full=0;
	
	if ( (buffers[i].block=calloc(BufSize,sizeof(char))) == NULL )			//arxikopoioume tous edamieutes//
	{
		perror("calloc");
		return -1;
	}
	if ( (err=pthread_mutex_init(&(buffers[i].mylock),NULL)) )    			//arxikopoioume ton mutex//
	{
		perror2("pthread_mutex_init",err);
		return -1;
	}
	if ( (err=pthread_cond_init(&(buffers[i].mycond1),NULL)) )			//arxikopoioume tis metavlhtes syn8hkhs//
	{
		perror2("pthread_cond_init",err);
		return -1;
	}
	if ( (err=pthread_cond_init(&(buffers[i].mycond2),NULL)) )
	{
		perror2("pthread_cond_init",err);
		return -1;
	}
	return 0;
}

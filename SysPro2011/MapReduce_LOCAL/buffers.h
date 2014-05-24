#ifndef __BUFFERS__
#define __BUFFERS__

#define BLKSIZE 1024
typedef struct BUFFERS
{
	char block[BLKSIZE];
	int curbyte;
	int pipedesc;
	int records;
}BUFFERS;

void initialize(BUFFERS *buffers, int pos, int pipedesc);
#endif

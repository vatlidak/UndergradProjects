#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "pipeLevel.h"
#define BLKSIZE 1024

int my_read (int filedes, char *block)
{
	int rval;

        if ( (rval=read (filedes, block, BLKSIZE)) < 0)					//periptwsh la8ous//
        {
            	perror ("read");
            	return -1;
        }
        else if (rval == 0)								//EOF//
          	return 0;
       	return rval;
}

int my_write(int filedes,char *block)
{
	int rval;	

	if ( (rval=write(filedes, block, BLKSIZE)) < 0)	{
		perror("write");
		return -1;
	}
	return rval;
}

void removepipes(int Mappers,int Reducers)
{
	int i,j;
	char buffer[56];

	for(i=0;i<Mappers;i++)
		for (j=0;j<Reducers;j++)
		{
			buffer[0]='\0';						
			sprintf(buffer,".pipe.%d.%d",i+1,j+1);				
			remove(buffer);
		}	
}


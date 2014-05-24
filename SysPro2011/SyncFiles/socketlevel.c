#include <stdio.h>
#include <string.h>
#include "types.h"

int myread(int sock,char* buf,int reqbytes)
{
	int readbytes;
	int rval;
	
	readbytes=0;
	bzero(buf,BUFSIZE);
	while (readbytes != reqbytes) 
	{
		rval=read(sock,buf+readbytes,reqbytes);
		if ( rval<=0 )
			return rval;
		else 
			readbytes+=rval;

	}
	printf("read:%s$\n",buf);
	return readbytes;
}


int mywrite(int sock,char* buf,int reqbytes)
{
	int writebytes;
	int rval;
	
	writebytes=0;
	
	while (writebytes != reqbytes) 
	{
		rval=write(sock,buf+writebytes,reqbytes);
		if ( rval<=0 )
			return rval;
		else 
			writebytes+=rval;
		
	}
	printf("wrote:%s$\n",buf);
	return writebytes;
	
	
}


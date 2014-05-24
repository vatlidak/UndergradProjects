#include <stdio.h>
#include "buffers.h"

void initialize(BUFFERS *buffers, int pos, int pipedesc) //synarthsh pou arxikopoiei tis domes pou xrhsimopoioume gia to buffering// 
{
	buffers[pos].curbyte=4;
	buffers[pos].records=0;
	buffers[pos].pipedesc=pipedesc;
	
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BF_Defines.h"
#include "My_Lib.h"
#include "HDF_Lib.h"
#include "FMM_Lib.h"
#include "BMM_Lib.h"

/* LRU is the function which implements LRU algorithm	
 * replacing Blocks from Memory.It finds the LRU Unpinned	
 * Block, writes it back to disk and returning it's position
 * in memory which is free to used from a new block. If all 
 * blocks are Pinned LRU fails and returns an error code.
 */		
int LRU()
{
	int 	i;
	int 	MemPosToReplace=-1;
	int	RetVal;
	int 	done;
	fileInfo_t finfo;
	unsigned long int Min;

	
	for ( i=0, done=0; i<BF_BUFFER_SIZE; i++ )					/* find Last Recently Used Block */
	{
		if ( done == 0 && Mem_info[i].PinCounter == 0 ){				
			Min=Mem_info[i].TimeStamp;		
			MemPosToReplace=i;
			done=1;
		}
		if ( Mem_info[i].PinCounter == 0  &&  Mem_info[i].TimeStamp < Min )
		{
			Min=Mem_info[i].TimeStamp;
			MemPosToReplace=i;
		}
	}
	if ( MemPosToReplace == -1 )							/* all blocks pinned */
	{
		BF_Errno=BFE_CANNOTREPLACELRU;
		return BFE_CANNOTREPLACELRU;
	}
	if ( Mem_info[MemPosToReplace].Dirty == TRUE )						
												/* block need to be written back */
	{											/* If it's dirty and file is still open*/
		bzero(finfo.filename,MAX_FILE_NAME);						
		strcpy(finfo.filename,Mem_info[MemPosToReplace].FileName);			/* initialize filename of finfo. */
		FMM_GetFileInfoByName(&finfo);							/* find rest info by name. 	*/
		if ( (RetVal=HDF_WriteBlock(Mem_info[MemPosToReplace].BlockNum+1		/* write to disk LRU block. 	*/
	              	,Mem_info[MemPosToReplace].Block, finfo.fp) ) != BFE_OK )
			return RetVal;
		return MemPosToReplace;
	}
	return MemPosToReplace;
}

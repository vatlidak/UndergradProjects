/* Buffer Management Module Level
 * provides functionality between
 * Mid Memory and DBMS.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BF_Defines.h"
#include "BMM_Lib.h"
#include "My_Lib.h"


/* Initializing structs */
void BMM_Init()
{
	int	i, j;
	
	Time=0;
	for( i=0; i<BF_BUFFER_SIZE; i++ ){
		Mem_info[i].Empty=TRUE;
		Mem_info[i].Dirty=FALSE;	
		Mem_info[i].TimeStamp=0;
		Mem_info[i].PinCounter=0;
		Mem_info[i].BlockNum=0;
		Mem_info[i].TimeStamp=(unsigned long int)0;
		bzero(Mem_info[i].FileName,MAX_FILE_NAME);
		bzero(Mem_info[i].Block,BF_BLOCK_SIZE);
		for ( j=0; j<MAXOPENFILES; j++)
			Mem_info[i].PinedBy[j]=FALSE;
	}
}


/* Reading block blockNum from file opening implyed from finfo in 
 * memory and making pointer blockBuf, pointing to the beginning of it.
 * If block is already in memory from current file opening set
 * errno but do not return error code. If there is no space in 
 * memory LRU decides which block to replace, if possible, otherwise
 * error code is returned since block cannot be loaded.
 */   
int BMM_GetBlock(fileInfo_t finfo, int blockNum, char** blockBuf)
{
	int	i;
	int 	RetVal, LRURetVal;
	
	Time++;										/* increase Time */
	for ( i=0; i<BF_BUFFER_SIZE; i++ )						
		if ( Mem_info[i].Empty == FALSE 					/* Block already in Memory */
		&& strcmp(finfo.filename,Mem_info[i].FileName) == 0  
		&& blockNum == Mem_info[i].BlockNum ){
			if ( Mem_info[i].PinedBy[finfo.fd] == TRUE ){			/* block already pinned by current file opening */
				*blockBuf=Mem_info[i].Block;				/* Inform pointer */
				BF_Errno=BFE_BLOCKFIXED ;				/* inform errno */
				return BFE_OK;						/* DO NOT return error code */
			}
			*blockBuf=Mem_info[i].Block;				/* Inform pointer */
			Mem_info[i].PinCounter++;
			Mem_info[i].PinedBy[finfo.fd]=TRUE;
			Mem_info[i].TimeStamp=Time;	
			return BFE_OK;
		}		
	for ( i=0; i< BF_BUFFER_SIZE; i++) 						/* Block not in memory */
		if ( Mem_info[i].Empty == TRUE ){					/* Available space in memory */
			if ( (RetVal=HDF_ReadBlock(blockNum+1, Mem_info[i].Block, finfo.fp)) != BFE_OK ) 
				return RetVal;
			bzero(Mem_info[i].FileName,MAX_FILE_NAME);
			strcpy(Mem_info[i].FileName,finfo.filename);
			Mem_info[i].Empty=FALSE;
			Mem_info[i].PinCounter=1;					/* PinCounter=1 since we just  brought block in memory.*/ 
			Mem_info[i].BlockNum=blockNum;					
			Mem_info[i].PinedBy[finfo.fd]=TRUE;
                        Mem_info[i].TimeStamp=Time;
 			*blockBuf= Mem_info[i].Block;
			return BFE_OK;
		}									
	if ( (LRURetVal=LRU()) < 0 ){ 							/* No Available space in memory */
		BF_Errno=RetVal;							/* LRU for Unpinned Blocks 	*/
		return RetVal;
	}												

	if ( (RetVal=HDF_ReadBlock(blockNum+1, Mem_info[LRURetVal].Block, finfo.fp))!= BFE_OK ) 
				return RetVal;
	bzero(Mem_info[LRURetVal].FileName,MAX_FILE_NAME);
	strcpy(Mem_info[LRURetVal].FileName,finfo.filename);
	Mem_info[LRURetVal].PinCounter=1;						/* PinCounter=1 since we just  brought block in memory.*/
	Mem_info[LRURetVal].BlockNum=blockNum;
	Mem_info[LRURetVal].PinedBy[finfo.fd]=TRUE;
        Mem_info[LRURetVal].TimeStamp=Time;
	*blockBuf= Mem_info[LRURetVal].Block;
	return BFE_OK;
}


/* Creating an empty block corresponing to block with blockNum 
 * from file opening implyed from finfo and making pointer blockBuf, 
 * pointing to the beginning of it. If there is no space in 
 * memory LRU decides which block to replace, if possible, 
 * otherwise error code is returned since block cannot be loaded.
 */   
int BMM_AllocBlock(fileInfo_t finfo, int blockNum,  char** blockBuf)
{
	int	i;
	int 	RetVal;
	
	Time++;
	for ( i=0; i<BF_BUFFER_SIZE; i++ )						
		if ( Mem_info[i].Empty == FALSE 					
		&& strcmp(finfo.filename,Mem_info[i].FileName) == 0  			/* Block already in Memory */
		&& blockNum == Mem_info[i].BlockNum ){					/* It shouldn't be... */
				*blockBuf=Mem_info[i].Block;				/* Inform pointer */
				BF_Errno=BFE_BLOCKFIXED ;				/* inform errno */
				return BFE_OK;						/* DO NOT return error code */
		}

	for ( i=0; i< BF_BUFFER_SIZE; i++) 						/* Block not in memory */
		if ( Mem_info[i].Empty == TRUE ){					/* Available space in memory */
			bzero(Mem_info[i].Block,BF_BLOCK_SIZE);
			bzero(Mem_info[i].FileName,MAX_FILE_NAME);
			strcpy(Mem_info[i].FileName,finfo.filename);
			Mem_info[i].Empty=FALSE;
			Mem_info[i].Dirty=TRUE;
			Mem_info[i].PinCounter=1;					/* PinCounter=1 since we just  brought block in memory.*/
			Mem_info[i].BlockNum=blockNum;
			Mem_info[i].PinedBy[finfo.fd]=TRUE;
                        Mem_info[i].TimeStamp=Time;
 			*blockBuf= Mem_info[i].Block;
			return BFE_OK;
		}									/* No Available space in memory */			
	if ( (RetVal=LRU()) < 0 ){ 							/* LRU for Unpinned Blocks 	*/
		BF_Errno=RetVal;
		return RetVal;
	}
	bzero(Mem_info[RetVal].Block,BF_BLOCK_SIZE);
	bzero(Mem_info[RetVal].FileName,MAX_FILE_NAME);
	strcpy(Mem_info[RetVal].FileName,finfo.filename);
	Mem_info[RetVal].PinCounter=1;							/* PinCounter=1 since we just  brought block in memory.*/
	Mem_info[RetVal].BlockNum=blockNum;
	Mem_info[RetVal].PinedBy[finfo.fd]=TRUE;
        Mem_info[RetVal].TimeStamp=Time;
 	Mem_info[RetVal].Dirty=TRUE;	
	*blockBuf= Mem_info[RetVal].Block;
	return BFE_OK;
}


/* Unpinning from memory block blockNum corresponding to 
 * file opening implyed from finfo. Change dirty depending
 * on third argument.Returning BFE_OK if no error occurs.
 */ 
int BMM_UnpinBlock(fileInfo_t finfo, int blockNum, BOOLEAN dirty)
{
	int 	i;
	
	for ( i=0; i< BF_BUFFER_SIZE; i++) 						/* find Block in memory */
		if ( Mem_info[i].Empty == FALSE 
		&& strcmp(finfo.filename,Mem_info[i].FileName) == 0  
		 && blockNum == Mem_info[i].BlockNum )
			if ( Mem_info[i].PinedBy[finfo.fd] == TRUE ){			/* Pined from current opening */
				if ( dirty == TRUE )
					Mem_info[i].Dirty=dirty;	
				Mem_info[i].PinedBy[finfo.fd] = FALSE;
				Mem_info[i].PinCounter--;
				return BFE_OK;
			}
			else{								/* not pinned from current opening */
				BF_Errno=BFE_BLOCKUNFIXED;
				return BFE_BLOCKUNFIXED ;
			}
	BF_Errno=BFE_BLOCKNOTINBUF;							/* Block Not in memory */
	return BFE_BLOCKNOTINBUF;		
}


/* Disposing block blockNum corresponding to file opening
 * implyed from finfo. If an error occurs return error code,
 * else return BFE_OK.
 */
int BMM_DisposeBlock(fileInfo_t finfo, int blockNum)
{
	int 	i;

	for ( i=0; i< BF_BUFFER_SIZE; i++)
	{					/* find Block in memory */
		if ( Mem_info[i].Empty == FALSE )
		{		
			if (strcmp(finfo.filename,Mem_info[i].FileName) == 0  && blockNum == Mem_info[i].BlockNum )
				if ( Mem_info[i].PinCounter == 0 ){				/* Unpined from current opening */
					Mem_info[i].Empty=TRUE;
					return BFE_OK;
				}
				else{								/*Not Unpined from current opening */
					BF_Errno=BFE_FILEHASFIXEDBLOCKS;
					return BFE_FILEHASFIXEDBLOCKS;
				}
			
		}
	}
	BF_Errno=BFE_BLOCKNOTINBUF;							/* Block Freed */
	return BFE_BLOCKNOTINBUF;				
}


/* Writting from memory to disk all dirty blocks from 
 * file opening implyed from finfo.
 */
int BMM_Flush(fileInfo_t finfo)
{
	int	i;
	int 	RetVal;
	
	for ( i=0; i< BF_BUFFER_SIZE; i++ ) 						/* find Block in memory */
		if ( Mem_info[i].Empty == FALSE  &&  strcmp(finfo.filename,Mem_info[i].FileName) == 0  ){
			if ( Mem_info[i].PinedBy[finfo.fd] == TRUE ){
				BF_Errno=BFE_FILEHASFIXEDBLOCKS;
				return BFE_FILEHASFIXEDBLOCKS;
			}
			if ( Mem_info[i].Dirty == TRUE && Mem_info[i].PinCounter == 0)
				if ( (RetVal=HDF_WriteBlock(Mem_info[i].BlockNum+1, Mem_info[i].Block, finfo.fp)) != BFE_OK)	
					return RetVal;
				
		}
	return BFE_OK;		
}


/* Clearing memory from all records related to filename */
int BMM_Clear(char* fileName)
{
	int 	i, j;
	
	for ( i=0; i< BF_BUFFER_SIZE; i++) 						/* find Block in memory */
		if ( Mem_info[i].Empty == FALSE  && strcmp(fileName,Mem_info[i].FileName) == 0 ){
			Mem_info[i].Empty=TRUE;
			Mem_info[i].Dirty=FALSE;	
			Mem_info[i].PinCounter=0;
			Mem_info[i].BlockNum=0;
			for ( j=0; j<MAXOPENFILES; j++)
				Mem_info[i].PinedBy[j]=FALSE;
		}			
	return BFE_OK;
}

/*A.M.: 1115 2005 00010 */
/*ATLIDAKIS VAGGELIS	*/
/*std05010@di.uoa.gr	*/

#include <stdio.h>
#include <string.h>
#include "FMM_Lib.h"
#include "HDF_Lib.h"
#include "BF_Defines.h"


/* Initializing structs */
void FMM_Init()
{
	int	i, j;
	
	for( i=0; i<MAXOPENFILES; i++ ){
		file_headers[i].empty=1;
		file_openings[i].empty=1;
		file_headers[i].openings=0;
		file_headers[i].dirty=0;
		for ( j=0; j<BF_BLOCK_SIZE; j++ )
			file_headers[i].header[j]=0;
	}
}


/* Opening file, with "fileName" if there is free	*/
/* space in the vector of openings, else return error.	*/
/* After opening a file searching for header of current */
/* file,via "fileName" and setting header Index		*/ 
/* to the appropriate position.If header doesn't exist  */
/* read it from file to intermediate memory. 		*/
/* If an error occured setting BF_Errno and returning   */
/* error code, else return fd.                          */ 
int FMM_Open(char* fileName)
{
	int 	i, fd, RetVal;
	
	for ( i=0; i<MAXOPENFILES; i++ )			/* search empty position for current opening */
		if ( file_openings[i].empty == 1 ){
			if ( HDF_OpenFile(fileName,&file_openings[i].fp) != BFE_OK )
				return  BFE_CANNOTOPENFILE;
			file_openings[i].empty=0;
			fd=i;
			break;
		}
	if ( i == MAXOPENFILES ){				/* no empty position found */
		BF_Errno=BFE_FTABFULL;
		return BFE_FTABFULL;
	}
	for ( i=0; i<MAXOPENFILES; i++ ) 			/* search header of current file */
		if ( file_headers[i].empty == 0  && strcmp(fileName,file_headers[i].name) == 0 ){
			file_openings[fd].header=i;
			file_headers[i].openings++;
			break;
		}
	if ( i == MAXOPENFILES ){				/* header not found. Load it to memory */
		for ( i=0; i<MAXOPENFILES; i++ ) 		
			if ( file_headers[i].empty == 1 ){
				if ( (RetVal=HDF_ReadBlock(0, file_headers[i].header, file_openings[fd].fp)) != BFE_OK )
					return RetVal;
				file_openings[fd].header=i;	/* header index for file opening */
				file_headers[i].openings++;     /* increase counter of file openings reffering to current header */
				strcpy(file_headers[i].name,fileName);
				file_headers[i].empty=0;
				break;
			}
	}
	return fd;
}


/* Closing file opening with "fileDesc".If after closing*/
/* current file opening, no file opening reffers to     */
/* respective  header write it back to disk, if changed */
/* If an error occured setting BF_Errno and returning   */
/* error code, else return BFE_OK.                      */ 
int FMM_Close(int fileDesc)
{
	int	RetVal;
	
	if ( FMM_IsValid(fileDesc) == FALSE ){			/* check validy of fileDesc */
		BF_Errno=BFE_FD;
		return BFE_FD;
	}
	file_headers[file_openings[fileDesc].header].openings--;	   	/* decrease counter of file openings reffering to current header */  
	if ( file_headers[file_openings[fileDesc].header].openings == 0  	/* if no file opening reffers to current header and header has   */
	     && file_headers[file_openings[fileDesc].header].dirty == 1 )	/* been changed, write it back to file. */			
	     if ( (RetVal=HDF_WriteBlock(0, file_headers[file_openings[fileDesc].header].header, file_openings[fileDesc].fp)) != BFE_OK )
			return RetVal;
			
	file_openings[fileDesc].empty=1; 			/* set current position as empty */
	if ( (RetVal=HDF_CloseFile(file_openings[fileDesc].fp)) != BFE_OK )	/* closing, using file pointer */ 
		return RetVal;										
	return BFE_OK;	
}


/* cheching if file, with "fileName" exists in file 	*/
/* openings.Returning true or false. 		     	*/ 
BOOLEAN FMM_IsOpen(char* fileName)
{
	int 	i;

	for ( i=0; i<MAXOPENFILES; i++ )
		if ( file_openings[i].empty == 0  &&  strcmp(file_headers[file_openings[i].header].name,fileName) == 0 )
			return TRUE;
	return FALSE;	
}


/* cheching if value of "fileDesc" reffers to a valid 	*/
/* file opening .Returning true or false.             	*/ 
BOOLEAN FMM_IsValid(int fileDesc)
{
	int 	i;
	
	if ( fileDesc<0 || fileDesc >= MAXOPENFILES )
		return FALSE;
	if ( file_openings[fileDesc].empty == 0 )
		return TRUE;
	return FALSE;
}


/* Filling struct finfo with information about file    	*/
/* opening with filename "finfo->filename". 	        */
/* If an error occured setting BF_Errno and returning   */
/* error code, else return BFE_OK.                      */ 
int FMM_GetFileInfoByName(fileInfo_t* finfo)
{
	int 	i;
	
	for ( i=0; i<MAXOPENFILES; i++ )         		/* search via filename */
		if ( file_openings[i].empty == 0  
		     &&  strcmp(file_headers[file_openings[i].header].name,finfo->filename) == 0 ){
			finfo->fp=file_openings[i].fp;
			finfo->fd=i;
			return BFE_OK;
		}
	BF_Errno=BFE_FILENOTEXISTS;
	return 	BFE_FILENOTEXISTS;
}

   
/* Filling struct finfo with information about file    	*/
/* opening with fileDesc: "finfo->fd".                 	*/
/* If an error occured setting BF_Errno and returning   */
/* error code, else return BFE_OK.                      */ 
int FMM_GetFileInfoByFD(fileInfo_t* finfo)
{
	if ( FMM_IsValid(finfo->fd) == FALSE ){			/* check validy of fd */
		BF_Errno= BFE_FD;
		return  BFE_FD ;
	}	
	finfo->fp=file_openings[finfo->fd].fp;
	bzero(finfo->filename,MAX_FILE_NAME );
	strcpy(finfo->filename,file_headers[file_openings[finfo->fd].header].name);
	return 	BFE_OK;
}


/* Checking if block, with blockNum, of file opening  	*/
/* with fileDesc reffers to a valid block.            	*/
/* returning true or false.                           	*/
BOOLEAN FMM_HEAD_IsValid(int fileDesc, int blockNum)
{
	int 	tempBitfield; 						/* We don't want to destroy the information, make a copy */ 
	
	if ( FMM_IsValid(fileDesc) == FALSE ){
		BF_Errno=BFE_FD;
		return BFE_FD;
	}
	tempBitfield=file_headers[file_openings[fileDesc].header].header[blockNum/8];	/* appropriate byte, reffered to blockNum */
//	printf("FMM_Head_IsValid::fd=%d, blockNum=%d,tempBitfield=%d ",fileDesc,blockNum,tempBitfield);
	tempBitfield = tempBitfield>>(7-blockNum%8);					/* bitwise operation */
	if ( (tempBitfield & 1 ) == 1 )
		return TRUE;
	else
		return FALSE;
}


/* Finding first valid (used) block of file opening  	*/
/* with fileDesc. Returning block number if no error 	*/
/* occurs.Otherwise setting errno and returning error	*/
/* code. */
int FMM_HEAD_GetFirstBlock(int fileDesc)	
{
	int 	i=0; 		
	int 	tempBitfield; 						/* We don't want to destroy the information in here, so make a copy */ 
	int 	bitNumber = 0; 						/* The position of the first bit that is 1 */
	int 	check=128;						/* binary value: 10000000 */

	if ( FMM_IsValid(fileDesc) == FALSE ){				/* check if fileDesc is valid */
		BF_Errno=BFE_FD;
		return BFE_FD;
	}	
	while ( file_headers[file_openings[fileDesc].header].header[i] == 0   	/* pass by bytes reffered to blocks NOT in use. */
		&&  i < BF_BLOCK_SIZE )
		i++;
	if ( i ==  BF_BLOCK_SIZE ){						/* all blocks INVALID */
		BF_Errno=BFE_EOF;
		return BFE_EOF;
	}				
	tempBitfield=file_headers[file_openings[fileDesc].header].header[i]; 	/* keep byte reffered to first valid block. */
	while ((tempBitfield & check) == 0 && bitNumber < 8 ){			/* find position of first valid bit.        */
  	 		check>>=1;						
   			bitNumber++;						
	}
	return ( 8*i + bitNumber );						/* return block number */
}


/* Finding next valid (used) block of file opening with	*/
/* fileDesc after block "prev". Returning block number	*/
/* if no error occurs.Otherwise setting errno and 	*/
/* returning error code. 			     	*/
int FMM_HEAD_GetNextBlock(int fileDesc, int prev)
{
	int 	i; 
	int 	tempBitfield; 						/* We don't want to destroy the information in here, so make a copy */ 
	int 	bitNumber; 						/* The position of the first bit that is 1 */
	int 	check=128;						/* binary value: 10000000 */

	if ( FMM_IsValid(fileDesc) == FALSE ){				/* check if fileDesc is valid */
		BF_Errno=BFE_FD;
		return BFE_FD;
	}
	if ( prev == MAX_BLOCKS-1){					/* check validy of previous blockNum */			
		BF_Errno=BFE_HEADOVERFLOW;
		return BFE_HEADOVERFLOW;
	}	
	i=(prev+1)/8;							/* find byte reffering to block after prev */
	tempBitfield=file_headers[file_openings[fileDesc].header].header[i];				
	check>>=(prev+1)%8;
	bitNumber=(prev+1)%8;
	
	while ( bitNumber < 8 ){		
		if ( (tempBitfield & check) != 0 )
			return ( 8*i + bitNumber );
 		check>>=1;					
		bitNumber++;					
	}
	i++;
	bitNumber=0;
	check=128;
	while ( file_headers[file_openings[fileDesc].header].header[i] == 0   	/* pass by bytes reffered to blocks NOT in use. */
		&&  i <  MAX_BLOCKS )
		i++;
	if ( prev == MAX_BLOCKS-1){						/* all blocks INVALID */
		BF_Errno=BFE_HEADOVERFLOW;
		return BFE_HEADOVERFLOW;
	}	
	tempBitfield=file_headers[file_openings[fileDesc].header].header[i];			
	while ( bitNumber < 8 ){				
		if ( (tempBitfield & check) != 0 )
			return ( 8*i + bitNumber );
 		check>>=1;					
		bitNumber++;					
	}
	return ( 8*i + bitNumber );
}	


/* Finding first invalid ( not used) block of file    	*/
/* opening with fileDesc.Returning block number if no 	*/
/* error occurs.Otherwise setting errno and returning 	*/
/* error code*/      
int FMM_HEAD_GetFirstEmpty(int fileDesc)	
{
	int 	i=0; 
	int 	tempBitfield; 						/* We don't want to destroy the information in here, so make a copy */ 	
	int 	bitNumber = 0; 					        /* The position of the first bit that is 1 */
	int 	check=128;						/* binary value: 10000000 */

	if ( FMM_IsValid(fileDesc) == FALSE ){				/* check if fileDesc is valid */
		BF_Errno=BFE_FD;
		return BFE_FD;
	}	
	while ( file_headers[file_openings[fileDesc].header].header[i] == 255   /* pass by bytes reffered to blocks in use. */
		&&  i < BF_BLOCK_SIZE ) 		
		i++;									
		
	if ( i == BF_BLOCK_SIZE ){						/* all blocks VALID */
		BF_Errno=BFE_EOF;
		return BFE_EOF;
	}		
	tempBitfield=file_headers[file_openings[fileDesc].header].header[i];	/* first byte cointaining bit indicating invalid block */
	while ((~tempBitfield & check) == 0 && bitNumber < 8 ){			/* find bit possition */
  	 		check>>=1;						
   			bitNumber++;						
	}
	return ( 8*i + bitNumber );						/* return block number */
}


/* Setting in bitmap of file oppening with fileDesc,   	*/
/* bit reffered to blockNum valid or in valid depending	*/
/* on value.Returning BFE_OK if no error occurs.	*/
/* Otherwise setting errno and returning error code.    */           
int FMM_HEAD_Set(int fileDesc, int blockNum, BOOLEAN value)
{
	if ( FMM_IsValid(fileDesc) == FALSE ){			/* check validy of fileDesc */
		BF_Errno=BFE_FD;
		return BFE_FD;
	}	
	else if ( blockNum >= MAX_BLOCKS){  			/* check validy of blockNum */
		BF_Errno=BFE_INVALIDBLOCK;
		return BFE_INVALIDBLOCK ;
	}
	if ( value == TRUE )					/* set appropriate bit TRUE  (1) */
		file_headers[file_openings[fileDesc].header].header[blockNum/8] |=1<<(7-blockNum%8);	/* blockNums are 0,1,2,...,7 */
	else if ( value == FALSE )				/* set appropriate bit FALSE (0) */
		file_headers[file_openings[fileDesc].header].header[blockNum/8] &=~(1<<(7-blockNum%8));	/* blockNums are 0,1,2,...,7 */
	file_headers[file_openings[fileDesc].header].dirty=1;
	return BFE_OK;
}

/*A.M.: 1115 2005 00010 */
/*ATLIDAKIS VAGGELIS	*/
/*std05010@di.uoa.gr	*/

/* FileName: BF_Lib.c
 *
 * Block File level contains functions to provide upper levels
 * an interface with the filed located at Hard Disk, using Block
 * as communication unit.
 *
 *
 * author: 	Atlidakis Vaggelis 
 * 
 * std05010@di.uoa.gr
 * A.M.:1115200500010
 * 
 */
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include 	"BF_Defines.h"
#include 	"BF_Lib.h"
#include 	"HDF_Lib.h"
#include 	"FMM_Lib.h"
#include 	"BMM_Lib.h"



/* Initialize parts of this level */
void BF_Init()
{
	FMM_Init();
	BMM_Init();
	BF_Errno=BFE_OK;
}



/* Create a file with name: fileName
 * using services provided from lower
 * Levels. Check all errors that may 
 * occur and return respective error 
 * code, else return BFE_OK.
 */
int BF_CreateFile(char *fileName)
{
	int 	RetVal;
	char 	header[BF_BLOCK_SIZE];
	FILE*	fp;
	
	if ( HDF_ExistsFile(fileName) == TRUE ){		/* check if file exists */
		BF_Errno=BFE_FILEEXISTS;
		return BFE_FILEEXISTS;
	}
	if ( (RetVal=HDF_CreateFile(fileName)) != BFE_OK )	/* if not, create it */
		return RetVal;
	bzero(header,BF_BLOCK_SIZE);
	if ( (RetVal=HDF_OpenFile(fileName,&fp)) != BFE_OK )	/* open it	*/
		return RetVal;
	if ( (RetVal=HDF_WriteBlock(0,header,fp)) != BFE_OK ) 	/* write empty header */
		return RetVal;	
	if ( (RetVal=HDF_CloseFile(fp)) != BFE_OK )		/* close it */
		return RetVal;
	return BFE_OK;
}



/* Destroy a file with name: fileName
 * using services provided from lower
 * Levels. Check all errors that may 
 * occur and return respective error 
 * code, else return BFE_OK.
 */
int BF_DestroyFile(char *fileName )
{
	int 	RetVal;
	
	if ( HDF_ExistsFile(fileName) == FALSE ){		/* check if file exists */
		BF_Errno= BFE_FILENOTEXISTS;
		return  BFE_FILENOTEXISTS;
	}
	if ( FMM_IsOpen(fileName) == TRUE ){			/* chech if it's still open */
		BF_Errno=BFE_FILEOPEN;
		return BFE_FILEOPEN;
	}
	BMM_Clear(fileName);					/* clear MidMem from information related*/
	if ( (RetVal=HDF_DestroyFile(fileName)) != BFE_OK )	/* to a file going to be destroyed 	*/
		return RetVal;
	return BFE_OK;
}



/* Close file opening with fileDesc
 * using services provided from lower
 * Levels. Check all errors that may 
 * occur and return respective error 
 * code, else return BFE_OK.
 */
int BF_CloseFile (int fileDesc )
{
	int 		RetVal;
	fileInfo_t	finfo;	
	
	finfo.fd=fileDesc;
	if ( (RetVal=FMM_GetFileInfoByFD(&finfo)) != BFE_OK ) 	/* FMM_GetFileInfoByFD checkinging validy of fd */
		return RetVal;				
	if ( (RetVal=BMM_Flush(finfo)) != BFE_OK ) 		/* Check if file have fixed blocks,	*/
		return RetVal;					/* and write to disk its dirty blocks 	*/
	if ( (RetVal=BMM_Clear(finfo.filename)) != BFE_OK ) 	/* clear mid mem from file's blocks	*/
		return RetVal;					
	if ( (RetVal=FMM_Close(fileDesc)) != BFE_OK ) 		/* close file opening */
		return RetVal;
	return BFE_OK;
}



/* Open file with name: fileName
 * using services provided from lower
 * Levels. Check all errors that may 
 * occur and return respective error 
 * code, else return BFE_OK.
 */
int BF_OpenFile (char *fileName)
{
	int 	fd;
		
	if ( HDF_ExistsFile(fileName) != TRUE ){		/* check if file exists */
		BF_Errno= BFE_FILENOTEXISTS;
		return  BFE_FILENOTEXISTS;
	}
	if ( (fd=FMM_Open(fileName)) < 0 )			/* open file */
		return fd;
	return fd;

}



/* Get First Block of file opening with fileDesc
 * using services provided from lower Levels. Set
 * blockbuf to point to the beginning of this block
 * and inform blockNum.Check all errors that may 
 * occur and return respective error code, else 
 * return BFE_OK.
 */
int BF_GetFirstBlock(int fileDesc ,int *blockNum ,char **blockBuf )
{
	int 		RetVal;
	fileInfo_t	finfo;
	
	finfo.fd=fileDesc;
	if ( (RetVal=FMM_GetFileInfoByFD(&finfo)) != BFE_OK )   	/* FMM_GetFileInfoByFD checkinging validy of fd */
		return RetVal;
	if ( (RetVal=FMM_HEAD_GetFirstBlock(fileDesc)) < 0 ) 	  	/* find in header pos of first valid block */
		return RetVal;
	*blockNum=RetVal;						/* inform blockNum */ 
	if ( (RetVal=BMM_GetBlock(finfo,*blockNum,blockBuf)) != BFE_OK )
		return RetVal;						/* Get Block */
	return BFE_OK;
}



/* Get Next Block,after block blockNum, of file 
 * opening with fileDesc using services provided 
 * from lower Levels. Set blockbuf to point to 
 * the beginning of this block and inform blockNum.
 * Check all errors that may occur and return 
 * respective error code, else return BFE_OK.
 */
int BF_GetNextBlock(int fileDesc ,int *blockNum ,char **blockBuf )
{
	int 		RetVal;
	fileInfo_t	finfo;
	
	finfo.fd=fileDesc;
	if ( (RetVal=FMM_GetFileInfoByFD(&finfo)) != BFE_OK ) 		/* FMM_GetFileInfoByFD checkinging validy of fd */
		return RetVal;
	if ( (RetVal= FMM_HEAD_GetNextBlock(fileDesc,*blockNum)) < 0 ) 	/* find in header pos of first valid block after blockNum */
		return RetVal;
	*blockNum=RetVal;						/* inform blockNum */ 
	if ( (RetVal=BMM_GetBlock(finfo,*blockNum,blockBuf)) != BFE_OK )
		return RetVal;						/* Get Block */
	return BFE_OK;		
}



/* Get a specific Block,wuth blockNum, of file 
 * opening with fileDesc using services provided 
 * from lower Levels. But firstly check validy 
 * asked block.Set blockbuf to point to the 
 * beginning of this block.Check all errors that 
 * may occur and return respective error code,
 * else return BFE_OK.
 */
int BF_GetThisBlock(int fileDesc ,int blockNum,char **blockBuf )
{
	int 		RetVal;
	fileInfo_t	finfo;
	
	finfo.fd=fileDesc;
	if ( (RetVal=FMM_GetFileInfoByFD(&finfo)) != BFE_OK ) 		/* FMM_GetFileInfoByFD checkinging validy of fd */
		return RetVal;	
	if ( (RetVal=FMM_HEAD_IsValid(fileDesc,blockNum)) != TRUE ){ 	/*  check in header  if block is valid */
		if ( RetVal == FALSE ){					
			BF_Errno=BFE_INVALIDBLOCK;			/* error: invalid block */
			return BFE_INVALIDBLOCK; 
		}
		return RetVal;						/* Other error returned from FMM level */
	}
	finfo.fd=fileDesc;
	if ( (RetVal=BMM_GetBlock(finfo,blockNum,blockBuf)) != BFE_OK )	/* Get Block */
		return RetVal;
	return BFE_OK;
}



/* Allocate in MidMem a new empty Block for file 
 * opening with fileDesc using services provided 
 * from lower Levels. Set blockbuf to point to 
 * the beginning of this block and inform blockNum.
 * Check all errors that may occur and return 
 * respective error code, else return BFE_OK.
 */
int BF_AllocBlock(int fileDesc ,int *blockNum ,char **blockBuf )
{
	int		RetVal;
	fileInfo_t 	finfo;
	
	if ( (RetVal=FMM_HEAD_GetFirstEmpty(fileDesc)) < 0 ) 			/* check header to find pos of first empty block */
		return RetVal;			
	*blockNum=RetVal;							/* inform blockNum */
	finfo.fd=fileDesc;
	if ( (RetVal=FMM_GetFileInfoByFD(&finfo)) != BFE_OK ) 			/* FMM_GetFileInfoByFD checkinging valid of fd */
		return RetVal;
	if ( (RetVal=BMM_AllocBlock(finfo,*blockNum,blockBuf)) != BFE_OK )	/* Allock block */
		return RetVal;
	if ( (RetVal=FMM_HEAD_Set(fileDesc,*blockNum,TRUE)) != BFE_OK )		/* inform header */
		return RetVal;
	return BFE_OK;
}



/* Dispose Block,with blockNum, of file 
 * opening with fileDesc using services 
 * provided from lower Levels and Inform 
 * header.But firstly check validy of given block.
 * Check all errors that may occur and return 
 * respective error code, else return BFE_OK.
 */
int BF_DisposeBlock(int fileDesc,int blockNum)
{
	int		RetVal;
	fileInfo_t 	finfo;
	
	if ( (RetVal=FMM_HEAD_IsValid(fileDesc,blockNum)) != TRUE ){ 	/*  check in header  if block is valid */
		if ( RetVal == FALSE ){					
			BF_Errno=BFE_BLOCKFREE;				/* error: invalid block, means already disposed */
			return BFE_BLOCKFREE; 
		}
		return RetVal;						/* Other error returned from FMM level */
	}
	finfo.fd=fileDesc;
	finfo.fd=fileDesc;
	if ( (RetVal=FMM_GetFileInfoByFD(&finfo)) != BFE_OK ) 		/* FMM_GetFileInfoByFD checkinging valid of fd */
		return RetVal;
	if ( (RetVal=BMM_DisposeBlock(finfo,blockNum)) != BFE_OK && RetVal!=BFE_BLOCKNOTINBUF)	/* Dispose block */
		return RetVal;
	if ( (RetVal=FMM_HEAD_Set(fileDesc,blockNum,FALSE)) != BFE_OK )				/* inform header */
		return RetVal;
	return BFE_OK;
}



/* Unpin Block,with blockNum, of file opening
 * with fileDesc using services provided from 
 * lower Levels. But firstly check validy of
 * given block.Check all errors that may occur 
 * and return respective error code,
 * else return BFE_OK.
 */
int BF_UnpinBlock(int fileDesc,int blockNum,int dirty)
{
	int		RetVal;
	fileInfo_t 	finfo;
		
	if ( (RetVal=FMM_HEAD_IsValid(fileDesc,blockNum)) != TRUE ){ 	/*  check in header  if block is valid */
		if ( RetVal == FALSE ){					
			BF_Errno=BFE_BLOCKFREE;				/* error: invalid block, means already disposed */
			return BFE_BLOCKFREE; 
		}
		return RetVal;						/* Other error returned from FMM level */
	}
	finfo.fd=fileDesc;
	if ( (RetVal=FMM_GetFileInfoByFD(&finfo)) != BFE_OK ) 		/* FMM_GetFileInfoByFD checkinging valid of fd */
		return RetVal;
	if ( (RetVal=BMM_UnpinBlock(finfo,blockNum,dirty)) != BFE_OK )	/* unpinn block */
		return RetVal;
	return BFE_OK;
}



/*
 * print errString and respective error
 * depending on the value of BF_Errno.
 *
 */
void BF_PrintError(char* errString)
{
  switch (BF_Errno)              
  {
    case BFE_NOMEM:
         printf ("%s\n", errString);
         printf ("Unable to alloc memory.\n");
         break;
    case BFE_CANNOTOPENFILE:
         printf ("%s\n", errString);
         printf ("Unable to open file.\n");
         break;
    case BFE_CANNOTCLOSEFILE:
         printf ("%s\n", errString);
         printf ("Unable to close file.\n");
         break;
    case BFE_CANNOTCREATEFILE:
         printf ("%s\n", errString);
         printf ("Unable to create file.\n");
         break;
    case BFE_INCOMPLETEREAD:
         printf ("%s\n", errString);
         printf ("Incomplete block read.\n");
         break;
    case BFE_INCOMPLETEWRITE:
         printf ("%s\n", errString);
         printf ("Incomplete block write.\n");
         break;
    case BFE_FILEEXISTS:
         printf ("%s\n", errString);
         printf ("File already exists.\n");
         break;
    case BFE_NOBUF:
         printf ("%s\n", errString);
         printf ("No space in intermediate memory.\n");
         break;
    case BFE_FILEOPEN:
         printf ("%s\n", errString);
         printf ("File already open.\n");
         break;
    case BFE_FD:
         printf ("%s\n", errString);
         printf ("Invalid fd.\n");
         break;
    case BFE_FILENOTEXISTS:
         printf ("%s\n", errString);
         printf ("File does not exists.\n");
         break;
    case BFE_FTABFULL:
         printf ("%s\n", errString);
         printf ("Table of open files full.\n");
         break;
    case BFE_HEADOVERFLOW:
         printf ("%s\n", errString);
         printf ("Invalid block Number given as \"previous\" argument.\n");
         break;
    case BFE_BLOCKFIXED:
         printf ("%s\n", errString);
         printf ("Block already fixed.\n");
         break;
    case BFE_BLOCKUNFIXED :
         printf ("%s\n", errString);
         printf ("Block already unfixed.\n");
         break;
    case BFE_EOF:
         printf ("%s\n", errString);
         printf ("No valid block in file.\n");
         break;
    case BFE_FILEHASFIXEDBLOCKS:
         printf ("%s\n", errString);
         printf ("File has fixed blocks.\n");
         break;
    case BFE_BLOCKFREE:
         printf ("%s\n", errString);
         printf ("Block already disposed.\n");
         break;    
    case BFE_BLOCKINBUF:
         printf ("%s\n", errString);
         printf ("Block already in intermediate memory.\n");
         break;
    case BFE_BLOCKNOTINBUF:
         printf ("%s\n", errString);
         printf ("Block not in intermediate memory.\n");
         break;
    case BFE_INVALIDBLOCK:
         printf ("%s\n", errString);
         printf ("Invalid block number.\n");
         break;
    case  BFE_CANNOTDESTROYFILE:
    	 printf ("%s\n", errString);
         printf ("Unable to destroy file.\n");
         break;
    case BFE_FSEEK:
         printf ("%s\n", errString);
         printf ("Inproper fseek.\n");
         break;
    case BFE_CANNOTREPLACELRU:
         printf ("%s\n", errString);
         printf ("Last Recently Used block cannot replaced.\n");
         break;
    
   }
}

/* Hard Disk Functionality Level.  */
/* In this level we have functions */ 
/* to achive communication with    */
/* hard disk. */
#include <stdio.h>
#include <string.h>
#include "HDF_Lib.h"
#include "BF_Defines.h"


/* opening a binary file, with "fileName"    */
/* and return filepointer to "*file".        */
/* If an error occured setting BF_Errno      */
/* and return error code, else return BFE_OK */ 
int HDF_OpenFile(char* fileName, FILE** file)           
{
	if (  (*file=fopen(fileName,"rb+")) == NULL  ){
		BF_Errno=BFE_CANNOTOPENFILE;
		return BFE_CANNOTOPENFILE;
	}
	return BFE_OK;
}


/* closing a file, with filepointer "file*"  */
/* If an error occured setting BF_Errno      */
/* and return error code, else return BFE_OK */ 
int HDF_CloseFile(FILE* file)
{
	if (  fclose(file)  ){
		BF_Errno=BFE_CANNOTCLOSEFILE;
		return BFE_CANNOTCLOSEFILE;
	}
	return BFE_OK;

}


/* creating a binary file, with "fileName",  */
/* if it doesn't exists, otherwise truncate  */
/* it. After creating file  close it. 	     */ 
/* If an error occured setting BF_Errno      */
/* and return error code, else return BFE_OK */ 
int HDF_CreateFile(char* fileName)
{
	FILE *fp;
	
	if (  (fp=fopen(fileName,"wb+")) == NULL  ){
		BF_Errno=BFE_CANNOTCREATEFILE;
		return BFE_CANNOTCREATEFILE;
	}
	if (  fclose(fp)  ){
		BF_Errno=BFE_CANNOTCLOSEFILE;
		return BFE_CANNOTCLOSEFILE;
	}
	return BFE_OK;
}


/* Deleting file, with "filename". */
/* If an error occured setting BF_Errno      */
/* and return error code, else return BFE_OK */ 
int HDF_DestroyFile(char* fileName)
{
	if ( remove(fileName) ){
		BF_Errno=BFE_CANNOTDESTROYFILE;
		return  BFE_CANNOTDESTROYFILE;
	}
	return BFE_OK;
}


/* cheching if file, with fileName exists.*/
/* Returning TRUE or FALSE depending on   */
/* wheather the file exists or not 	  */
BOOLEAN HDF_ExistsFile(char* fileName)
{
	FILE 	*fp;
	
	if (  (fp=fopen(fileName,"rb+")) == NULL  )
		return FALSE;
	else
		fclose(fp);
	return TRUE;
}


/* Reading   block with blockIndex,    */
/* from file, with filepointer *file   */
/* and setting pointer blockBuf to the */
/* first character read.               */
/* If an error occured setting BF_Errno      */
/* and return error code, else return BFE_OK */ 
int HDF_ReadBlock(int blockIndex, char* blockBuf, FILE* file)
{
	int 	n;
	
	if ( fseek(file,blockIndex*BF_BLOCK_SIZE,SEEK_SET) == -1 ){
		BF_Errno=BFE_FSEEK;
		return BFE_FSEEK;
	}	
	if ( ( n=fread(blockBuf,sizeof(char),BF_BLOCK_SIZE,file) ) != BF_BLOCK_SIZE ){
		 BF_Errno=BFE_INCOMPLETEREAD;
		 return  BFE_INCOMPLETEREAD;
	}
	return BFE_OK;
}


/* Writting block, with block Index and  */
/* a pointer blockBuf to the first char, */
/* to file, with file pointer "*file".   */
/* If an error occured setting BF_Errno      */
/* and return error code, else return BFE_OK */ 
int HDF_WriteBlock(int blockIndex, char* blockBuf, FILE* file)
{	
	if ( fseek(file,blockIndex*BF_BLOCK_SIZE,SEEK_SET) == -1 ){
		BF_Errno=BFE_FSEEK;
		return BFE_FSEEK;
	}	
	if ( fwrite(blockBuf,sizeof(char),BF_BLOCK_SIZE,file)  != BF_BLOCK_SIZE ){
		 BF_Errno=BFE_INCOMPLETEWRITE ;
		 return  BFE_INCOMPLETEWRITE ;
	}
	return BFE_OK;
}

/*A.M.: 1115 2005 00010 */
/*ATLIDAKIS VAGGELIS	*/
/*std05010@di.uoa.gr	*/

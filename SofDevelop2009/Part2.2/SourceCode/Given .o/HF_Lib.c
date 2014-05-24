/*
 * Heap File Level.
 *
 * Heap File Level provides upper levels
 * a programming interface to handle such 
 * files.
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogiannopoulos Aris, Kuriazof Xristina
 * AM: 	    1115200500010, 1115200500004, 1115200600276
 * 
 *
 * Date: 6 December, 2009.
 */
#include <stdio.h>

#include "BF_Defines.h"
#include "BF_Lib.h"

#include "HF_Defines.h"
#include "HF_Lib.h"
#include "SMM_Lib.h"

/*
 * This is a void funtion initiazing structs of 
 * current level and inferriors.
 */
void HF_Init(void){
	HF_errno = HFE_OK;
	BF_Init();
	SMM_Init();
}


/*
 * This is a funtion creating a Heap File and 
 * writting the respective heap level header.
 * Uppon succesful execution HFE_OK is returned,
 * otherwise HFE_ernno is set and error code is
 * returned.
 */
int HF_CreateFile(char *fileName)
{
	int fd, blocknum;
	char* block;
	if(BF_CreateFile(fileName) != BFE_OK)
		return  (HF_errno = BF_Errno);
	if((fd=BF_OpenFile(fileName)) < 0)
		return  (HF_errno = BF_Errno);
	if(BF_AllocBlock(fd, &blocknum, &block) != BFE_OK || blocknum != 0)
		return  (HF_errno = BF_Errno);
	if(BF_UnpinBlock(fd, 0, TRUE) != BFE_OK)
		return (HF_errno = BF_Errno);
	if(BF_CloseFile(fd) != BFE_OK)
		return (HF_errno = BF_Errno);
	return (HF_errno = HFE_OK);
}


/*
 * This is a funtion Destroying a Heap File.
 * Uppon succesful execution HFE_OK is returned,
 * otherwise HFE_ernno is set and error code is
 * returned.
 */
int HF_DestroyFile(char *fileName)
{
	int rval;
        if((rval=BF_DestroyFile(fileName)) != BFE_OK)
        	return (HF_errno = BF_Errno);
        return (HF_errno = HFE_OK);

}


/*
 * This is a funtion Opening a Heap File.
 * Uppon succesful execution File Descripitor is 
 * returned, otherwise HFE_ernno is set and error 
 * code is returned.
 */
int HF_OpenFile(char *fileName)
{
	int fd;
	if((fd=BF_OpenFile(fileName)) < 0)
		return (HF_errno = BF_Errno);
	return fd;
}


/*
 * This is a funtion Closinging a Heap File.
 * Uppon succesful execution HFE_OK is returned,
 * otherwise HFE_ernno is set and error  code is 
 * returned.
 */
int HF_CloseFile(int fileDesc)
{
	int rval;

	if(SMM_hasOpenScans(fileDesc)==FALSE)
	{
		if( (rval=BF_CloseFile(fileDesc)) < 0)
			return (HF_errno = rval);
	}
	else return (HF_errno = HFE_HASOPENSCANS);
	return (HF_errno = HFE_OK);
}


/*
 * This is a function inserting a record into Heap
 * File with RMM level function calls. Uppon succesful 
 * execution rval is returned, otherwise HFE_ernno 
 * is set and error  code is returned. 
 */
int HF_InsertRec(int fileDesc, char *record, int recordSize)
{
	int rval;
	if((rval = RMM_InsertRec(fileDesc, record, recordSize)) != HFE_OK)
		HF_errno = rval;
	return rval;
}


/*
 * This is a function deleting a record into Heap
 * File with RMM level function calls. Uppon succesful 
 * execution rval is returned, otherwise HFE_ernno 
 * is set and error  code is returned. 
 */
int HF_DeleteRec(int fileDesc, int recId, int recordSize)
{
	int rval;
	if((rval = RMM_DeleteRec(fileDesc, recId, recordSize)) != HFE_OK)
		HF_errno = rval;
	return rval;
}


/*
 * This is a function getting first valid record from Heap
 * File with RMM level function calls. Uppon succesful 
 * execution recId is returned and "record" points to record.
 * otherwise HFE_ernno  is set and error  code is returned. 
 */
int HF_GetFirstRec(int fileDesc, char *record, int recordSize)
{
	int recId;
	if((recId = RMM_GetFirstRec(fileDesc, record, recordSize)) < 0)
		HF_errno = recId;
	return recId;
}


/*
 * This is a function getting next valid record (after recId)
 * from Heap File with RMM level function calls. Uppon succesful 
 * execution recId is returned and "record" points to record.
 * otherwise HFE_ernno  is set and error  code is returned. 
 */
int HF_GetNextRec(int fileDesc, int recId, char *record, int recordSize)
{
	int recid;
	if((recid = RMM_GetNextRec(fileDesc, recId, record, recordSize)) < 0)
		return (HF_errno = recid);
	return recid;
}


/*
 * This is a function getting next valid record (after recId)
 * from Heap File with RMM level function calls. Uppon succesful 
 * execution recId is returned and "record" points to record.
 * otherwise HFE_ernno  is set and error  code is returned. 
 */
int HF_GetThisRec(int fileDesc, int recId, char *record, int recordSize)
{
	int rval;
	if((rval = RMM_GetThisRec(fileDesc ,recId, record, recordSize)) != HFE_OK)
		return (HF_errno = rval);
	return HFE_OK;
}


/*
 * This is a function Opening a file scaning for Heap File with 
 * SMM level function calls. Uppon succesful  execution ScanDesc 
 * is returned otherwise HFE_ernno  is set and error  code is returned. 
 */
int HF_OpenFileScan(int fileDesc, int recordSize, char attrType, int attrLength, int attrOffset, int op, char *value){
	int scanId;
	if((scanId = SMM_OpenFileScan(fileDesc, recordSize, attrType, attrLength, attrOffset, op, value)) < 0)
		return (HF_errno = scanId);
	return scanId;
}


/*
 * This is a function finding next record corresponding to Scan
 * with scanDesc with SMM level function calls. Uppon succesful
 * execution ScanDesc is returned otherwise HFE_ernno is set and 
 * error code is returned. 
 */
int HF_FindNextRec(int scanDesc, char *record){
	int recId;
	if((recId = SMM_FindNextRec(scanDesc, record)) < 0)
		return (HF_errno = recId);
	return recId;
}


/* 
 * This is a function closing an open file scan with scanDesc. 
 * Uppon succesful execution HFE_OK is returned otherwise HFE_ernno
 * is set and error code is returned.
 */ 
int HF_CloseFileScan(int scanDesc){
	int rval;
	if((rval = SMM_CloseFileScan(scanDesc)) != HFE_OK)
		return (HF_errno = rval);
	return HFE_OK;
}

/* Print respective message for HFE_errno code */
void HF_PrintError(char *errString)
{
	printf("%s\n", errString);
	if(HF_errno >= -24)			//error in BF lenel
		 BF_PrintError(errString);
	else
	{
		switch(HF_errno)
		{
			case HFE_OK:
				printf("No errors\n");
				break;	
			case HFE_EOF: 
				printf("End of file \n");
				break;	
			case HFE_INVALIDREC:
				printf("Invalid record \n");
				break;	
			case HFE_STFULL:
				printf("Scan table full\n");
				break;	
			case HFE_INVALIDOP:
				printf("Invalid scan operator\n");
				break;			
			case HFE_RECEMPTY:
				printf("Record is empty\n");
				break;	
			case HFE_ALLBLOCKSFULL:
				printf("Unable to aloc block\n");
				break;	
			case HFE_NOMEM:
				printf("Unable to aloc memory\n");
				break;	
			case HFE_INVALIDSCANDESC:
				printf("Invalid ScanDesc\n");
				break;	
			case HFE_HASOPENSCANS:
				printf("There are open scans\n");
				break;	
		}
	}
}























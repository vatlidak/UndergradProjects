/*
 * Scan Management Level.
 *
 * There are functions providing Heap File
 * the ability to search records satisfing 
 * varing conditions.
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogiannopoulos Aris, Kuriazof Xristina
 * AM: 	    1115200500010, 1115200500004, 1115200600276
 * 
 *
 * Date: 6 December, 2009.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF_Defines.h"
#include "BF_Lib.h"

#include "HF_Defines.h"
#include "RMM_Lib.h"
#include "SMM_Lib.h"




/*
 * This is a void function to initialize
 * structs needed for SMM level.
 */
void SMM_Init()
{
	int	i;
	
	for ( i=0;i<MAXSCANS;i++ )
		scan_info[i].empty=TRUE;
}



/*
 * This is a function Opening a File Scan.
 * If no error occours the scanDesc of current 
 * scan is returned, otwerwise error code is 
 * returned an HF_errno is set.
 */
int SMM_OpenFileScan(int fileDesc, int recordSize, char attrType, int attrLength, int attrOffset, int op, char *value )
{
	int	i;
	int	scanDesc;
	int 	recId;
	char	*record;
	
	scanDesc=-1;
	for ( i=0;i<MAXSCANS;i++ )							/* search for an empty position in the scans' table */
		if ( scan_info[i].empty==TRUE ){
			scan_info[i].empty=FALSE;
			scanDesc=i;
			break;
		}
	if ( scanDesc == -1 )
		return (HF_errno = HFE_STFULL);	
	
	scan_info[scanDesc].recordSize=recordSize;
	scan_info[scanDesc].lastRecId=-1;
	scan_info[scanDesc].fileDesc=fileDesc;
	scan_info[scanDesc].attrType=attrType;
	scan_info[scanDesc].attrLength=attrLength;
	scan_info[scanDesc].attrOffset=attrOffset;
	scan_info[scanDesc].op=op;
	
	if ( value == NULL )
		scan_info[scanDesc].value=value;
	else
	{	
		if ( (scan_info[scanDesc].value=calloc(attrLength,sizeof(char))) == NULL )
			return (HF_errno = HFE_NOMEM);
		if ( attrType == 'i' )
			*(int*)scan_info[scanDesc].value = *(int*)value;
		else if ( attrType == 'f' )
			*(float*)scan_info[scanDesc].value = *(float*)value;	
		else
			strcpy(scan_info[scanDesc].value,value);
	}	
	return scanDesc;
}


/*
 * This is a function finding next record satisfy
 * the condition described in Scaning with scanDesc.
 * If no error occours recId is returned, otwerwise 
 * error code is returned an HF_errno is set.
 */
int SMM_FindNextRec(int scanDesc, char *record )
{
	int	i;
	int 	recId;
	int 	retVal;
	

	if ( scan_info[scanDesc].empty==TRUE )
		return (HF_errno=HFE_INVALIDSCANDESC);	
		
	if ( scan_info[scanDesc].value == NULL ){
		if ( (retVal=RMM_GetNextRec(scan_info[scanDesc].fileDesc,scan_info[scanDesc].lastRecId,record,scan_info[scanDesc].recordSize)) < 0 )
			return (HF_errno=retVal);
		return (scan_info[scanDesc].lastRecId=retVal);	
	}
	else
	{
		while ( (scan_info[scanDesc].lastRecId=RMM_GetNextRec(scan_info[scanDesc].fileDesc
									,scan_info[scanDesc].lastRecId,record,scan_info[scanDesc].recordSize))  >= 0)
		{
			switch ( scan_info[scanDesc].op )              
			{	
				case 1:									/* equal */
				   	if ( scan_info[scanDesc].attrType == 'i' )
				   	{
					      	if ( *(int*)(record+scan_info[scanDesc].attrOffset) == *(int*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else if (scan_info[scanDesc].attrType == 'f' )
				   	{
					      	if ( *(float*)(record+scan_info[scanDesc].attrOffset) == *(float*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else 
					{
					      	if ( strcmp(record+scan_info[scanDesc].attrOffset,scan_info[scanDesc].value) == 0 )
							return scan_info[scanDesc].lastRecId;						
					}
					break;	
				case 2:									/* less than */
				   	if ( scan_info[scanDesc].attrType == 'i' )
				   	{
					      	if ( *(int*)(record+scan_info[scanDesc].attrOffset) < *(int*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else if ( scan_info[scanDesc].attrType == 'f' )
				   	{
					      	if ( *(float*)(record+scan_info[scanDesc].attrOffset) < *(float*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else 
					{
					      	if ( strcmp(record+scan_info[scanDesc].attrOffset,scan_info[scanDesc].value) < 0 )
							return scan_info[scanDesc].lastRecId;						
					}
					break;									/* greater than */
				case 3:
				   	if ( scan_info[scanDesc].attrType == 'i' )
				   	{
					      	if ( *(int*)(record+scan_info[scanDesc].attrOffset) > *(int*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else if ( scan_info[scanDesc].attrType == 'f' )
				   	{
					      	if ( *(float*)(record+scan_info[scanDesc].attrOffset) > *(float*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else 
					{
					      	if ( strcmp(record+scan_info[scanDesc].attrOffset,scan_info[scanDesc].value) > 0 )
							return scan_info[scanDesc].lastRecId;						
					}
					break;	
				case 4:										/* less than or equal */
				   	if ( scan_info[scanDesc].attrType == 'i' )
				   	{
					      	if ( *(int*)(record+scan_info[scanDesc].attrOffset) <= *(int*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else if (  scan_info[scanDesc].attrType == 'f' )
				   	{
					      	if ( *(float*)(record+scan_info[scanDesc].attrOffset) <= *(float*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else 
					{
					      	if ( strcmp(record+scan_info[scanDesc].attrOffset,scan_info[scanDesc].value) <= 0 )
							return scan_info[scanDesc].lastRecId;						
					}
					break;	
				case 5:										/* greater than or equal */
				   	if (  scan_info[scanDesc].attrType == 'i' )
				   	{
					      	if ( *(int*)(record+scan_info[scanDesc].attrOffset) >= *(int*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else if (  scan_info[scanDesc].attrType == 'f' )
				   	{
					      	if ( *(float*)(record+scan_info[scanDesc].attrOffset) >= *(float*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else 
					{
					      	if ( strcmp(record+scan_info[scanDesc].attrOffset,scan_info[scanDesc].value) >= 0 )
							return scan_info[scanDesc].lastRecId;						
					}
					break;	
				case 6:										/* not equal */
				   	if (  scan_info[scanDesc].attrType == 'i' )
				   	{
					      	if ( *(int*)(record+scan_info[scanDesc].attrOffset) != *(int*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else if (  scan_info[scanDesc].attrType == 'f' )
				   	{
					      	if ( *(float*)(record+scan_info[scanDesc].attrOffset) != *(float*)scan_info[scanDesc].value )
							return scan_info[scanDesc].lastRecId;						
					}
					else 
					{
					      	if ( strcmp(record+scan_info[scanDesc].attrOffset,scan_info[scanDesc].value) != 0 )
							return scan_info[scanDesc].lastRecId;						
					}
					break;	
				    
			}/* switch */
		}/* while */	
	}/* else */	
	return (HF_errno=scan_info[scanDesc].lastRecId);	
}


/*
 * This is a function Closinging a File Scan.
 * If no error occours HFE_OK is returned,
 * othrwise error code is returned and
 * HF_errno is set.
 */
int SMM_CloseFileScan( int scanDesc)
{
	if ( scan_info[scanDesc].empty == TRUE )
		return (HF_errno= HFE_INVALIDSCANDESC);
	scan_info[scanDesc].empty=TRUE;
	if ( scan_info[scanDesc].value != NULL )
		free(scan_info[scanDesc].value);
	return (HF_errno = HFE_OK);
}


/*
 * This is a function returning TRUE or FALSE
 * depending on wheather file with fileDesc has
 * open Scans.
 */
BOOLEAN SMM_hasOpenScans(int fileDesc)
{
	int 	i;
	
	for ( i=0;i<MAXSCANS;i++ )
		if ( (scan_info[i].fileDesc == fileDesc) && (scan_info[i].empty == FALSE)  )
			return TRUE;
	return FALSE;

}

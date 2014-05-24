/* 
 * File:   RMM_Lib.h
 * Author: marialena
 *
 * Created on November 25, 2009, 6:56 PM
 */

#ifndef _RMM_LIB_H
#define	_RMM_LIB_H

int RMM_InsertRec(int fileDesc, char* record, int recordSize);
int RMM_DeleteRec(int fileDesc, int recId, int recordSize);
int RMM_GetFirstRec(int fileDesc, char* record, int recordSize);
int RMM_GetNextRec(int fileDesc, int recId, char* record, int recordSize);
int RMM_GetThisRec(int fileDesc, int recId, char* record, int recordSize);

#endif	/* _RMM_LIB_H */


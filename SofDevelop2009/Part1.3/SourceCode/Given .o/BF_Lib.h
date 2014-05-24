/*
 * File:   BF_Lib.h
 * Author: Herald
 *
 * Created on March 6, 2008, 1:55 AM
 */

#include "BF_Defines.h"

#ifndef _BF_LIB_H
#define	_BF_LIB_H

void BF_Init(void);
int BF_CreateFile(char* fileName);
int BF_DestroyFile(char* fileName);
int BF_OpenFile(char *fileName);
int BF_CloseFile(int fileDesc);
int BF_GetFirstBlock(int fileDesc, int *blockNum, char **blockBuf);
int BF_GetNextBlock(int fileDesc, int *blockNum, char **blockBuf);
int BF_GetThisBlock(int fileDesc, int blockNum, char **blockBuf);
int BF_AllocBlock(int fileDesc, int *blockNum, char **blockBuf);
int BF_DisposeBlock(int fileDesc, int blockNum);
int BF_UnpinBlock(int fileDesc, int blockNum, int dirty);

void BF_PrintError(char *errString);

#endif	/* _BF_LIB_H */

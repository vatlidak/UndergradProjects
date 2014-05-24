/*
 *  LH.h
 *  
 *
 *  Created by Natasa Sevastidou on 5/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "record.h"

int MaxRecs;

typedef struct{
	int FileKind;
	char attrType;
	char attrName[25];
	int attrLength;
	int buckets;
	int split;
	int level;
	float loadThrs;
	int total_rec;
	int maxrecs;
}LHheader;

typedef struct {
	int fileDesc; 
	char attrName[8]; 
	char attrType;
	int attrLength;
	int buckets;
	float loadThrs;
	int total_rec;
	int level;
	int split;
	
} LH_info;

int LH_CreateIndex(char *fileName,	char* attrName,char attrType, int attrLength, int buckets, float loadThrs);

LH_info* LH_OpenIndex(char *filename);
int LH_CloseIndex(LH_info* header_info);
int LH_InsertEntry (LH_info* header_info,Record record );
void LH_GetAllEntries(LH_info header_info,      void* value);
int HashStatistics( char* filename /* όνομα του αρχείου που ενδιαφέρει */ );

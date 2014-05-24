#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF_Defines.h"
#include "HDF_Lib.h"
#include "FMM_Lib.h"

#define fileName1 "ATHLETES"
#define fileName2 "EVENTS"

char *printBoolean(BOOLEAN boolean) {
	char *value = malloc(sizeof(char) * 10);
	if (boolean == TRUE)
		strcpy(value, "VALID");
	else
		strcpy(value, "INVALID");

	return value;
}

void printFileInfo(fileInfo_t *finfo) {
	printf("Filename: %s\n", finfo->filename);
	printf("File pointer: %d\n", finfo->fp);
	printf("File descriptor: %d\n\n", finfo->fd);
}

int main(void) {
	int rvalue;
	FILE *fp1, *fp2;
	char *buffer;
	int fd11, fd12, fd13;
	int fd21, fd22;
	int blockNumInFile11;
	int blockNumInHeader11, blockNumInHeader12;
	int blockNumInHeader21;
	int firstEmpty;
	fileInfo_t finfo;

	// ---------------------- Dimiourgia twn fileName1 kai fileName2 ----------------------

	// ---------------------- Dimiourgia tou fileName1 ----------------------

	printf("\n--------------\n");
	printf("CREATING FILES\n");
	printf("--------------\n\n");

	// Elegxos an yparxei to fileName1
	printf("Checking if file %s exists...\n\n", fileName1);
	if (HDF_ExistsFile(fileName1) == TRUE) {
		printf("Checkpoint 1:\n");
		printf("HDF_ExistsFile returned TRUE!\n\n");
	}

	// Dimiourgia tou arxeiou fileName1
	printf("Creating file %s...\n\n", fileName1);
	if ( (rvalue = HDF_CreateFile(fileName1)) != BFE_OK) {
		printf("Checkpoint 2:\n");
		printf("HDF_CreateFile() returned %d!\n\n", rvalue);
	}

	// Anoigma tou arxeiou fileName1
	printf("Opening file %s...\n\n", fileName1);
	if ((rvalue = HDF_OpenFile(fileName1, &fp1)) != BFE_OK)
	{
		printf("Checkpoint 3:\n");
		printf("HDF_OpenFile() returned %d, should have returned 0!\n\n",rvalue);
	}

	// Dimiourgia epikefalidas tou arxeiou sti mnimi
	buffer = malloc(sizeof(char) * BF_BLOCK_SIZE);
	memset(buffer, 0, BF_BLOCK_SIZE);

	// Antigrafi epikefalidas sto block 0 tou arxeiou
	printf("Writing file header to disk...\n\n");
	if ((rvalue = HDF_WriteBlock(0, buffer, fp1)) != BFE_OK)
	{
		printf("Checkpoint 4:");
		printf("HDF_WriteBlock() returned %d!\n\n",rvalue);
	}

	// Kleisimo tou arxeiou fileName1
	printf("Closing file %s\n\n", fileName1);
	if ((rvalue = HDF_CloseFile(fp1)) != BFE_OK)
	{
		printf("Checkpoint 5:\n");
		printf("HDF_CloseFile() returned %d!\n\n", rvalue);
	}

	// ---------------------- Dimiourgia tou fileName2 ----------------------

	// Elegxos an yparxei to fileName2
	printf("Checking if file %s exists...\n\n", fileName2);
	if (HDF_ExistsFile(fileName2) == TRUE) {
		printf("Checkpoint 6:\n");
		printf("HDF_ExistsFile returned TRUE!\n\n");
	}

	// Dimiourgia tou arxeiou fileName2
	printf("Creating file %s...\n\n", fileName2);
	if ( (rvalue=HDF_CreateFile(fileName2)) != BFE_OK) {
		printf("Checkpoint 7:\n");
		printf("HDF_CreateFile() returned %d!\n\n", rvalue);
	}

	// Anoigma tou arxeiou fileName2
	printf("Opening file %s...\n\n", fileName2);
	if ((rvalue = HDF_OpenFile(fileName2, &fp2)) != BFE_OK)
	{
		printf("Checkpoint 8:\n");
		printf("HDF_OpenFile() returned %d, should have returned 0!\n\n",rvalue);
	}

	// Dimiourgia epikefalidas tou arxeiou sti mnimi
	memset(buffer, 0, BF_BLOCK_SIZE);

	// Antigrafi epikefalidas sto block 0 tou arxeiou
	printf("Writing file header to disk...\n\n");
	if ((rvalue = HDF_WriteBlock(0, buffer, fp2)) != BFE_OK)
	{
		printf("Checkpoint 9:");
		printf("HDF_WriteBlock() returned %d!\n\n",rvalue);
	}

	// Kleisimo tou arxeiou fileName2
	printf("Closing file %s\n\n", fileName2);
	if ((rvalue = HDF_CloseFile(fp2)) != BFE_OK)
	{
		printf("Checkpoint 10:\n");
		printf("HDF_CloseFile() returned %d!\n\n", rvalue);
	}

	// ---------------------- FMM epipedo ----------------------

	printf("------------------------------------\n");
	printf("OPENING FILES AND PROCESSING HEADERS\n");
	printf("------------------------------------\n\n");

	FMM_Init();

	// Anoigma tou fileName1
	printf("Opening file %s (1)...\n\n", fileName1);
	if ((fd11 = FMM_Open(fileName1)) < 0) {
		printf("Checkpoint 11:\n");
		printf("FMM_Open() returned %d!\n\n", fd11);
	}

	// Anoigma tou fileName2
	printf("Opening file %s (1)...\n\n", fileName2);
	if ((fd21 = FMM_Open(fileName2)) < 0) {
		printf("Checkpoint 12:\n");
		printf("FMM_Open() returned %d!\n\n", fd21);
	}

	// 2o anoigma tou fileName1
	printf("Opening file %s (2)...\n\n", fileName1);
	if ((fd12 = FMM_Open(fileName1)) < 0) {
		printf("Checkpoint 13:\n");
		printf("FMM_Open() returned %d!\n\n", fd12);
	}

	// To 1o anoigma tou fileName1 markarei to block blockNumInFile11 (arithmisi HDF) tou fileName1 ws egkyro
	blockNumInFile11 = 3;
	blockNumInHeader11 = blockNumInFile11 - 1; // PROSOXH SE AYTO!!!
	printf("Marking header bit %d as valid for file %s (1)...\n\n", blockNumInHeader11, fileName1);
	if ((rvalue = FMM_HEAD_Set(fd11, blockNumInHeader11, TRUE)) != BFE_OK) {
		printf("Checkpoint 14:");
		printf("FMM_HEAD_Set() returned %d!\n\n",rvalue);
	}

	// To 2o anoigma tou fileName1 prepei na mporei na dei ayti ti metavoli tou parapanw block se valid
	printf("2nd opening of file %s sees marked block as %s\n\n", fileName1, printBoolean(FMM_HEAD_IsValid(fd12, blockNumInHeader11)));

	// 3o anoigma tou fileName1
	printf("Opening file %s (3)...\n\n", fileName1);
	if ((fd13 = FMM_Open(fileName1)) < 0) {
		printf("Checkpoint 15:\n");
		printf("FMM_Open() returned %d!\n\n", fd13);
	}

	// To 3o anoigma tou fileName1 prepei episis na mporei na dei ayti ti metavoli tou parapanw block se valid
	printf("3nd opening of file %s sees marked block as %s\n\n", fileName1, printBoolean(FMM_HEAD_IsValid(fd13, blockNumInHeader11)));

	// To 3o anoigma tou fileName1 markarei to block blockNumInHeader12 (arithmisi FMM) tou fileName1 ws egkyro
	blockNumInHeader12 = 9;
	printf("Marking header bit %d as valid for file %s (3)...\n\n", blockNumInHeader12, fileName1);
	if ((rvalue = FMM_HEAD_Set(fd13, blockNumInHeader12, TRUE)) != BFE_OK) {
		printf("Checkpoint 16:");
		printf("FMM_HEAD_Set() returned %d!\n\n",rvalue);
	}

	// To 2o anoigma tou fileName1 prepei na mporei na dei tin teleytaia metavoli
	printf("2nd opening of file %s sees marked block as %s\n\n", fileName1, printBoolean(FMM_HEAD_IsValid(fd12, blockNumInHeader12)));

	// To 1o anoigma tou fileName1 prepei episis na vlepei tin teleytaia metavoli
	printf("1st opening of file %s sees marked block as %s\n\n", fileName1, printBoolean(FMM_HEAD_IsValid(fd11, blockNumInHeader12)));

	// Kleisimo 1ou anoigmatos tou fileName1
	printf("Closing file %s (1)...\n\n", fileName1);
	if ((rvalue = FMM_Close(fd11)) != BFE_OK) {
		printf("Checkpoint 17:\n");
		printf("FMM_Close() returned %d!\n\n", rvalue);
	}

	// 2o anoigma tou fileName2
	printf("Opening file %s (2)...\n\n", fileName2);
	if ((fd22 = FMM_Open(fileName2)) < 0) {
		printf("Checkpoint 18:\n");
		printf("FMM_Open() returned %d!\n\n", fd22);
	}

	// To 2o anoigma tou fileName2 markarei to block blockNumInHeader21 (arithmisi FMM) tou fileName1 ws egkyro
	blockNumInHeader21 = 0;
	printf("Marking header bit %d as valid for file %s (2)...\n\n", blockNumInHeader21, fileName2);
	if ((rvalue = FMM_HEAD_Set(fd22, blockNumInHeader21, TRUE)) != BFE_OK) {
		printf("Checkpoint 19:");
		printf("FMM_HEAD_Set() returned %d!\n\n",rvalue);
	}

	printf("1st opening of file %s sees marked block as %s\n\n", fileName2, printBoolean(FMM_HEAD_IsValid(fd21, blockNumInHeader21)));

	// Anaktisi tou prwtou egkyrou block tou arxeiou fileName2 apo to 1o anoigma
	printf("Retrieving first empty block of file %s using first opening...\n\n", fileName2);
	if ((firstEmpty = FMM_HEAD_GetFirstEmpty(fd21)) == BFE_EOF) {
		printf("Checkpoint 20:");
		printf("FMM_HEAD_GetFirstEmpty returned %d!\n\n",rvalue);
	}

	// To 1o anoigma tou fileName2 prepei na vlepei tin allagi, kai ara na epistrefei ws prwto keno block to block 1 (FMM arithmisi)
	printf("1st opening of file %s sees block no %d as the first empty block\n\n", fileName2, firstEmpty);

	// Kleisimo 3ou anoigmatos tou fileName1
	printf("Closing file %s (3)...\n\n", fileName1);
	if ((rvalue = FMM_Close(fd13)) != BFE_OK) {
		printf("Checkpoint 21:\n");
		printf("FMM_Close() returned %d!\n\n", rvalue);
	}

	// Anaktisi pliroforias gia to arxeio fileName1 me vasi to onoma
	strcpy(finfo.filename, fileName1);
	printf("Retrieving file information by name for file %s...\n\n", fileName1);
	if ((rvalue = FMM_GetFileInfoByName(&finfo)) != BFE_OK) {
		printf("Checkpoint 22:\n");
		printf("FMM_GetFileInfoByName() returned %d!\n\n", rvalue);
	}

	printFileInfo(&finfo);

	// Kleisimo 2ou anoigmatos tou fileName1
	printf("Closing file %s (2)...\n\n", fileName1);
	if ((rvalue = FMM_Close(fd12)) != BFE_OK) {
		printf("Checkpoint 23:\n");
		printf("FMM_Close() returned %d!\n\n", rvalue);
	}

	// Kleisimo 1ou anoigmatos tou fileName2
	printf("Closing file %s (1)...\n\n", fileName2);
	if ((rvalue = FMM_Close(fd21)) != BFE_OK) {
		printf("Checkpoint 24:\n");
		printf("FMM_Close() returned %d!\n\n", rvalue);
	}

	// Anaktisi pliroforias gia to arxeio fileName2 me vasi to fd
	strcpy(finfo.filename, fileName1);
	finfo.fd = fd22;
	printf("Retrieving file information by file descriptor using opening 2 of file %s...\n\n", fileName2);
	if ((rvalue = FMM_GetFileInfoByFD(&finfo)) != BFE_OK) {
		printf("Checkpoint 25:\n");
		printf("FMM_GetFileInfoByName() returned %d!\n\n", rvalue);
	}

	printFileInfo(&finfo);

	// Kleisimo 2ou anoigmatos tou fileName2
	printf("Closing file %s (2)...\n\n", fileName2);
	if ((rvalue = FMM_Close(fd22)) != BFE_OK) {
		printf("Checkpoint 26:\n");
		printf("FMM_Close() returned %d!\n\n", rvalue);
	}

	free(buffer);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF_Defines.h"
#include "HDF_Lib.h"
#include "FMM_Lib.h"

#define fileName "ATHLETES"
#define ATHLETE_SIZE 32

void printFileInfo(fileInfo_t *finfo) {
	printf("Filename: %s\n", finfo->filename);
	printf("File pointer: %d\n", finfo->fp);
	printf("File descriptor: %d\n\n", finfo->fd);
}

int main(void) {
	int rvalue;
	FILE *fp;
	char *buffer;
	int fd;
	fileInfo_t finfo;
	char athlete[ATHLETE_SIZE];
	int offset;
	int blockNumInFile1;
	int blockNumInHeader1;
	int blockNumInFile2;
	int blockNumInHeader2;
	int firstValid;
	int secondValid;

	// ---------------------- HDF epipedo ----------------------

	// Elegxos an yparxei to fileName
	printf("\nChecking if file %s exists...\n\n", fileName);
	if (HDF_ExistsFile(fileName) == TRUE) {
		printf("Checkpoint 1:\n");
		printf("HDF_ExistsFile returned TRUE!\n\n");
	}

	// Dimiourgia tou arxeiou fileName
	printf("Creating file %s...\n\n", fileName);
	if ( (rvalue=HDF_CreateFile(fileName)) != BFE_OK) {
		printf("Checkpoint 2:\n");
		printf("HDF_CreateFile() returned %d!\n\n", rvalue);
	}

	// Anoigma tou arxeiou fileName
	printf("Opening file %s...\n\n", fileName);
	if ((rvalue = HDF_OpenFile(fileName,&fp)) != BFE_OK)
	{
		printf("Checkpoint 3:\n");
		printf("HDF_OpenFile() returned %d, should have returned 0!\n\n",rvalue);
	}

	// Dimiourgia epikefalidas tou arxeiou sti mnimi
	buffer = malloc(sizeof(char) * BF_BLOCK_SIZE);
	memset(buffer, 0, BF_BLOCK_SIZE);

	// Antigrafi epikefalidas sto block 0 tou arxeiou
	printf("Writing file header to disk...\n\n");
	if ((rvalue = HDF_WriteBlock(0, buffer, fp)) != BFE_OK)
	{
		printf("Checkpoint 4:");
		printf("HDF_WriteBlock() returned %d!\n\n",rvalue);
	}

	// Kleisimo tou arxeiou fileName
	printf("Closing file %s\n\n", fileName);
	if ((rvalue = HDF_CloseFile(fp)) != BFE_OK)
	{
		printf("Checkpoint 5:\n");
		printf("HDF_CloseFile() returned %d!\n\n", rvalue);
	}

	// ---------------------- FMM epipedo ----------------------

	FMM_Init();

	// Anoigma tou arxeiou
	printf("Opening file %s...\n\n", fileName);
	if ((fd = FMM_Open(fileName)) < 0) {
		printf("Checkpoint 6:\n");
		printf("FMM_Open() returned %d!\n\n", fd);
	}

	// Elegxos an i thesi fd tou pinaka anoixtwn arxeiwn einai pleon egkyri kataxwrisi arxeiou
	printf("Checking for validity of position %d of open files array...\n\n", fd);
	if (FMM_IsValid(fd) != TRUE) {
		printf("Checkpoint 7:\n");
		printf("FMM_IsValid() returned FALSE!\n\n");
	}

	// Anaktisi pliroforias gia to arxeio me vasi to onoma
	strcpy(finfo.filename, fileName);
	printf("Retrieving file information by name...\n\n");
	if ((rvalue = FMM_GetFileInfoByName(&finfo)) != BFE_OK) {
		printf("Checkpoint 8:\n");
		printf("FMM_GetFileInfoByName() returned %d!\n\n", rvalue);
	}
	printFileInfo(&finfo);

	// Anaktisi pliroforias gia to arxeio me vasi to fd
	finfo.fd = fd;
	printf("Retrieving file information by file descriptor...\n\n");
	if ((rvalue = FMM_GetFileInfoByFD(&finfo)) != BFE_OK) {
		printf("Checkpoint 9:\n");
		printf("FMM_GetFileInfoByFD() returned %d!\n\n", rvalue);
	}
	printFileInfo(&finfo);

	// Dimiourgia enos neou block sti mnimi
	memset(buffer, 0, BF_BLOCK_SIZE);
	offset = 0;
	strcpy(athlete, "Periklis Iakovakis");
	memcpy(buffer + offset, athlete, ATHLETE_SIZE);
	offset += ATHLETE_SIZE;
	strcpy(athlete, "Pyrros Dimas");
	memcpy(buffer + offset, athlete, ATHLETE_SIZE);
	offset += ATHLETE_SIZE;
	strcpy(athlete, "Helena Isinbayeva");
	memcpy(buffer + offset, athlete, ATHLETE_SIZE);
	offset += ATHLETE_SIZE;
	strcpy(athlete, "Blanka Vlasic");
	memcpy(buffer + offset, athlete, ATHLETE_SIZE);

	// Grapsimo aytou tou block sto arxeio sti thesi blockNumInFile
	fp = finfo.fp;
	blockNumInFile1 = 5;
	printf("Writing block to disk...\n\n");
	if ((rvalue = HDF_WriteBlock(blockNumInFile1, buffer, fp)) != BFE_OK)
	{
		printf("Checkpoint 10:");
		printf("HDF_WriteBlock() returned %d!\n\n",rvalue);
	}

	// Enimerwsi tis epikefalidas tou arxeiou oti to block ayto einai pleon egkyro
	blockNumInHeader1 = blockNumInFile1 - 1; // PROSOXH SE AYTO!!!
	printf("Updating header...\n\n");
	if ((rvalue = FMM_HEAD_Set(fd, blockNumInHeader1, TRUE)) != BFE_OK) {
		printf("Checkpoint 11:");
		printf("FMM_HEAD_Set() returned %d!\n\n",rvalue);
	}

	// Elegxos an enimerwthike i epikefalida
	printf("Checking header...\n\n");
	if (FMM_HEAD_IsValid(fd, blockNumInHeader1) == FALSE) {
		printf("Checkpoint 12:");
		printf("FMM_HEAD_isValid() returned %d!\n\n",rvalue);
	}

	// Anaktisi tou prwtou egkyrou block tou arxeiou
	printf("Retrieving first valid block...\n\n");
	if ((firstValid = FMM_HEAD_GetFirstBlock(fd)) == BFE_EOF) {
		printf("Checkpoint 13:");
		printf("FMM_HEAD_GetFirstBlock returned %d!\n\n",rvalue);
	}

	printf("firstValid = %d, it should be equal to %d\n\n", firstValid, blockNumInHeader1);

	// Dimiourgia enos 2ou neou block sti mnimi
	memset(buffer, 0, BF_BLOCK_SIZE);
	offset = 0;
	strcpy(athlete, "Vasilis Spanoulis");
	memcpy(buffer + offset, athlete, ATHLETE_SIZE);
	offset += ATHLETE_SIZE;
	strcpy(athlete, "Sofoklis Sxortsianitis");
	memcpy(buffer + offset, athlete, ATHLETE_SIZE);

	// Grapsimo aytou tou block sto arxeio sti thesi blockNumInFile
	blockNumInFile2 = 3;
	printf("Writing block to disk...\n\n");
	if ((rvalue = HDF_WriteBlock(blockNumInFile2, buffer, fp)) != BFE_OK)
	{
		printf("Checkpoint 14:");
		printf("HDF_WriteBlock() returned %d!\n\n",rvalue);
	}

	// Enimerwsi tis epikefalidas tou arxeiou oti to block ayto einai pleon egkyro
	blockNumInHeader2 = blockNumInFile2 - 1; // PROSOXH SE AYTO!!!
	printf("Updating header...\n\n");
	if ((rvalue = FMM_HEAD_Set(fd, blockNumInHeader2, TRUE)) != BFE_OK) {
		printf("Checkpoint 15:");
		printf("FMM_HEAD_Set() returned %d!\n\n",rvalue);
	}

	// Anaktisi tou prwtou egkyrou block tou arxeiou
	printf("Retrieving first valid block...\n\n");
	if ((firstValid = FMM_HEAD_GetFirstBlock(fd)) == BFE_EOF) {
		printf("Checkpoint 16:");
		printf("FMM_HEAD_GetFirstBlock returned %d!\n\n",rvalue);
	}

	printf("firstValid = %d, it should be equal to %d\n\n", firstValid, blockNumInHeader2);

	// Anaktisi tou prwtou egkyrou block tou arxeiou meta apo to firstValid
	printf("Retrieving first valid block after block %d...\n\n", firstValid);
	if ((secondValid = FMM_HEAD_GetNextBlock(fd, firstValid)) == BFE_EOF) {
		printf("Checkpoint 17:");
		printf("FMM_HEAD_GetFirstBlock returned %d!\n\n",rvalue);
	}

	printf("secondValid = %d, it should be equal to %d\n\n", secondValid, blockNumInHeader1);

	// Kleisimo arxeiou
	printf("Closing file %s...\n\n", fileName);
	if ((rvalue = FMM_Close(fd)) != BFE_OK) {
		printf("Checkpoint 19:\n");
		printf("FMM_Close() returned %d!\n\n", rvalue);
	}

	free(buffer);

	return 0;
}

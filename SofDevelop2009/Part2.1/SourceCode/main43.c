#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF_Defines.h"
#include "BF_Lib.h"
#include "BMM_Lib.h"
//#include "FMM_Lib.h"
//#include "HDF_Lib.h"
//#include "RMM_Lib.h"

#define RMM_MAIN_NAME_SIZE 30
#define RMM_MAIN_EVENT_NAME_SIZE 60
#define RMM_MAIN_DATE_SIZE 12

/*Megethos eggrafis typou Athlete*/
#define RMM_MAIN_ATHLETE_REC_SIZE sizeof(int) + 2*(sizeof(char) * RMM_MAIN_NAME_SIZE)

/*Megethos eggrafis typou Event*/
#define RMM_MAIN_EVENT_REC_SIZE sizeof(int) + (sizeof(char) * RMM_MAIN_EVENT_NAME_SIZE)

/*Megethos eggrafis typouParticipation*/
#define RMM_MAIN_PARTICIPATION_REC_SIZE 2*sizeof(int) + (sizeof(char) * RMM_MAIN_DATE_SIZE)

void main()
{
	int partsFd;
	char *partsRec;
	int counter;
	int recId;
	int athId, evId;
	char *partDate;

	BF_Init();

	//Anoigma arxeiou PARTICIPATIONS
	partsFd = BF_OpenFile("PARTICIPATIONS");

	if (partsFd < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on PARTICIPATIONS.");
		return;
	}

	partsRec = (char *) malloc(RMM_MAIN_PARTICIPATION_REC_SIZE);
	if (partsRec == NULL)
	{
		printf("Participation record malloc failed\n");
		return;
	}

	counter = 0;
	partDate = (char *) malloc(RMM_MAIN_DATE_SIZE);
	if (partDate == NULL)
	{
		printf("Participation date malloc failed\n");
		return;
	}

	printf("Counting Records of file PARTICIPATIONS\n");

	recId = RMM_GetFirstRec(partsFd, partsRec, RMM_MAIN_PARTICIPATION_REC_SIZE);
	
	while (recId >= 0)
	{
		counter++;

		memcpy((void *) &athId, (void *) partsRec, sizeof(int));
		partsRec += sizeof(int);

		memcpy((void *) &evId, (void *) partsRec, sizeof(int));
		partsRec += sizeof(int);

		memcpy((void *) partDate, (void *) partsRec, RMM_MAIN_DATE_SIZE);
		partsRec += RMM_MAIN_DATE_SIZE;

		printf("#%d Participation record: recId=%d, data=(%d, %d, %s)\n", counter, recId, athId, evId, partDate);

		
		partsRec -= RMM_MAIN_PARTICIPATION_REC_SIZE;

		recId = RMM_GetNextRec(partsFd, recId, partsRec, RMM_MAIN_PARTICIPATION_REC_SIZE);
	}

	free(partsRec);
	free(partDate);

	printf("The next number must be 1252: %d\n\n", counter);


	
	//Kleisimo arxeiou PARTICIPATIONS
	if (BF_CloseFile(partsFd) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on PARTICIPATIONS.");
}


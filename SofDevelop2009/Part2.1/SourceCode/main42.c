#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF_Defines.h"
#include "BF_Lib.h"
//#include "BMM_Lib.h"
#//include "FMM_Lib.h"
//#include "HDF_Lib.h"


#include "RMM_Lib.h"
#include "HF_Defines.h"

#define NO_OF_DELETES 20

#define RMM_MAIN_NAME_SIZE 30
#define RMM_MAIN_EVENT_NAME_SIZE 60
#define RMM_MAIN_DATE_SIZE 12

/*Megethos tis eggrafis typou Athlete*/
#define RMM_MAIN_ATHLETE_REC_SIZE sizeof(int) + 2*(sizeof(char) * RMM_MAIN_NAME_SIZE)

/*Megethos tis eggrafis typouEvent*/
#define RMM_MAIN_EVENT_REC_SIZE sizeof(int) + (sizeof(char) * RMM_MAIN_EVENT_NAME_SIZE)

/*Megethos tis eggrafis typou Participation*/
#define RMM_MAIN_PARTICIPATION_REC_SIZE 2*sizeof(int) + (sizeof(char) * RMM_MAIN_DATE_SIZE)

int main(void)
{
	int partsFd;
	int athletesFd;

	char *partsRec;
	char *athletesRec;

	int counter;

	int recId;
	int i;
	int retVal;

       
	//Anoigma arxeiou ATHLETES

    BF_Init();
	athletesFd = BF_OpenFile("ATHLETES");

	if (athletesFd < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on ATHLETES.");
		return 0;
	}

	athletesRec = (char *) malloc(RMM_MAIN_ATHLETE_REC_SIZE);
	if (athletesRec == NULL)
	{
		printf("Athlete record malloc failed\n");
		return 0;
	}

	counter = 0;

	printf("Counting Records of file ATHLETES\n");

	retVal = RMM_GetFirstRec(athletesFd, athletesRec, RMM_MAIN_ATHLETE_REC_SIZE);
	
	while (retVal >= 0)
	{
		counter++;

		if (counter == 1 || counter == 386 || (counter % 50) == 0 )
		{
			int athId;
			char *athSurname, *athName;

			athSurname = (char *) malloc(RMM_MAIN_NAME_SIZE);
			if (athSurname == NULL)
			{
				printf("Athlete surname malloc failed\n");
				return 0;
			}
			athName = (char *) malloc(RMM_MAIN_NAME_SIZE);
			if (athName == NULL)
			{
				printf("Athlete name malloc failed\n");
				return 0;
			}

			memcpy( &athId, athletesRec, sizeof(int));
			athletesRec += sizeof(int);

			memcpy( athSurname, athletesRec, RMM_MAIN_NAME_SIZE);
			athletesRec += RMM_MAIN_NAME_SIZE;

			memcpy( athName, athletesRec, RMM_MAIN_NAME_SIZE);
			athletesRec += RMM_MAIN_NAME_SIZE;

			printf("#%d Athlete record: recId=%d, data=(%d, %s, %s)\n", counter, retVal, athId, athSurname, athName);

			free(athSurname);
			free(athName);
			
			athletesRec -= RMM_MAIN_ATHLETE_REC_SIZE;
		}

		retVal = RMM_GetNextRec(athletesFd, retVal, athletesRec, RMM_MAIN_ATHLETE_REC_SIZE);
	}

	free(athletesRec);

	printf("The next number must be 386: %d\n\n", counter);

	//Kleisimo arxeiou ATHLETES
	if (BF_CloseFile(athletesFd) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");



	//Anoigma arxeiou PARTICIPATIONS
	partsFd = BF_OpenFile("PARTICIPATIONS");

	if (partsFd < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on PARTICIPATIONS.");
		return 0;
	}

	partsRec = (char *) malloc(RMM_MAIN_PARTICIPATION_REC_SIZE);
	if (partsRec == NULL)
	{
		printf("Participation record malloc failed\n");
		return 0;
	}

	printf("Deleting Records from file PARTICIPATIONS (random selection)\n");


	for (i=0; i <NO_OF_DELETES; i++)
	{
		recId = rand()%1272;

		if ( RMM_GetThisRec(partsFd, recId, partsRec, RMM_MAIN_PARTICIPATION_REC_SIZE) != HFE_OK )
			printf("RMM_GetThisRec failed to retrieve record with recId %d from PARTICIPATIONS", recId);

		else
		{
			int athId, evId;
			char *partDate;

			partDate = (char *) malloc(RMM_MAIN_DATE_SIZE);
			if (partDate == NULL)
			{
				printf("Participation date malloc failed\n");
				return 0;
			}

			memcpy((void *) &athId, (void *) partsRec, sizeof(int));
			partsRec += sizeof(int);

			memcpy((void *) &evId, (void *) partsRec, sizeof(int));
			partsRec += sizeof(int);

			memcpy((void *) partDate, (void *) partsRec, RMM_MAIN_DATE_SIZE);
			partsRec += RMM_MAIN_DATE_SIZE;

			printf("Participation record to delete: recId=%d, data=(%d, %d, %s)\n", recId, athId, evId, partDate);
			if ( RMM_DeleteRec(partsFd, recId, RMM_MAIN_PARTICIPATION_REC_SIZE) != HFE_OK )
				printf("RMM_DeleteRec failed to delete record with recId %d from PARTICIPATIONS", recId);

			free(partDate);
			
			partsRec -= RMM_MAIN_PARTICIPATION_REC_SIZE;
		}

	}

	free(partsRec);

	//Kleisimo arxeiou PARTICIPATIONS
	if (BF_CloseFile(partsFd) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on PARTICIPATIONS.");


		
	return 0;
}


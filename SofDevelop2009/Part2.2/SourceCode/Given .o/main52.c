#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HF_Lib.h"

#define HF_MAIN_NAME_SIZE 30
#define HF_MAIN_EVENT_NAME_SIZE 60
#define HF_MAIN_DATE_SIZE 12

/*Μέγεθος της εγγραφής τύπου Athlete*/
#define HF_MAIN_ATHLETE_REC_SIZE sizeof(int) + 2*(sizeof(char) * HF_MAIN_NAME_SIZE)

/*Μέγεθος της εγγραφής τύπου Event*/
#define HF_MAIN_EVENT_REC_SIZE sizeof(int) + (sizeof(char) * HF_MAIN_EVENT_NAME_SIZE)

/*Μέγεθος της εγγραφής τύπου Participation*/
#define HF_MAIN_PARTICIPATION_REC_SIZE 2*sizeof(int) + (sizeof(char) * HF_MAIN_DATE_SIZE)

void main()
{
	int athletesFd;
	int eventsFd;
	int partsFd;

	char *athleteRec;
	char *eventRec;
	char *partsRec;

	int athletesScan;
	int athletesScan1;

	int eventsScan;

	int counter;

	int recId;


	//Αρχικοποίηση Επιπέδου HF
	HF_Init();


	//’νοιγμα Αρχείου PARTICIPATIONS
	partsFd = HF_OpenFile("PARTICIPATIONS");

	if (partsFd < 0)
	{
		HF_PrintError("Error in HF_OpenFile called on PARTICIPATIONS.");
		return;
	}

	partsRec = (char *) malloc(HF_MAIN_PARTICIPATION_REC_SIZE);
	if (partsRec == NULL)
	{
		printf("Participation record malloc failed\n");
		return;
	}

	counter = 0;

	printf("Counting Records of file PARTICIPATIONS\n");

	recId = HF_GetFirstRec(partsFd, partsRec, HF_MAIN_PARTICIPATION_REC_SIZE);
	printf("%d\n",recId);
	
	while (recId >= 0)
	{
		counter++;
		
		if (counter == 1 || counter == 1272 || (counter % 100) == 0 )
		{
			int athId, evId;
			char *partDate;

			partDate = (char *) malloc(HF_MAIN_DATE_SIZE);
			if (partDate == NULL)
			{
				printf("Participation date malloc failed\n");
				return;
			}

			memcpy((void *) &athId, (void *) partsRec, sizeof(int));
			partsRec += sizeof(int);

			memcpy((void *) &evId, (void *) partsRec, sizeof(int));
			partsRec += sizeof(int);

			memcpy((void *) partDate, (void *) partsRec, HF_MAIN_DATE_SIZE);
			partsRec += HF_MAIN_DATE_SIZE;

			printf("#%d Participation record: recId=%d, data=(%d, %d, %s)\n", counter, recId, athId, evId, partDate);

			free(partDate);
			
			partsRec -= HF_MAIN_PARTICIPATION_REC_SIZE;
		}

		recId = HF_GetNextRec(partsFd, recId, partsRec, HF_MAIN_PARTICIPATION_REC_SIZE);
	}

	free(partsRec);

	printf("The next number must be 1272: %d\n\n", counter);


	//’νοιγμα Αρχείου EVENTS
	eventsFd = HF_OpenFile("EVENTS");

	if (eventsFd < 0)
	{
		HF_PrintError("Error in HF_OpenFile called on EVENTS.");
		return;
	}

	//Scan στο Αρχείο EVENTS με NULL συνθήκη
	eventsScan = HF_OpenFileScan(eventsFd, 
									  HF_MAIN_EVENT_REC_SIZE,
									  ' ',
									  -1,
									  -1,
									  -1,
									  (char *) NULL);
	if (eventsScan < 0) 
	{
		HF_PrintError("HF_OpenFileScan on EVENTS failed");
		return;
	}


	eventRec = (char *) malloc(HF_MAIN_EVENT_REC_SIZE);
	if (eventRec == NULL)
	{
		printf("Event Record malloc failed\n");
		return;
	}

	counter = 0;

	printf("Scan of file EVENTS with null condition\n");

	int rVal;
	while ((rVal=HF_FindNextRec(eventsScan, eventRec)) >= 0)
	{
		int eventId;
		char *eventName = (char *) malloc(HF_MAIN_EVENT_NAME_SIZE);
		if (eventName == NULL)
		{
			printf("Event Name malloc failed\n");
			return;
		}

		counter++;

		memcpy((void *) &eventId, (void *) eventRec, sizeof(int));
		eventRec += sizeof(int);

		memcpy((void *) eventName, (void *) eventRec, HF_MAIN_EVENT_NAME_SIZE);
		eventRec += HF_MAIN_EVENT_NAME_SIZE;

		printf("Found Event Record: (%d, \"%s\")\n", eventId, eventName);

		eventRec -= HF_MAIN_EVENT_REC_SIZE;

		free(eventName);
	}
	printf("Next number must be equal to 32: %d\n\n", counter);

	free(eventRec);

	//Κλείσιμο του Scan στο Αρχείο EVENTS
	if (HF_CloseFileScan(eventsScan) != HFE_OK)
	{
		HF_PrintError("Close of Scan on EVENTS Failed.");
		return;
	}


	//’νοιγμα Αρχείου ATHLETES
	athletesFd = HF_OpenFile("ATHLETES");

	if (athletesFd < 0)
	{
		HF_PrintError("Error in HF_OpenFile called on ATHLETES.");
		return;
	}

	//Scan στο Αρχείο ATHLETES με συνθήκη athleteSurname = "MELETOGLOY"
	athletesScan = HF_OpenFileScan(athletesFd, 
								   HF_MAIN_ATHLETE_REC_SIZE,
								   'c',
								   HF_MAIN_NAME_SIZE,
								   sizeof(int),
								   1,
								   "MELETOGLOY");
	
	if (athletesScan < 0) 
	{
		HF_PrintError("HF_OpenFileScan on ATHLETES failed");
		return;
	}

	athleteRec = (char *) malloc(HF_MAIN_ATHLETE_REC_SIZE);
	if (athleteRec == NULL)
	{
		printf("Athlete Record malloc failed\n");
		return;
	}

	printf("Ok till here\n");
	if ((rVal=HF_FindNextRec(athletesScan, athleteRec)) < 0)
	{
		HF_PrintError("Athlete Record not found");
	}
	else
	{
		int athleteId;
		char *athleteName;
		char *athleteSurname;
		

		athleteName = (char *) malloc(HF_MAIN_NAME_SIZE);
		if (athleteName == NULL)
		{
			printf("Athlete Name malloc failed\n");
			return;
		}
		athleteSurname = (char *) malloc(HF_MAIN_NAME_SIZE);
		if (athleteSurname == NULL)
		{
			printf("Athlete Surname malloc failed\n");
			return;
		}


		memcpy((void *) &athleteId, (void *) athleteRec, sizeof(int));
		athleteRec += sizeof(int);

		memcpy((void *) athleteSurname, (void *) athleteRec, HF_MAIN_NAME_SIZE);
		athleteRec += HF_MAIN_NAME_SIZE;

		memcpy((void *) athleteName, (void *) athleteRec, HF_MAIN_NAME_SIZE);
		athleteRec += HF_MAIN_NAME_SIZE;

		athleteRec -= HF_MAIN_ATHLETE_REC_SIZE;

		//Επαλήθευση τιμής που ανακτήθηκε
		if (strcmp(athleteSurname, "MELETOGLOY") != 0)
		{
			HF_PrintError("Invalid Athlete Record returned");
			return;
		}

		printf("Name of MELETOGLOY is %s. Scanning for Athletes with different name.\n", athleteName);

		//Δεύτερο Scan στο Αρχείο ATHLETES με συνθήκη athleteName != (Name of "MELETOGLOY")
		athletesScan1 = HF_OpenFileScan(athletesFd, 
									  HF_MAIN_ATHLETE_REC_SIZE,
									  'c',
									  HF_MAIN_NAME_SIZE,
									  sizeof(int) + HF_MAIN_NAME_SIZE,
									  6,
									  athleteName);

		counter = 0;

		printf("Scan of file ATHLETES with condition: athleteName != %s\n", athleteName);

		while (HF_FindNextRec(athletesScan1, athleteRec) >= 0)
		{
			char *sameAthleteName = (char *) malloc(HF_MAIN_NAME_SIZE);
			if (sameAthleteName == NULL)
			{
				printf("2nd Athlete Name malloc failed\n");
				return;
			}

			counter++;

			memcpy((void *) &athleteId, (void *) athleteRec, sizeof(int));
			athleteRec += sizeof(int);

			memcpy((void *) athleteSurname, (void *) athleteRec, HF_MAIN_NAME_SIZE);
			athleteRec += HF_MAIN_NAME_SIZE;

			memcpy((void *) sameAthleteName, (void *) athleteRec, HF_MAIN_NAME_SIZE);
			athleteRec += HF_MAIN_NAME_SIZE;

			athleteRec -= HF_MAIN_ATHLETE_REC_SIZE;

			printf("Found Athlete Record (%d, %s, %s).\n", athleteId, athleteSurname, sameAthleteName);

			//Επαλήθευση τιμής που ανακτήθηκε
			if (strcmp(athleteName, sameAthleteName) == 0)
			{
				HF_PrintError("Invalid Athlete Record\n");
				return;
			}

			free(sameAthleteName);
		}

		printf("Next number must be equal to 379: %d\n\n", counter);

		free(athleteName);
		free(athleteSurname);

		//Κλείσιμο του δεύτερου Scan στο Αρχείο ATHLETES
		if (HF_CloseFileScan(athletesScan1) != HFE_OK)
		{
			HF_PrintError("Close of second Scan on ATHLETES Failed.");
			return;
		}
	}

	free(athleteRec);

	//Κλείσιμο του πρώτου Scan στο Αρχείο ATHLETES
	if (HF_CloseFileScan(athletesScan) != HFE_OK)
	{
		HF_PrintError("Close of first Scan on ATHLETES Failed.");
		return;
	}

	
	//Κλείσιμο Αρχείου PARTICIPATIONS
	if (HF_CloseFile(partsFd) != HFE_OK)
		HF_PrintError("Error in HF_CloseFile called on PARTICIPATIONS.");
	
	//Κλείσιμο Αρχείου EVENTS
	if (HF_CloseFile(eventsFd) != HFE_OK)
		HF_PrintError("Error in HF_CloseFile called on EVENTS.");

	//Κλείσιμο Αρχείου ATHLETES
	if (HF_CloseFile(athletesFd) != HFE_OK)
		HF_PrintError("Error in HF_CloseFile called on ATHLETES.");

}


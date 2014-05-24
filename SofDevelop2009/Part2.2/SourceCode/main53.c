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
	int eventsScan;
	int partsScan;

	int eventId;
	int eventRecId;
	int partRecId;

	int partsCounter = 0;


	//Αρχικοποίηση Επιπέδου HF
	HF_Init();


	//’νοιγμα Αρχείου EVENTS
	eventsFd = HF_OpenFile("EVENTS");

	if (eventsFd < 0)
	{
		HF_PrintError("Error in HF_OpenFile called on EVENTS.");
		return;
	}


	//’νοιγμα Αρχείου PARTICIPATIONS
	partsFd = HF_OpenFile("PARTICIPATIONS");

	if (partsFd < 0)
	{
		HF_PrintError("Error in HF_OpenFile called on PARTICIPATIONS.");
		return;
	}


	//’νοιγμα Αρχείου ATHLETES
	athletesFd = HF_OpenFile("ATHLETES");

	if (athletesFd < 0)
	{
		HF_PrintError("Error in HF_OpenFile called on ATHLETES.");
		return;
	}
	
	eventId= 30;

	//Scan στο Αρχείο EVENTS με συνθήκη eventId >= "30"
	eventsScan = HF_OpenFileScan(eventsFd, 
								 HF_MAIN_EVENT_REC_SIZE,
								 'i',
								 sizeof(int),
								 0,
								 5,
								 (char *) &eventId);
	
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

	printf("Scan of file EVENTS with condition: eventId >= %d\n\n", eventId);

	while ( (eventRecId = HF_FindNextRec(eventsScan, eventRec)) >= 0)
	{		
		int recEventId;
		char *eventName = (char *) malloc(HF_MAIN_EVENT_NAME_SIZE);
		if (eventName == NULL)
		{
			printf("Event Name malloc failed\n");
			return;
		}

		memcpy((void *) &recEventId, (void *) eventRec, sizeof(int));
		eventRec += sizeof(int);

		memcpy((void *) eventName, (void *) eventRec, HF_MAIN_EVENT_NAME_SIZE);
		eventRec += HF_MAIN_EVENT_NAME_SIZE;

		printf("Found Event Record: recId=%d, data=(%d, %s)\n", eventRecId, recEventId, eventName);

		eventRec -= HF_MAIN_EVENT_REC_SIZE;

		//Επαλήθευση της τιμής που ανακτήθηκε
		if (recEventId < eventId)
		{
			printf("Invalid Event record\n");
			return;
		}


		//Scan στο Αρχείο PARTICIPATIONS με συνθήκη eventId = recEventId
		partsScan = HF_OpenFileScan(partsFd,
									HF_MAIN_PARTICIPATION_REC_SIZE,
									'i',
									sizeof(int),
									sizeof(int),
									1,
									(char *) &recEventId);

		if (partsScan < 0) 
		{
			HF_PrintError("HF_OpenFileScan on PARTICIPATIONS failed");
			return;
		}

		partsRec = (char *) malloc(HF_MAIN_PARTICIPATION_REC_SIZE);
		if (partsRec == NULL)
		{
			printf("Participation Record malloc failed\n");
			return;
		}

		printf("Scan of file PARTICIPATIONS with condition: eventId = %d\n", recEventId);

		while ( (partRecId = HF_FindNextRec(partsScan, partsRec)) >= 0)
		{
			int partAthId, partEvId;
			char *partDate;

			partDate = (char *) malloc(HF_MAIN_DATE_SIZE);
			if (partDate == NULL)
			{
				printf("Participation Date malloc failed\n");
				return;
			}

			memcpy((void *) &partAthId, (void *)partsRec, sizeof(int));
			partsRec += sizeof(int);

			memcpy((void *) &partEvId, (void *)partsRec, sizeof(int));
			partsRec += sizeof(int);

			memcpy((void *) partDate, (void *)partsRec, HF_MAIN_DATE_SIZE);
			partsRec += HF_MAIN_DATE_SIZE;

			printf("Found Participation Record: recId=%d, data=(%d, %d, %s)\n", partRecId, partAthId, partEvId, partDate);

			partsRec -= HF_MAIN_PARTICIPATION_REC_SIZE;

			//Επαλήθευση της τιμής που ανακτήθηκε
			if (partEvId != recEventId)
			{
				HF_PrintError("Invalid Participation Record\n");
				return;
			}


			//Scan στο Αρχείο ATHLETES με συνθήκη athleteId = partAthId
			athletesScan = HF_OpenFileScan(athletesFd, 
										   HF_MAIN_ATHLETE_REC_SIZE,
										   'i',
										   sizeof(int),
										   0,
										   1,
										   (char *) &partAthId);
			
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

			printf("Scan of file ATHLETES with condition: athleteId = %d\n", partAthId);

			if (HF_FindNextRec(athletesScan, athleteRec) >= 0)
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

				printf("Found Athlete Record: (%d, %s, %s)\n", athleteId, athleteSurname, athleteName);

				//Επαλήθευση της τιμής που ανακτήθηκε
				if (athleteId != partAthId)
				{
					HF_PrintError("Invalid Athlete Record\n");
					return;
				}

				printf("Athlete %s, %s participated in %s on %s.\n", athleteSurname, athleteName, eventName, partDate);

				free(athleteSurname);
				free(athleteName);
			}

			if (HF_FindNextRec(athletesScan, athleteRec) >= 0)
			{
				HF_PrintError("File Scan on Athletes returned a second Athlete record");
				return;
			}

			free(athleteRec);

			//Κλείσιμο του Scan στο Αρχείο ATHLETES
			if (HF_CloseFileScan(athletesScan) != HFE_OK)
			{
				HF_PrintError("Close of Scan on ATHLETES Failed.");
				return;
			}

			printf("Deleting Participation Record %d\n", partRecId);
			if (HF_DeleteRec(partsFd, partRecId, HF_MAIN_PARTICIPATION_REC_SIZE) != HFE_OK)
			{
				HF_PrintError("Deletion of Participation Record failed.");
				return;
			}
			partsCounter++;
			
			free(partDate);
		}

		free(partsRec);

		//Κλείσιμο του Scan στο Αρχείο PARTICIPATIONS
		if (HF_CloseFileScan(partsScan) != HFE_OK)
		{
			HF_PrintError("Close of Scan on PARTICIPATIONS Failed.");
			return;
		}

		printf("Deleting Event Record: recId=%d, data=(%d, %s)\n\n", eventRecId, recEventId, eventName);
		if (HF_DeleteRec(eventsFd, eventRecId, HF_MAIN_EVENT_REC_SIZE) != HFE_OK)
		{
			HF_PrintError("Deletion of Event Record failed.");
			return;
		}

		free(eventName);
	}

	free(eventRec);

	printf("Deleted %d participations\n", partsCounter);
	
	
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


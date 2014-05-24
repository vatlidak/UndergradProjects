#include <stdio.h>
#include <string.h>
#include "BF_Lib.h"
#include "BF_Defines.h"

#define BF_MAIN_NAME_SIZE 30
#define BF_MAIN_EVENT_NAME_SIZE 60
#define BF_MAIN_DATE_SIZE 12
#define BF_MAIN_MAX_NUM_OF_RECS 16
#define BF_MAIN_MAX_NUM_OF_EVENT_RECS 50

void insertEvent(int eventId, char *eventName, char **eventsBlockBuf)
{
	memcpy((void *) *eventsBlockBuf, (void *) &eventId, sizeof(int));
	*eventsBlockBuf += sizeof(int);
	strcpy(*eventsBlockBuf, eventName);
	*eventsBlockBuf += BF_MAIN_EVENT_NAME_SIZE;
}

void insertAthlete(int athleteId, char *athleteSurname, char *athleteName, char **athletesBlockBuf)
{
	memcpy((void *) *athletesBlockBuf, (void *) &athleteId, sizeof(int));
	*athletesBlockBuf += sizeof(int);
	strcpy(*athletesBlockBuf, athleteSurname);
	*athletesBlockBuf += BF_MAIN_NAME_SIZE;
	strcpy(*athletesBlockBuf, athleteName);
	*athletesBlockBuf += BF_MAIN_NAME_SIZE;
}

void insertParticipation(int eventId, int athleteId, char *date, char **participationsBlockBuf)
{
	memcpy((void *) *participationsBlockBuf, (void *) &eventId, sizeof(int));
	*participationsBlockBuf += sizeof(int);
	memcpy((void *) *participationsBlockBuf, (void *) &athleteId, sizeof(int));
	*participationsBlockBuf += sizeof(int);
	strcpy(*participationsBlockBuf, date);
	*participationsBlockBuf += BF_MAIN_DATE_SIZE;
}

void callAllocBlock(int fileDescriptor, int *blockNum, char **blockBuf, char *fileName)
{
	char message[BF_MAIN_EVENT_NAME_SIZE];
	sprintf(message, "Error in BF_AllocBlock called on %s.", fileName);
	if (BF_AllocBlock(fileDescriptor, blockNum, blockBuf) < 0)
		BF_PrintError(message);
	else memset(*blockBuf, 0, BF_BLOCK_SIZE);
}

int main()
{
	int eventsFd;
	int eventsBlockNum;
	char *eventsBlockBuf;
	int eventId;

	int athletesFd;
	int athletesBlockNum;
	char *athletesBlockBuf;
	int athleteId;

	int participationsFd;
	int participationsBlockNum;
	char *participationsBlockBuf;

	/* ������������ ��� �������� ������� ����� */
	BF_Init();

	/* ��������� ����� ������� */
	if (BF_CreateFile("EVENTS") != BFE_OK)
	{
		BF_PrintError("Error in BF_CreateFile called on EVENTS.");
	}

	if (BF_CreateFile("ATHLETES") != BFE_OK)
	{
		BF_PrintError("Error in BF_CreateFile called on ATHLETES.");
	}

	if (BF_CreateFile("PARTICIPATIONS") != BFE_OK)
	{
		BF_PrintError("Error in BF_CreateFile called on PARTICIPATIONS.");
	}

	/* ������� ����� ������� */
	eventsFd = BF_OpenFile("EVENTS");
	athletesFd = BF_OpenFile("ATHLETES");
	participationsFd = BF_OpenFile("PARTICIPATIONS");

	eventId = 0;
	athleteId = 0;

	/* �������� ��� ��� ����� ��� �� ������ EVENTS. */
	callAllocBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf, "EVENTS");

	/* �������� ��� �������� 1 ��� ������ EVENT */
	insertEvent(eventId, "XEIROSFAIRISH", &eventsBlockBuf);

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 1 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BEMH", "PANAGOYLA", &athletesBlockBuf);

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 2 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GIOYPH", "STYLIANH", &athletesBlockBuf);

	/* �������� ��� �������� 3 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 5 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 6 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 7 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 8 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 9 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 10 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 11 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 12 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 13 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 14 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 15 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 16 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 17 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 18 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 19 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 20 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 21 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 3 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKOLIA", "GRHGORIA", &athletesBlockBuf);

	/* �������� ��� �������� 22 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 23 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 24 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 25 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 26 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 27 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 28 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 4 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DVROUEOY", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 29 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 30 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 31 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 32 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 33 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 34 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 35 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 36 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 37 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 38 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 39 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 40 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 41 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 42 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 43 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 44 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 45 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 5 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UEODVRIDOY", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 46 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 47 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 48 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 49 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 50 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1999", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 51 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 52 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 53 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 54 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 55 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 56 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 57 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 58 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 59 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 60 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 61 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 62 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 63 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 6 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MAYROGENH", "ELEYUERIA", &athletesBlockBuf);

	/* �������� ��� �������� 64 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 65 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 66 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 67 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 68 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 69 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 70 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 71 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 7 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MIXALOPOYLOY", "MIXAELA", &athletesBlockBuf);

	/* �������� ��� �������� 72 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 73 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 74 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 75 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 8 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NIKOLH", "ELENA", &athletesBlockBuf);

	/* �������� ��� �������� 76 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 77 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 78 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 79 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 80 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 81 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 82 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 83 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 84 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 85 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 9 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PATSIOY", "ANASTASIA", &athletesBlockBuf);

	/* �������� ��� �������� 86 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 87 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 88 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 89 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 90 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 91 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 92 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 93 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 94 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 95 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 96 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 97 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 98 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 99 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 100 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 101 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 102 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 10 ��� ������ ATHLETES */
	insertAthlete(athleteId, "POIMENIDOY", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 103 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 104 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 105 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 106 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 11 ��� ������ ATHLETES */
	insertAthlete(athleteId, "POTARH", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 107 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 108 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 109 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 110 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 111 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 112 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 113 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 12 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SKARA", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 114 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 115 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 13 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SOYSA", "TATIANA", &athletesBlockBuf);

	/* �������� ��� �������� 116 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 117 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 118 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 14 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FVTIADOY", "IVANNA", &athletesBlockBuf);

	/* �������� ��� �������� 119 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 120 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 121 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 122 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 123 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 124 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 125 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 126 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 127 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 128 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 129 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 130 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 131 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 132 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 133 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 134 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 135 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 136 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 137 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 138 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 15 ��� ������ ATHLETES */
	insertAthlete(athleteId, "CAUA", "ANNA", &athletesBlockBuf);

	/* �������� ��� �������� 139 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 140 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 141 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 16 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ALBANOS", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 142 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 143 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 144 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 145 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 146 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 147 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 148 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 149 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 150 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1998", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 151 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 152 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 153 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 154 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 155 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 156 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 157 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1991", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 17 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BASILAKHS", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 158 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 159 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 160 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 161 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 162 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 163 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 164 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 165 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 18 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BOGLHS", "EYAGGELOS", &athletesBlockBuf);

	/* �������� ��� �������� 166 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 167 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 168 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 169 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 170 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 171 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 172 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 173 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 174 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 175 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 176 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 19 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GRAMMATIKOS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 177 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 178 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 179 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 180 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 181 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 182 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 183 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 184 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 185 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 186 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 187 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 188 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 20 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ZARABINAS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 189 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 190 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 191 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 192 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 193 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 194 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 195 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 196 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 197 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 198 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 199 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 200 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2000", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 201 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 202 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 203 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 21 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARYPIDHS", "SABBAS", &athletesBlockBuf);

	/* �������� ��� �������� 204 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 205 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 22 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAFFATOS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 206 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 207 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 208 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 209 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 210 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 23 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOKOLODHMHTRAKHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 211 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 212 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 213 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 214 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 215 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 216 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 217 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 218 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 219 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 220 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 24 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPALVMENOS", "SPYRIDVN", &athletesBlockBuf);

	/* �������� ��� �������� 221 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 222 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 223 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 224 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 225 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 226 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 227 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 228 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 25 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZIMOYRTOS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 229 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 230 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 231 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 232 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 233 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 234 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 235 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 236 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 26 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TROYPHS", "ANDREAS", &athletesBlockBuf);

	/* �������� ��� �������� 237 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 238 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 239 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 27 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSILIMPARHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 240 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 241 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 242 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 243 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 244 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 245 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 246 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 247 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 248 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 249 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 250 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1993", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 251 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 252 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 28 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XALKIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 253 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 254 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 29 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XATSATOYRIAN", "KRIKOR-GRHGOR", &athletesBlockBuf);

	/* �������� ��� �������� 255 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 256 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 257 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 258 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 259 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 260 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 261 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 262 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 263 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 264 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 265 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 266 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 267 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 268 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 269 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 30 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRYSOPOYLOS", "IVANNHS", &athletesBlockBuf);

	/* �������� ��� �������� 270 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 271 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 272 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 273 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 274 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 275 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 276 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 277 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 278 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 279 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 280 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 281 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 282 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 283 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1989", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 2 ��� ������ EVENT */
	insertEvent(eventId, "ANTISFAIRISH", &eventsBlockBuf);

	/* �������� ��� �������� 31 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ZAXARIADOY", "XRISTINA", &athletesBlockBuf);

	/* �������� ��� �������� 284 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 285 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 286 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 287 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 288 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 289 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 290 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 291 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 292 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 293 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 294 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 295 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 296 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 297 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 298 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 299 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 300 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 32 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DANIHLIDOY", "ELENH", &athletesBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 301 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 302 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1995", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 33 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MAZARAKHS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 303 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 304 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 305 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 306 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 307 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 308 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 309 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 310 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 311 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 312 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 313 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 314 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 315 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 316 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 317 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 318 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 319 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 320 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 321 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 34 ��� ������ ATHLETES */
	insertAthlete(athleteId, "OIKONOMIDHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 322 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 323 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 324 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 325 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 326 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 327 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 328 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1988", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 3 ��� ������ EVENT */
	insertEvent(eventId, "ARSH BARVN", &eventsBlockBuf);

	/* �������� ��� �������� 35 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KASAPH", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 329 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 330 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 36 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KASTRITSH", "XARIKLEIA", &athletesBlockBuf);

	/* �������� ��� �������� 331 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 332 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 37 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSAKIRH", "ANASTASIA", &athletesBlockBuf);

	/* �������� ��� �������� 333 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 334 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 335 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 336 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 337 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 338 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 339 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 340 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 341 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 342 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 343 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 344 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 345 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 346 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 347 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 348 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 349 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 350 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1998", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 351 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 38 ��� ������ ATHLETES */
	insertAthlete(athleteId, "IVANNIDH", "XRISTINA", &athletesBlockBuf);

	/* �������� ��� �������� 352 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 353 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 354 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 355 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 356 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 357 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 358 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 359 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 360 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 361 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 362 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 363 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 364 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 39 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SAMPANHS", "LEVNIDAS", &athletesBlockBuf);

	/* �������� ��� �������� 365 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 366 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 40 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MHTROY", "BIKTVR", &athletesBlockBuf);

	/* �������� ��� �������� 367 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 368 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 369 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 370 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 371 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 41 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DHMAS", "PYRROS", &athletesBlockBuf);

	/* �������� ��� �������� 372 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 373 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 374 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 375 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 376 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 377 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 378 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 379 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 380 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 381 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 382 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 383 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 384 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 385 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 386 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 387 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 388 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 389 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 390 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 42 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MARKOYLAS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 391 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 392 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 393 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 394 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 395 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 396 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 397 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 43 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAKIASBILHS", "AKAKIOS", &athletesBlockBuf);

	/* �������� ��� �������� 398 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 399 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 400 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1998", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 401 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 402 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 403 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 404 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 405 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 406 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 407 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 44 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYRTIDHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 408 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 409 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 410 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 411 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 412 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 413 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 414 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 415 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2003", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 4 ��� ������ EVENT */
	insertEvent(eventId, "TAEKBONTO", &eventsBlockBuf);

	/* �������� ��� �������� 45 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AUANASOPOYLOY", "ARETH", &athletesBlockBuf);

	/* �������� ��� �������� 416 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 417 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 418 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 419 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 420 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 421 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 422 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 423 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 424 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 425 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 46 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MYSTAKIDOY", "ELISABET", &athletesBlockBuf);

	/* �������� ��� �������� 426 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 427 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 428 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 429 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 430 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 431 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 432 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 433 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 434 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 435 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 436 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 437 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 438 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 47 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NIKOLAIDHS", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 439 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 440 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 441 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 442 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 48 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MOYROYTSOS", "MIXALHS", &athletesBlockBuf);

	/* �������� ��� �������� 443 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 444 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 5 ��� ������ EVENT */
	insertEvent(eventId, "GYMNASTIKH", &eventsBlockBuf);

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 49 ��� ������ ATHLETES */
	insertAthlete(athleteId, "EYUYMIOY", "HLEKTRA-ELLH", &athletesBlockBuf);

	/* �������� ��� �������� 445 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 446 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 447 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 448 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 50 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAKIOY", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 449 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 450 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2001", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 451 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 452 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 453 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 454 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 455 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 456 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 457 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 51 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MAGNHSALH", "BARBARA", &athletesBlockBuf);

	/* �������� ��� �������� 458 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 459 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 52 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PANTAZH", "STERGIANH", &athletesBlockBuf);

	/* �������� ��� �������� 460 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 461 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 462 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 463 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 464 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 465 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 466 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 467 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 468 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 469 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 470 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 471 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 472 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 473 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 474 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 53 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRISTIDOY", "STYLIANH", &athletesBlockBuf);

	/* �������� ��� �������� 475 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 476 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 477 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 478 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 479 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 480 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 481 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 482 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 483 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 484 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 485 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 486 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 487 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 488 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 489 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 490 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 491 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 492 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 493 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 54 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRONOPOYLOY", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 494 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 495 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 496 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 497 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 498 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 499 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 500 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/2000", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 501 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 502 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 503 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 504 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 505 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 506 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 507 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 508 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 509 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 510 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 511 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 512 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 55 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ANDRIOLA", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 513 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 514 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 515 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 516 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 517 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 518 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 56 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PALLIDOY", "UEODVRA", &athletesBlockBuf);

	/* �������� ��� �������� 519 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 520 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 521 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 6 ��� ������ EVENT */
	insertEvent(eventId, "GYMNASTIKH TRAMPOLINO", &eventsBlockBuf);

	/* �������� ��� �������� 57 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PELIBANIDHS", "MIXAHL", &athletesBlockBuf);

	/* �������� ��� �������� 522 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 523 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 524 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 525 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 526 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 527 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 528 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 529 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 7 ��� ������ EVENT */
	insertEvent(eventId, "GYMNASTIKH ENORGANH", &eventsBlockBuf);

	/* �������� ��� �������� 58 ��� ������ ATHLETES */
	insertAthlete(athleteId, "APOSTOLIDH", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 530 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 531 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 532 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 59 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPISMPIKOY", "STEFANI", &athletesBlockBuf);

	/* �������� ��� �������� 533 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 534 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 535 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 536 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 537 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 538 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 539 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 540 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 60 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MARAS", "BLASIOS", &athletesBlockBuf);

	/* �������� ��� �������� 541 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 542 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 543 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 544 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 61 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TAMPAKOS", "DHMOSUENHS", &athletesBlockBuf);

	/* �������� ��� �������� 545 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 546 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 547 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 548 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1998", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 8 ��� ������ EVENT */
	insertEvent(eventId, "ISTIOPLOIA", &eventsBlockBuf);

	/* �������� ��� �������� 62 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPEKATVROY", "SOFIA", &athletesBlockBuf);

	/* �������� ��� �������� 549 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 550 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1999", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 551 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 552 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 553 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 554 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 555 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 556 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 557 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 558 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 559 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 560 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 561 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 63 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSOYLFA", "AIMILIA", &athletesBlockBuf);

	/* �������� ��� �������� 562 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 563 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 564 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 565 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 566 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 567 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 568 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 569 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 570 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 571 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 572 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 573 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 574 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 575 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 64 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KRABARIVTH", "BIRGINIA", &athletesBlockBuf);

	/* �������� ��� �������� 576 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 577 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1990", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 65 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FRAI", "AUHNA", &athletesBlockBuf);

	/* �������� ��� �������� 578 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 579 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 580 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 581 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 582 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 583 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 584 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 585 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 586 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 587 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 588 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 589 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 590 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 591 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 592 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 593 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 66 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GIAKOYMIDOY", "AIKATERINH", &athletesBlockBuf);

	/* �������� ��� �������� 594 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 67 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DHMHTRAKOPOYLOY", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 595 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 596 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 597 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 598 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 599 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 600 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1987", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 601 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 602 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 603 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 68 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MANTZARAKH", "EYTYXIA", &athletesBlockBuf);

	/* �������� ��� �������� 604 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1988", &participationsBlockBuf);

	/* �������� ��� �������� 605 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 606 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 607 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 608 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 609 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 610 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 611 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 612 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 613 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 614 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 615 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 616 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 617 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 618 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 619 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 69 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOSMATOPOYLOS", "ANDREAS", &athletesBlockBuf);

	/* �������� ��� �������� 620 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 621 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 622 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 623 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 624 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 625 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 626 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 627 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 628 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 629 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 630 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 631 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 632 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 633 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 634 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 635 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 636 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 70 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TRIGKVNHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 637 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 638 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 639 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 640 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 641 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 642 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 643 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 644 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 71 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAXOYMAS", "AUANASIOS", &athletesBlockBuf);

	/* �������� ��� �������� 645 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 646 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 647 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 72 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PORTOSALTE", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 648 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 649 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 650 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1992", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 651 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 652 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 653 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 73 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPAUANASIOY", "AIMILIOS", &athletesBlockBuf);

	/* �������� ��� �������� 654 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 655 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 656 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 657 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 658 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 659 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 660 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 661 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 662 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 663 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 664 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 665 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 666 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 667 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 668 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 669 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 670 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 671 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 74 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XEIMVNAS", "EYAGGELOS", &athletesBlockBuf);

	/* �������� ��� �������� 672 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 673 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 674 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 675 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 676 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 677 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 678 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 679 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 680 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 681 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 682 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 683 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 684 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 75 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAKLAMANAKHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 685 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 686 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 687 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 688 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 689 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 690 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 691 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 692 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 76 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PELEKANAKHS", "LEVNIDAS", &athletesBlockBuf);

	/* �������� ��� �������� 693 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 694 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 695 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 696 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 697 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 698 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 699 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 700 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1988", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 701 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 702 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 703 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 704 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 77 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KONTOGOYRHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 705 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 706 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 707 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 708 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 709 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 710 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 711 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 712 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 713 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 714 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 715 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 716 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 717 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 78 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PASXALIDHS", "IORDANHS", &athletesBlockBuf);

	/* �������� ��� �������� 718 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 719 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 720 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 721 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 722 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 723 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 724 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 725 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 726 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 727 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 728 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 729 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 730 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 731 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 732 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 79 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GAREFHS", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 733 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 734 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 735 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 736 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 737 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 738 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 739 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 740 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 741 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 742 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 743 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 744 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 745 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 746 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1995", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 9 ��� ������ EVENT */
	insertEvent(eventId, "KANOE-KAGIAK SLALOM", &eventsBlockBuf);

	/* �������� ��� �������� 80 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FEREKIDH", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 747 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 748 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 749 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 750 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1993", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 751 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 752 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 753 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 754 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 755 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 756 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 757 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 758 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 759 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 81 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSAKMAKHS", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 760 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 761 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 762 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 763 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 764 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 765 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 766 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 767 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 768 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 769 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 770 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 771 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 772 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 773 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 774 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 775 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 776 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 777 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 82 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DHMHTRIOY", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 778 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1999", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 10 ��� ������ EVENT */
	insertEvent(eventId, "EPITRAPEZIA ANTISFAIRISH", &eventsBlockBuf);

	/* �������� ��� �������� 83 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BOLAKAKH", "ARXONTIA", &athletesBlockBuf);

	/* �������� ��� �������� 779 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 780 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 781 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 782 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 783 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 784 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 785 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 786 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 787 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 788 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 789 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 790 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 791 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 792 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 793 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 794 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 84 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MOIROY", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 795 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 796 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 797 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 798 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 799 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 800 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1995", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 801 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 802 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 85 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKIVNHS", "PANAGIVTHS", &athletesBlockBuf);

	/* �������� ��� �������� 803 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 804 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 805 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 806 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 807 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 808 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 809 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 810 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 811 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 812 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 86 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KREANGKA", "KALINIKOS", &athletesBlockBuf);

	/* �������� ��� �������� 813 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 814 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 815 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 816 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 817 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 818 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 819 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 820 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 821 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 822 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2004", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 11 ��� ������ EVENT */
	insertEvent(eventId, "IPPASIA", &eventsBlockBuf);

	/* �������� ��� �������� 87 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DEMIROPOYLOY", "AGLAIA", &athletesBlockBuf);

	/* �������� ��� �������� 823 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 824 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 825 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 826 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 827 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 828 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 829 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 830 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 831 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 832 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 833 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 834 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 835 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 836 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 88 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LEMAN", "GKERTA", &athletesBlockBuf);

	/* �������� ��� �������� 837 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 838 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 89 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SOYRLA", "ALEJANDRA", &athletesBlockBuf);

	/* �������� ��� �������� 839 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 90 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AUANASIADH", "EMMANOYELA", &athletesBlockBuf);

	/* �������� ��� �������� 840 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 841 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 842 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 843 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 844 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 845 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 846 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 847 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 848 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 91 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ROMPERSON-MYTILHNAIOY", "XANNA", &athletesBlockBuf);

	/* �������� ��� �������� 849 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 850 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 851 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 852 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 853 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 854 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 855 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 856 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 857 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 858 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 859 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 860 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 861 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 862 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 863 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 864 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 865 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 866 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 92 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSATSOY", "DANAH", &athletesBlockBuf);

	/* �������� ��� �������� 867 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 868 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 869 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 870 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 871 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 872 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 873 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 874 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 875 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 93 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ANTIKATZIDH", "MIKAELA-XAINTI", &athletesBlockBuf);

	/* �������� ��� �������� 876 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 877 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 878 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 879 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 880 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 881 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 882 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 94 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PETRHS", "ANTVNHS", &athletesBlockBuf);

	/* �������� ��� �������� 883 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 884 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 885 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 886 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 887 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 888 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 889 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 890 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 891 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 892 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 893 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 894 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 895 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 896 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 897 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 898 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1991", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 12 ��� ������ EVENT */
	insertEvent(eventId, "KANOE-KAGIAK TAXYTHTA", &eventsBlockBuf);

	/* �������� ��� �������� 95 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ALEJOPOYLOY", "AUHNA-UEODVRA", &athletesBlockBuf);

	/* �������� ��� �������� 899 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 96 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KILIGKARIDHS", "ANDREAS", &athletesBlockBuf);

	/* �������� ��� �������� 900 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1997", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 901 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 902 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 903 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 904 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 905 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 906 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 907 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2005", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 97 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPANDREOY", "APOSTOLOS", &athletesBlockBuf);

	/* �������� ��� �������� 908 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 909 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 910 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 911 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 912 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 913 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 914 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1999", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 13 ��� ������ EVENT */
	insertEvent(eventId, "KVPHLASIA", &eventsBlockBuf);

	/* �������� ��� �������� 98 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPISKITZH", "XRYSH", &athletesBlockBuf);

	/* �������� ��� �������� 915 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 916 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 917 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 918 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 919 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 920 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 921 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 922 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 99 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SAKELLARIDOY", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 923 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 924 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 925 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 926 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 927 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 100 ��� ������ ATHLETES */
	insertAthlete(athleteId, "POLYMEROS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 928 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 929 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 101 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SKIAUITHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 930 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 931 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 932 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 933 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 934 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 935 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 936 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 937 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 938 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 939 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 940 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 14 ��� ������ EVENT */
	insertEvent(eventId, "MONTERNO PENTAULO", &eventsBlockBuf);

	/* �������� ��� �������� 102 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PARTITS", "KATALIN-MPEAT", &athletesBlockBuf);

	/* �������� ��� �������� 941 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 942 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 943 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 944 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 103 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FLVROS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 945 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 946 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 947 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 948 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 949 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 950 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2001", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 951 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 952 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1990", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 15 ��� ������ EVENT */
	insertEvent(eventId, "MPEIZMPVL", &eventsBlockBuf);

	/* �������� ��� �������� 104 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DHMHTRELHS", "TZEIMS-XRISTODOYLOS", &athletesBlockBuf);

	/* �������� ��� �������� 953 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 954 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 955 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 956 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 957 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 958 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 959 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 960 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 961 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 962 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 105 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DOYROS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 963 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 964 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 965 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 966 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 967 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 968 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 969 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 970 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 971 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 972 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 973 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 974 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 975 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 976 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 977 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 978 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 979 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 980 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 981 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 982 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 106 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ZABARAS", "KLINTON", &athletesBlockBuf);

	/* �������� ��� �������� 983 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 984 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 985 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 986 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 987 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 988 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 989 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 990 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 991 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 992 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 107 ��� ������ ATHLETES */
	insertAthlete(athleteId, "OYEIN", "UEODVRAKOS", &athletesBlockBuf);

	/* �������� ��� �������� 993 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 994 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 995 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 996 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 997 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 998 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 999 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1000 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 108 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZARENT-GEVRGIOS", "UEODVROY", &athletesBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1001 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1002 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 109 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NIKOLAOS", "UEOXARHS", &athletesBlockBuf);

	/* �������� ��� �������� 1003 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1004 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1005 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1006 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1007 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1008 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1009 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1010 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1011 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1012 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1013 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 110 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KORY-ANTVNIOS", "KABOYRGIARHS", &athletesBlockBuf);

	/* �������� ��� �������� 1014 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1015 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1016 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1017 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1018 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1019 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1020 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 111 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DHMHTRIOS", "KINGKSMPOYRI", &athletesBlockBuf);

	/* �������� ��� �������� 1021 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1022 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1023 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1024 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1025 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1026 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1027 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1028 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1029 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1030 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1031 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1032 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1033 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1034 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1035 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1036 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1037 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1038 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 112 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ROMPERT-REIMONT", "KOTTARAS", &athletesBlockBuf);

	/* �������� ��� �������� 1039 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1040 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1041 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1042 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1043 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1044 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1045 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1046 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1047 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/2000", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 113 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GEVRGIOS", "KOYTSANTVNAKHS", &athletesBlockBuf);

	/* �������� ��� �������� 1048 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1049 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1050 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 114 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MIXAHL", "KREMMYDAS", &athletesBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1051 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1052 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1053 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1054 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1055 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1056 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1057 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1058 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1059 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1060 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1061 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1062 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1063 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1064 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1065 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1066 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1067 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1068 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1069 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1070 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 115 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ALEJANDROS", "MAHSTRALHS", &athletesBlockBuf);

	/* �������� ��� �������� 1071 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1072 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 116 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PHTER", "GKAS", &athletesBlockBuf);

	/* �������� ��� �������� 1073 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1074 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1075 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1076 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1077 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1078 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1079 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1080 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1081 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1082 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1083 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1084 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1085 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 117 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MARKAKHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 1086 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1087 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1088 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1089 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1090 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1091 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1092 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1093 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 118 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MELEXES", "MELETI", &athletesBlockBuf);

	/* �������� ��� �������� 1094 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1095 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1096 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1097 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1098 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1099 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1100 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2003", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1101 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1102 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1103 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 119 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ROSS", "MPELINTZER", &athletesBlockBuf);

	/* �������� ��� �������� 1104 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1105 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1106 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1107 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1108 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1109 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1110 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1111 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1112 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1113 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1114 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1115 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1116 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1117 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1118 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1119 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1120 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1121 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 120 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KLEHTON", "MPOYRAS", &athletesBlockBuf);

	/* �������� ��� �������� 1122 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1123 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1124 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1125 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1126 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1127 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1128 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1129 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1130 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1131 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1132 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1133 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 121 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPRANTLH", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 1134 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1135 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1136 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1137 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1138 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1139 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1140 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1141 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1142 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1143 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1144 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1145 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1146 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 122 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPRAK", "ANDREAS-TZEHMS", &athletesBlockBuf);

	/* �������� ��� �������� 1147 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 123 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPALYMPERHS", "ERIK-NTANIEL", &athletesBlockBuf);

	/* �������� ��� �������� 1148 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1149 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1150 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1151 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1152 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1153 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1154 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 124 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ROMPINSON", "XRISTOFOROS", &athletesBlockBuf);

	/* �������� ��� �������� 1155 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1156 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1157 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1158 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1159 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1160 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1161 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1162 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1163 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1164 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 125 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SPANOS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1165 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1166 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1167 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 126 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SPENSER", "SVN", &athletesBlockBuf);

	/* �������� ��� �������� 1168 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1169 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1170 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1171 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1172 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1173 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1174 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1175 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1176 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 127 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZEIMS", "SYKARAS", &athletesBlockBuf);

	/* �������� ��� �������� 1177 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1178 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1179 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1180 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1181 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1182 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1183 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1184 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1185 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1186 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1187 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1188 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1189 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1190 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1191 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1192 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1193 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1194 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1195 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 128 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PANAGIVTHS", "SVTHROPOYLOS", &athletesBlockBuf);

	/* �������� ��� �������� 1196 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1197 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1198 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1199 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1200 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1987", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1201 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1202 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1203 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1204 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1205 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1206 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1207 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1208 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1209 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1210 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1211 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1212 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1213 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1214 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1215 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1989", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 129 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PANAGIVTHS", "XAISLER", &athletesBlockBuf);

	/* �������� ��� �������� 1216 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1217 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1218 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1219 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1220 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1221 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1222 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1993", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 16 ��� ������ EVENT */
	insertEvent(eventId, "KATADYSEIS", &eventsBlockBuf);

	/* �������� ��� �������� 130 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPPA-PAPABASILOPOYLOY", "EYTYXIA", &athletesBlockBuf);

	/* �������� ��� �������� 1223 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1224 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1225 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1226 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1227 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1228 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1229 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1230 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 131 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SFAKIANOY", "FLVRENTIA", &athletesBlockBuf);

	/* �������� ��� �������� 1231 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1232 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 132 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GEVRGATOY", "DIAMANTINA", &athletesBlockBuf);

	/* �������� ��� �������� 1233 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1234 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1235 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1236 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1237 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1238 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1239 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1240 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1241 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1242 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1243 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1244 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1245 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1246 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1247 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1248 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1249 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1250 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1990", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1251 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1252 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 133 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYTSOPETROY", "SVTHRIA", &athletesBlockBuf);

	/* �������� ��� �������� 1253 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1254 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1255 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1256 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1257 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1258 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1259 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1260 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1261 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1262 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 134 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GABRIHLIDHS", "IVANNHS", &athletesBlockBuf);

	/* �������� ��� �������� 1263 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1264 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1265 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1266 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1267 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1268 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1269 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1270 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1271 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1272 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1273 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1274 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1275 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1276 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1277 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1278 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1279 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1280 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1281 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 135 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TRAKAS", "SVTHRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1282 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1283 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1284 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1285 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1286 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1287 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1288 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1289 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1290 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1291 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1292 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 136 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPIMHS", "UVMAS", &athletesBlockBuf);

	/* �������� ��� �������� 1293 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1294 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1295 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1296 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1297 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1298 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1299 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1300 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1991", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1301 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1302 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1303 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1304 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1305 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1306 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1307 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 137 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SIRANIDHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 1308 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1309 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1310 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1311 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1312 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2001", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �� ����� ��� ������� EVENTS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(eventsFd, eventsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on EVENTS.");

	/* �������� ��� ��� ����� ��� �� ������ EVENTS. */
	callAllocBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf, "EVENTS");

	/* �������� ��� �������� 17 ��� ������ EVENT */
	insertEvent(eventId, "KOLYMBHSH", &eventsBlockBuf);

	/* �������� ��� �������� 138 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KABARNOY", "EIRHNH", &athletesBlockBuf);

	/* �������� ��� �������� 1313 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 139 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SARAKATSANH", "AIKATERINH", &athletesBlockBuf);

	/* �������� ��� �������� 1314 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1315 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1316 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1317 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1318 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1319 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1320 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1321 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1322 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1323 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1324 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1325 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1326 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1327 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1328 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1329 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1330 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 140 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARASTERGIOY", "EIRHNH", &athletesBlockBuf);

	/* �������� ��� �������� 1331 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1332 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1333 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1334 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1335 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1336 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1337 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1338 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1339 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 141 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DHMOSXAKH", "ZVH", &athletesBlockBuf);

	/* �������� ��� �������� 1340 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1341 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1342 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1343 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1344 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1345 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1346 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1347 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1348 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 142 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AGGELOPOYLOY", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 1349 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1350 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2004", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1351 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1352 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1353 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1354 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1355 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1356 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1357 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1358 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1359 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1360 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1361 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 143 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZABELLA", "AUHNA", &athletesBlockBuf);

	/* �������� ��� �������� 1362 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1363 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1364 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1365 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1366 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1367 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1368 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1369 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1370 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1371 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1372 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 144 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KVSTA", "EIRHNH", &athletesBlockBuf);

	/* �������� ��� �������� 1373 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1374 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1375 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1376 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1377 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1378 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1379 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1999", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 145 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KVSTH", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 1380 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1381 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1382 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1383 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1384 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1385 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1386 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1387 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1388 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1389 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1390 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1391 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1392 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1393 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1394 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1395 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 146 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MAXAIRA", "ANTVNIA", &athletesBlockBuf);

	/* �������� ��� �������� 1396 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1397 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1398 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1399 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1400 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1990", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1401 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1402 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1403 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1404 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1405 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1406 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1407 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1408 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1409 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1410 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1411 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1412 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 147 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MANVLH", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 1413 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1414 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1415 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1416 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1417 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1418 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1419 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 148 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSAGKA", "EYAGGELIA", &athletesBlockBuf);

	/* �������� ��� �������� 1420 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1421 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1422 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1423 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 149 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MATSA", "MARUA", &athletesBlockBuf);

	/* �������� ��� �������� 1424 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1425 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1426 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1427 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1428 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1429 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1430 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1431 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1432 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1433 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1434 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1435 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1436 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1437 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1438 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1439 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 150 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NIANGKOYARA", "NERY-MANTEY", &athletesBlockBuf);

	/* �������� ��� �������� 1440 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1441 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1442 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1443 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1444 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1445 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1446 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1447 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1448 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1449 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1450 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/2002", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1451 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1452 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1453 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1454 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1455 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 151 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LYMPERTA", "MARIANNA", &athletesBlockBuf);

	/* �������� ��� �������� 1456 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1457 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1458 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1459 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1460 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1461 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1462 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1463 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1464 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1465 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1466 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 152 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GRHGORIADHS", "ARISTEIDHS", &athletesBlockBuf);

	/* �������� ��� �������� 1467 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1468 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1469 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1470 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1471 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1472 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1473 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1474 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1475 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1476 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 153 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PASTRAS", "SVTHRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1477 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1478 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1479 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1480 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1481 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1482 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1483 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 154 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOS", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 1484 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1485 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1486 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 155 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DIAMANTIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1487 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1488 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1489 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1490 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1491 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1492 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1493 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1494 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1495 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1496 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1497 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1498 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1499 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1500 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1988", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1501 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 156 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ZHSIMOS", "ANDREAS", &athletesBlockBuf);

	/* �������� ��� �������� 1502 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1503 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1504 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1505 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1506 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1507 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1508 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1509 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1510 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1511 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1512 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1513 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1514 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1515 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1516 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 157 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOKKVDHS", "IVANNHS", &athletesBlockBuf);

	/* �������� ��� �������� 1517 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1518 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1519 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1520 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1521 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1522 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1523 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1524 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1525 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1526 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1527 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1528 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 158 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DRYMVNAKOS", "IVANNHS", &athletesBlockBuf);

	/* �������� ��� �������� 1529 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1530 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1531 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1532 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1533 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1534 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1535 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1536 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1537 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1538 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1539 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1540 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1541 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1542 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1543 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1544 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1545 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1546 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1547 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1548 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 159 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ALYFANTHS", "RVMANOS-IASVN", &athletesBlockBuf);

	/* �������� ��� �������� 1549 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1550 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1998", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1551 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1552 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 160 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKIOYLMPAS", "ANTVNIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1553 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1554 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1555 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1556 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1557 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1558 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1559 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1560 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1561 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1562 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1563 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1564 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1565 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1566 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1567 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1568 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1569 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1570 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1571 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1572 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2005", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 161 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GIANNIVTHS", "SPYRIDVN", &athletesBlockBuf);

	/* �������� ��� �������� 1573 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1574 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1575 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1576 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1577 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1578 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1579 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1580 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1581 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1582 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1583 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1584 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1585 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1586 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1587 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1588 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1589 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1590 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 162 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MAGGANAS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1591 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1592 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1593 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1594 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1595 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1596 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1597 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 163 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPITSAKHS", "SPYRIDVN", &athletesBlockBuf);

	/* �������� ��� �������� 1598 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1599 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1600 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1989", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1601 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1602 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1603 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1604 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1605 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1606 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 164 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSOLTOS", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 1607 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 165 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ANTVNOPOYLOS", "APOSTOLOS", &athletesBlockBuf);

	/* �������� ��� �������� 1608 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1609 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1610 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1611 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 166 ��� ������ ATHLETES */
	insertAthlete(athleteId, "JYLOYRHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 1612 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1613 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1614 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1615 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1616 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1617 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1618 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1619 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1620 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1621 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 167 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSAGKARAKHS", "APOSTOLOS", &athletesBlockBuf);

	/* �������� ��� �������� 1622 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1623 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1624 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1625 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1626 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1627 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1628 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1629 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1630 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 18 ��� ������ EVENT */
	insertEvent(eventId, "PALH ELEYUERA", &eventsBlockBuf);

	/* �������� ��� �������� 168 ��� ������ ATHLETES */
	insertAthlete(athleteId, "CAUA", "FANH", &athletesBlockBuf);

	/* �������� ��� �������� 1631 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1632 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1633 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1634 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1635 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1636 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1637 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1638 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1639 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1640 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 169 ��� ������ ATHLETES */
	insertAthlete(athleteId, "POYMPOYRIDOY", "SOFIA", &athletesBlockBuf);

	/* �������� ��� �������� 1641 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1642 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1643 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1644 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1645 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1646 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1647 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1648 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1649 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1650 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1651 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1652 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1653 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1654 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1655 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 170 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ZYGOYRH", "STAYROYLA", &athletesBlockBuf);

	/* �������� ��� �������� 1656 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1657 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1658 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1659 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1660 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1661 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1662 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1663 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1664 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 171 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BRYVNH", "MARIA-LOYIZA", &athletesBlockBuf);

	/* �������� ��� �������� 1665 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1666 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1667 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1668 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1669 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1670 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 172 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPATZELAS", "NESTVRAS", &athletesBlockBuf);

	/* �������� ��� �������� 1671 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1672 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1673 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1674 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1675 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1676 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1677 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1678 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1679 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1680 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1681 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1682 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1683 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1684 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1685 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1686 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1687 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 173 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARNTANOB", "AMIRAN", &athletesBlockBuf);

	/* �������� ��� �������� 1688 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1689 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1690 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1691 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1692 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1693 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1694 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1695 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1696 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1697 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1698 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1699 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 174 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ASLANASBILI", "MPESIK", &athletesBlockBuf);

	/* �������� ��� �������� 1700 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2004", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1701 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1702 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1703 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1704 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1705 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1706 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1707 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1708 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1709 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1710 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1711 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1712 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1713 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1714 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1715 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1716 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1717 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1718 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 175 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TASKOYDHS", "APOSTOLOS", &athletesBlockBuf);

	/* �������� ��� �������� 1719 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1720 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1721 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 176 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPETINIDHS", "EMZARIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1722 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1723 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1724 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1725 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1726 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1727 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1728 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1729 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1730 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1731 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1732 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1733 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1992", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 177 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LOIZIDHS", "LAZAROS", &athletesBlockBuf);

	/* �������� ��� �������� 1734 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1735 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1736 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1737 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1738 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1739 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1740 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1741 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1742 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1743 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1744 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1745 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1746 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 178 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LALIVTHS", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 1747 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1748 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1749 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1750 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1997", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1751 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1752 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1753 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1754 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1755 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1756 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1757 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1758 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1759 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1760 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1761 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1762 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1988", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 19 ��� ������ EVENT */
	insertEvent(eventId, "PALH ELLHNORVMAIKH", &eventsBlockBuf);

	/* �������� ��� �������� 179 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYTSIOYMPAS", "JENOFVN", &athletesBlockBuf);

	/* �������� ��� �������� 1763 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1764 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1765 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1766 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1767 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1768 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1769 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1770 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1771 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1772 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1773 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1774 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1775 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1776 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1777 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1778 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1779 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 180 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KIOYREGKIAN", "ARTIOM", &athletesBlockBuf);

	/* �������� ��� �������� 1780 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1781 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1782 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1783 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1784 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1785 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1786 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1787 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1788 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1789 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1790 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1791 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1792 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1793 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1794 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 181 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKIKAS", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 1795 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1796 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1797 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1798 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1799 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1800 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1993", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1801 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1802 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1803 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1804 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1805 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1806 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1807 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 182 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ARKOYDEAS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 1808 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1809 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1810 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1811 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1812 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1813 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1814 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1815 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 183 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOLITSOPOYLOS", "ALEJIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1816 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1817 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1818 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1819 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 184 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ABRAMHS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1820 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1821 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1822 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1823 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1824 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1825 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1826 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1827 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1828 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1829 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1830 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1831 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 185 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UANOS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 1832 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1833 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1834 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1835 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1836 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1837 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1838 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1839 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1840 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1841 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1842 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1843 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1844 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1845 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 20 ��� ������ EVENT */
	insertEvent(eventId, "PETOSFAIRISH", &eventsBlockBuf);

	/* �������� ��� �������� 186 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BLAXOY", "IVANNA", &athletesBlockBuf);

	/* �������� ��� �������� 1846 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1847 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1848 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1849 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1850 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2005", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1851 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1852 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1853 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1854 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1855 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1856 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1857 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1858 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1859 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1860 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 187 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKARAGKOYNH", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 1861 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1862 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1863 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1864 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1865 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1866 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1867 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1868 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1869 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1870 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1871 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1872 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1873 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1874 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1875 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1876 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1877 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1878 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 188 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKARAGKOYNH", "NIKH", &athletesBlockBuf);

	/* �������� ��� �������� 1879 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1880 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 189 ��� ������ ATHLETES */
	insertAthlete(athleteId, "IORDANIDOY", "SOFIA", &athletesBlockBuf);

	/* �������� ��� �������� 1881 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1882 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1883 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1884 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1885 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1886 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1887 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 190 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KIOSH", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 1888 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1889 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1890 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1891 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1892 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1893 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 191 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MEMETZH", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 1894 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1895 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1896 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1897 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1898 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1899 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1900 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1991", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1901 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1902 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1903 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 192 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NTOYMITRESKOY", "ROYJANTRA-KONTROYTSA", &athletesBlockBuf);

	/* �������� ��� �������� 1904 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1905 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1906 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1907 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1908 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1909 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1910 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1911 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1912 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1913 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1914 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1915 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1916 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1917 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/2005", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 193 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPAZOGLOY", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 1918 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1919 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1920 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1921 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1922 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1923 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1924 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1925 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1926 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1927 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1928 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1929 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1930 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 194 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PRONIADOY", "ZANNA", &athletesBlockBuf);

	/* �������� ��� �������� 1931 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1932 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1933 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1934 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1935 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1936 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1937 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1938 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1939 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1940 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 195 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SAKKOYLA", "XARIKLEIA", &athletesBlockBuf);

	/* �������� ��� �������� 1941 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1942 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1943 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1944 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1945 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1946 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1947 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1948 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1949 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1950 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1988", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 1951 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1952 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1953 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1954 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1955 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1956 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1957 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1958 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 196 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZANAKAKH", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 1959 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1960 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1961 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1962 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1963 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1964 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 1965 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 1966 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 1967 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1968 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1969 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 197 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XATZHNIKOY", "ELEYUERIA", &athletesBlockBuf);

	/* �������� ��� �������� 1970 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 198 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKIOYRDAS", "MARIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1971 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1972 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 1973 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 1974 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1975 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 1976 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1977 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 199 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYRNETAS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 1978 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 1979 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1980 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1981 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 1982 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1983 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 200 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KRABARIK", "ANTREI", &athletesBlockBuf);

	/* �������� ��� �������� 1984 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1985 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1986 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 201 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LAPPAS", "HLIAS", &athletesBlockBuf);

	/* �������� ��� �������� 1987 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 1988 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 1989 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 1990 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 1991 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 1992 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 1993 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 1994 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 1995 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 1996 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 1997 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 1998 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 1999 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2000 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1999", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2001 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2002 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 202 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPAEF", "TONTOR-ZLATKOB", &athletesBlockBuf);

	/* �������� ��� �������� 2003 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2004 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2005 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2006 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2007 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2008 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2009 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2010 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2011 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2012 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 203 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PANTALEVN", "SVTHRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2013 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2014 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2015 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2016 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2017 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2018 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 204 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PROYSALHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 2019 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2020 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2021 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2022 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2023 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2024 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2025 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2026 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2027 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2028 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2029 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2030 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 205 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ROYMELIVTHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 2031 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2032 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2033 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2034 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 206 ��� ������ ATHLETES */
	insertAthlete(athleteId, "STEFANOY", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2035 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2036 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2037 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 207 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSAKIROPOYLOS", "ANTVNIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2038 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2039 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2040 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2041 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2042 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2043 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2044 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2045 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2046 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2047 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2048 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2049 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2050 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2051 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2052 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 208 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XATZHANTVNIOY", "UEODVROS", &athletesBlockBuf);

	/* �������� ��� �������� 2053 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2054 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2055 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2056 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2057 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2058 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2059 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2060 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2061 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2062 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2063 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2064 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2065 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2066 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2067 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2068 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2069 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2070 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2071 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2004", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 209 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRISTOFIDELHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 2072 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2073 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2074 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2075 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2004", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 21 ��� ������ EVENT */
	insertEvent(eventId, "MPITS BOLLEY", &eventsBlockBuf);

	/* �������� ��� �������� 210 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ARBANITH", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 2076 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2077 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2078 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2079 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2080 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2081 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2082 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2083 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2084 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2085 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2086 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2087 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2088 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2089 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2090 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2091 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2092 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 211 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARANTASIOY", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 2093 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2094 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2095 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2096 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2097 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2098 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2099 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2100 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/2000", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2101 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2102 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2103 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 212 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYTROYMANIDOY", "EYUALIA", &athletesBlockBuf);

	/* �������� ��� �������� 2104 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2105 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2106 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2107 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2108 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2109 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2110 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2111 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2112 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2113 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2114 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2115 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2116 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2117 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2118 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2119 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2120 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 213 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SFYRH", "EYFROSYNH", &athletesBlockBuf);

	/* �������� ��� �������� 2121 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2122 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2123 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 214 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MIXALOPOYLOS", "AUANASIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2124 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2125 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2126 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2127 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2128 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2129 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2130 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2131 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2132 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 215 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPELIGRATHS", "PAYLOS", &athletesBlockBuf);

	/* �������� ��� �������� 2133 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2134 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 22 ��� ������ EVENT */
	insertEvent(eventId, "JIFASKIA", &eventsBlockBuf);

	/* �������� ��� �������� 216 ��� ������ ATHLETES */
	insertAthlete(athleteId, "RENTOYMH", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 2135 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2136 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2137 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2138 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2139 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2140 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2141 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2142 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2143 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2144 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2145 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2146 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2147 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2148 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2149 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2150 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1987", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2151 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2152 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2153 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 217 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MAGKANOYDAKH", "DHMHTRA", &athletesBlockBuf);

	/* �������� ��� �������� 2154 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2155 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2156 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2157 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2158 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2159 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2160 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2161 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2162 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2163 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2164 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2165 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 218 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SIDHROPOYLOY", "NIKH-KATERINA", &athletesBlockBuf);

	/* �������� ��� �������� 2166 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2167 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2168 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2169 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2170 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2171 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2172 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2173 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2174 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2175 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2176 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2177 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2178 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2179 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2180 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2181 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 219 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRHSTOY", "IVANNA", &athletesBlockBuf);

	/* �������� ��� �������� 2182 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2183 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2184 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2185 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2186 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2187 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2188 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2189 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2190 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2191 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2192 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2193 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2194 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2195 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2196 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2197 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 220 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AMPALOB", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2198 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2199 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2200 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1988", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2201 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2202 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2203 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2204 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2205 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2206 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2207 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 221 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MANETAS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 2208 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2209 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2210 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2211 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2212 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2213 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2214 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2215 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2216 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2217 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2218 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2219 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 222 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPASMATZIAN", "MARIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2220 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2221 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2222 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2223 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2224 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2225 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2226 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 223 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NTOYRAKOS", "TZEHSON-MAIKL", &athletesBlockBuf);

	/* �������� ��� �������� 2227 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2228 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2229 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2230 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2231 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2232 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 23 ��� ������ EVENT */
	insertEvent(eventId, "PODHLASIA OREINH", &eventsBlockBuf);

	/* �������� ��� �������� 224 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KVTOYLAS", "EMMANOYHL", &athletesBlockBuf);

	/* �������� ��� �������� 2233 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2234 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2235 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2236 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2237 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2238 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2239 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1989", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 24 ��� ������ EVENT */
	insertEvent(eventId, "PODOSFAIRO", &eventsBlockBuf);

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 225 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GIATRAKOY", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 2240 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 226 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KABBADA", "ALEJANDRA", &athletesBlockBuf);

	/* �������� ��� �������� 2241 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2242 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2243 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2244 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2245 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2246 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2247 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2248 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2249 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2250 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2002", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2251 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2252 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2253 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 227 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KALYBA", "TANYA", &athletesBlockBuf);

	/* �������� ��� �������� 2254 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2255 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2256 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2257 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2258 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2259 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2260 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2261 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2262 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 228 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ELENH", "KATSAITH", &athletesBlockBuf);

	/* �������� ��� �������� 2263 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2264 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2265 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2266 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2267 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2268 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2269 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2270 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2271 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2272 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2273 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2274 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2275 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2276 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2277 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2278 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2279 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 229 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KVNSTANTINA", "LAGOYMTZH", &athletesBlockBuf);

	/* �������� ��� �������� 2280 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2281 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2282 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2283 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2284 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2285 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2286 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2287 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2288 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2289 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2290 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2291 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 230 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AGGELIKH", "LAZAROY", &athletesBlockBuf);

	/* �������� ��� �������� 2292 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2293 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2294 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2295 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 231 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MARIA", "LOSENO", &athletesBlockBuf);

	/* �������� ��� �������� 2296 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2297 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2298 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2299 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2300 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1992", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2301 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2302 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2303 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2304 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2305 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2306 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2307 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2308 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2309 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2310 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2311 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2312 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 232 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GOYOLKER", "AMAL", &athletesBlockBuf);

	/* �������� ��� �������� 2313 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2314 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2315 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2316 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2317 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2318 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2319 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2320 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2321 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2322 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 233 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MIXAHLIDOY", "EYTYXIA", &athletesBlockBuf);

	/* �������� ��� �������� 2323 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2324 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2325 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2326 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 234 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MOSXOY", "ILHANA", &athletesBlockBuf);

	/* �������� ��� �������� 2327 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2328 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2329 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2330 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2331 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2332 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2333 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2334 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2335 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2336 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2337 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 235 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPENSON", "ELENH-MARI", &athletesBlockBuf);

	/* �������� ��� �������� 2338 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2339 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2340 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2341 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2342 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2343 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2344 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2345 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2346 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2347 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2348 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2349 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 236 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PANTELEIADOY", "DHMHTRA", &athletesBlockBuf);

	/* �������� ��� �������� 2350 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1991", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2351 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2352 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2353 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2354 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2355 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2356 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2357 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2358 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2359 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2360 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2361 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2362 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2363 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2364 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 237 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOY", "ANASTASIA", &athletesBlockBuf);

	/* �������� ��� �������� 2365 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2366 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2367 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2368 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2369 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2370 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2371 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2372 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2373 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2374 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2375 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2376 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2377 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2378 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2379 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2380 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2381 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2382 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2383 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2384 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 238 ��� ������ ATHLETES */
	insertAthlete(athleteId, "POYRIDOY", "AUANASIA", &athletesBlockBuf);

	/* �������� ��� �������� 2385 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 239 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SMIU", "SOFIA-ANTVNIA", &athletesBlockBuf);

	/* �������� ��� �������� 2386 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2387 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2388 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2389 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2390 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2391 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2392 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2393 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2394 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2395 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2396 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2397 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2398 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2399 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 240 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SOYPIADOY", "BASILIKH", &athletesBlockBuf);

	/* �������� ��� �������� 2400 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1990", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2401 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2402 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2403 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2404 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2405 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2406 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2407 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2408 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2409 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2410 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2411 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2412 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2413 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2414 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2415 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2416 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1997", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 241 ��� ������ ATHLETES */
	insertAthlete(athleteId, "STRATAKH", "KALLIOPH", &athletesBlockBuf);

	/* �������� ��� �������� 2417 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2418 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2419 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2420 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2421 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2422 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2423 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2424 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2425 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 242 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TEFANH", "AGGELIKH", &athletesBlockBuf);

	/* �������� ��� �������� 2426 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2427 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2428 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2429 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2430 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2431 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2432 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2433 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 243 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XATZHGIANNIDOY", "NATALIA", &athletesBlockBuf);

	/* �������� ��� �������� 2434 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2435 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2436 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2437 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2438 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2439 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2440 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2441 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2442 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2443 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2444 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2445 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2446 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2447 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2448 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2449 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2450 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2002", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2451 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 244 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AGRITHS", "ANASTASIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2452 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2453 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2454 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2455 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2456 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2457 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2458 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2459 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2460 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2461 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2462 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2463 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2464 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2465 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2466 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2467 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2468 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 245 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AMANATIDHS", "IVANNHS", &athletesBlockBuf);

	/* �������� ��� �������� 2469 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2470 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2471 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2472 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2473 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2474 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2475 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2476 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2477 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2478 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2479 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2480 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 246 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AMPARHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2481 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2482 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2483 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2484 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2485 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2486 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2487 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 247 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BALLAS", "SPYRIDVN", &athletesBlockBuf);

	/* �������� ��� �������� 2488 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2489 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2490 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2491 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2492 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2493 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2494 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2495 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2496 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2497 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2498 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2499 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2500 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1993", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2501 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2502 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2503 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2504 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 248 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BYNTRA", "LOYKAS", &athletesBlockBuf);

	/* �������� ��� �������� 2505 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2506 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2507 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2508 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2509 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2510 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2511 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2512 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2513 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 249 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GALANOPOYLOS", "ARISTEIDHS", &athletesBlockBuf);

	/* �������� ��� �������� 2514 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2515 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2516 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2517 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2518 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2519 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2520 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2521 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2522 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2523 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2524 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2525 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 250 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GIANNOY", "KLEOPAS", &athletesBlockBuf);

	/* �������� ��� �������� 2526 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2527 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2528 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2529 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 251 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GOYNDOYLAKHS", "FANOYRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2530 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2531 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 252 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARYPIDHS", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 2532 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2533 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2534 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2535 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 253 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LAGOS", "PANAGIVTHS", &athletesBlockBuf);

	/* �������� ��� �������� 2536 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2537 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2538 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2539 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2540 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2541 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2542 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2543 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2544 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2545 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2546 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2547 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2548 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2549 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2550 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2004", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2551 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2552 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2553 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2554 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 254 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MORAS", "EYAGGELOS", &athletesBlockBuf);

	/* �������� ��� �������� 2555 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2556 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2557 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2558 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 255 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NEMPEGLERAS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 2559 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2560 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2561 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2562 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2563 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2564 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 256 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2565 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2566 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2567 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2568 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2569 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2570 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2571 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2572 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2573 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2574 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2575 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2576 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2003", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 257 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SALPIGGIDHS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2577 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2578 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2579 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2580 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2581 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2582 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2583 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2584 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2585 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2586 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2587 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2588 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2589 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2590 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2591 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 258 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SAPANHS", "MILTIADHS", &athletesBlockBuf);

	/* �������� ��� �������� 2592 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2593 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2594 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2595 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2596 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2597 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2598 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2599 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2600 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2004", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2601 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 259 ��� ������ ATHLETES */
	insertAthlete(athleteId, "STOLTIDHS", "IEROKLHS", &athletesBlockBuf);

	/* �������� ��� �������� 2602 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 260 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TARALIDHS", "IVANNHS", &athletesBlockBuf);

	/* �������� ��� �������� 2603 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2604 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2605 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2606 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2607 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 261 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FVTAKHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2608 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2609 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2610 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2611 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2612 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2613 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1992", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 25 ��� ������ EVENT */
	insertEvent(eventId, "PYGMAXIA", &eventsBlockBuf);

	/* �������� ��� �������� 262 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAPERVNHS", "MARIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2614 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2615 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2616 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2617 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2618 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2619 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2620 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2621 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 263 ��� ������ ATHLETES */
	insertAthlete(athleteId, "IVANNIDHS", "SPYRIDVN", &athletesBlockBuf);

	/* �������� ��� �������� 2622 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2623 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2624 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2625 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2626 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2627 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2628 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2629 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 264 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOTAKOS", "UEODVROS", &athletesBlockBuf);

	/* �������� ��� �������� 2630 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2631 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 265 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GAZHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2632 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2633 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2634 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2635 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2636 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2637 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2638 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2639 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2640 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2641 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2642 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2643 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2644 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2645 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2646 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 266 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAYLIDHS", "HLIAS", &athletesBlockBuf);

	/* �������� ��� �������� 2647 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2648 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2649 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2650 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1994", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2651 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2652 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2653 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 267 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KLADOYXAS", "SPYRIDVN", &athletesBlockBuf);

	/* �������� ��� �������� 2654 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2655 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2656 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2657 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2658 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2659 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2660 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2661 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2662 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2663 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2664 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2665 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2666 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2667 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2668 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2669 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2670 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2671 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2672 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2673 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1995", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 26 ��� ������ EVENT */
	insertEvent(eventId, "SKOPOBOLH", &eventsBlockBuf);

	/* �������� ��� �������� 268 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARAFLOY", "MARINA", &athletesBlockBuf);

	/* �������� ��� �������� 2674 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2675 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2676 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2677 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2678 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2679 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 269 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SMYRLH", "ALEJIA", &athletesBlockBuf);

	/* �������� ��� �������� 2680 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2681 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2682 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2683 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2684 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2685 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2686 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2687 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2688 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 270 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FAKA", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 2689 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2690 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2691 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2692 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2693 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2694 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 271 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KASOYMH", "AGAUH", &athletesBlockBuf);

	/* �������� ��� �������� 2695 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2696 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2697 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2698 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2699 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2700 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1992", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2701 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2702 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2703 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 272 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GEVRGAKOPOYLOS", "DIONYSIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2704 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2705 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2706 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2707 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2708 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2709 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2710 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2711 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2712 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2713 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2714 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2004", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 273 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PETSANHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2715 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2716 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2717 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2718 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2719 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2720 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2721 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2722 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2723 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2724 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2725 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2726 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2727 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2728 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2729 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2730 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2731 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2732 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2733 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 274 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SABORGIANNAKHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 2734 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2735 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2736 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2737 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2738 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2739 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2740 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 275 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SPYROPOYLOS", "AGGELOS", &athletesBlockBuf);

	/* �������� ��� �������� 2741 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2742 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2743 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2744 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2745 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2746 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2747 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2748 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2749 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 276 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LIOGRHS", "EYAGGELOS", &athletesBlockBuf);

	/* �������� ��� �������� 2750 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1987", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2751 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2752 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 277 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SALABANTAKHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 2753 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2754 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2755 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2756 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2757 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2758 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2759 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2760 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2761 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2762 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2763 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2764 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2765 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2766 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2767 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2768 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2769 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 278 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ANTVNIADHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 2770 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2771 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2772 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2773 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2774 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2775 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2776 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2777 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2778 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2779 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1996", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 27 ��� ������ EVENT */
	insertEvent(eventId, "SYGXRONISMENH KOLYMBHSH", &eventsBlockBuf);

	/* �������� ��� �������� 279 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ANASTASIOY", "AGLAIA", &athletesBlockBuf);

	/* �������� ��� �������� 2780 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2781 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2782 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2783 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2784 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2785 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2786 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2787 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2788 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 280 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GEVRGIOY", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 2789 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2790 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2791 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2792 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2793 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2794 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2795 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2796 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2797 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2798 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2799 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2800 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1992", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2801 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2802 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2803 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2804 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 281 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GOYDA", "EYFROSYNH", &athletesBlockBuf);

	/* �������� ��� �������� 2805 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2806 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2807 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2808 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2809 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2810 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2811 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2812 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2813 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 282 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UALASSINIDOY", "XRISTINA", &athletesBlockBuf);

	/* �������� ��� �������� 2814 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2815 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2816 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2817 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 283 ��� ������ ATHLETES */
	insertAthlete(athleteId, "IVANNOY", "APOSTOLIA", &athletesBlockBuf);

	/* �������� ��� �������� 2818 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2819 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2820 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 284 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYTSOYDH", "EYGENIA", &athletesBlockBuf);

	/* �������� ��� �������� 2821 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2822 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2823 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2824 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2825 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2826 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2827 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2828 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2829 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2830 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2831 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2832 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2833 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2834 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2835 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2836 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2837 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2838 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2839 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 285 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PELEKANOY", "OLGA", &athletesBlockBuf);

	/* �������� ��� �������� 2840 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2841 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2842 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2843 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 286 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FTOYLH", "ELEYUERIA", &athletesBlockBuf);

	/* �������� ��� �������� 2844 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 287 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRISTODOYLOY", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 2845 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2846 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2847 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2848 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 28 ��� ������ EVENT */
	insertEvent(eventId, "SOFTMPVL", &eventsBlockBuf);

	/* �������� ��� �������� 288 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GEVRGANTA", "TZHNNY", &athletesBlockBuf);

	/* �������� ��� �������� 2849 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2850 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1989", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2851 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2852 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1998", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 289 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MARI", "GKEIL", &athletesBlockBuf);

	/* �������� ��� �������� 2853 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2854 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2855 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2856 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2857 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2858 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2859 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2860 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2861 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 290 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZOANNA", "ANTALI", &athletesBlockBuf);

	/* �������� ��� �������� 2862 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2863 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2864 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 291 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KANELAKH-KLOOYZMAN", "XLOH", &athletesBlockBuf);

	/* �������� ��� �������� 2865 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2866 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2867 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2868 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2869 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2870 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2871 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2872 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2873 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 292 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MARIA", "KARANTZA", &athletesBlockBuf);

	/* �������� ��� �������� 2874 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2875 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2876 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2877 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2878 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2879 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2880 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2881 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2882 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2883 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2884 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2885 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2886 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2887 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 293 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRISTINA", "KOYTOYGKOY", &athletesBlockBuf);

	/* �������� ��� �������� 2888 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2889 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2890 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2891 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2892 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2893 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2894 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2895 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2896 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2897 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2898 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2899 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2900 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1996", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2901 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2902 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2903 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2904 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 294 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AIKATERINH", "KROMYDA", &athletesBlockBuf);

	/* �������� ��� �������� 2905 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2906 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2907 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2908 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2909 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2910 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2911 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2912 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2913 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2914 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2915 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2916 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2917 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2918 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2919 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2920 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2921 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 295 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AIKATERINH", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 2922 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2923 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2924 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2925 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2926 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2927 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2928 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2929 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 296 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPASOR", "TZESIKA", &athletesBlockBuf);

	/* �������� ��� �������� 2930 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 297 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LYN", "MPASOR", &athletesBlockBuf);

	/* �������� ��� �������� 2931 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2932 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2933 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2934 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2935 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2936 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2937 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2938 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2939 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2940 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 2941 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2942 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2943 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2944 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2945 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2946 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 298 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LINTSEI", "KRISTIN", &athletesBlockBuf);

	/* �������� ��� �������� 2947 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2948 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2949 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2950 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 2951 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2952 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2953 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2954 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2955 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2956 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2957 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 2958 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* �������� ��� �������� 2959 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 2960 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2961 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 299 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPOYZIOY", "IVANNA", &athletesBlockBuf);

	/* �������� ��� �������� 2962 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 300 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SKIGKAS", "STEFANI", &athletesBlockBuf);

	/* �������� ��� �������� 2963 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2964 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2965 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2966 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 2967 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2968 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2969 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2970 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2971 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 2972 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2973 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 301 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZARNESKI", "BANESSA", &athletesBlockBuf);

	/* �������� ��� �������� 2974 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2975 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2976 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 2977 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2978 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 2979 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2980 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 2981 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 2982 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 302 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZEIMS", "LINTZY", &athletesBlockBuf);

	/* �������� ��� �������� 2983 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2984 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2985 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 2986 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2987 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 2988 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2989 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 303 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LVREN", "FARNGOYORU", &athletesBlockBuf);

	/* �������� ��� �������� 2990 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 2991 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 2992 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2993 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 2994 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 2995 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 2996 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 2997 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 2998 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 2999 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3000 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 304 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TZEIMI", "LYN", &athletesBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3001 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3002 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3003 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3004 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3005 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3006 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3007 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3008 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3009 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3010 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3011 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3012 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3013 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3014 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3015 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3016 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3017 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3018 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3019 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3020 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/2005", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 305 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FARNGOYORU", "STEISI", &athletesBlockBuf);

	/* �������� ��� �������� 3021 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3022 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3023 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3024 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3025 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3026 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3027 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3028 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3029 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3030 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3031 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3032 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 306 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LH", "FARNGOYORU", &athletesBlockBuf);

	/* �������� ��� �������� 3033 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3034 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3035 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3036 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3037 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 307 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SARA", "RENE", &athletesBlockBuf);

	/* �������� ��� �������� 3038 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3039 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3040 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3041 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 29 ��� ������ EVENT */
	insertEvent(eventId, "STIBOS", &eventsBlockBuf);

	/* �������� ��� �������� 308 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UANOY", "AIKATERINH", &athletesBlockBuf);

	/* �������� ��� �������� 3042 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3043 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3044 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3045 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3046 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3047 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3048 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3049 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3050 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1986", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3051 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3052 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3053 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 309 ��� ������ ATHLETES */
	insertAthlete(athleteId, "RENTOYMH", "FLVRA", &athletesBlockBuf);

	/* �������� ��� �������� 3054 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3055 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3056 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 310 ��� ������ ATHLETES */
	insertAthlete(athleteId, "EFENTAKH", "KVNSTANTINA", &athletesBlockBuf);

	/* �������� ��� �������� 3057 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3058 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3059 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3060 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3061 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3062 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3063 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3064 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3065 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3066 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3067 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3068 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3069 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 311 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOKOTOY", "XRISTINA", &athletesBlockBuf);

	/* �������� ��� �������� 3070 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3071 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3072 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 312 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPAGIANNH", "AUHNA", &athletesBlockBuf);

	/* �������� ��� �������� 3073 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3074 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3075 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3076 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3077 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3078 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 313 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSOYMELEKA", "AUANASIA", &athletesBlockBuf);

	/* �������� ��� �������� 3079 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3080 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3081 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3082 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3083 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 314 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAIDANTZH", "OLGA", &athletesBlockBuf);

	/* �������� ��� �������� 3084 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3085 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3086 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3087 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3088 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3089 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3090 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3091 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3092 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3093 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3094 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3095 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3096 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3097 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3098 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3099 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3100 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1986", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3101 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 315 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKOYNTENOYDH", "XRYSOYLA", &athletesBlockBuf);

	/* �������� ��� �������� 3102 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3103 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3104 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3105 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3106 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3107 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3108 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3109 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3110 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3111 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3112 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3113 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3114 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3115 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 316 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XALKIA", "FANH", &athletesBlockBuf);

	/* �������� ��� �������� 3116 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3117 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3118 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3119 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 317 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BASARMIDOY", "MARINA", &athletesBlockBuf);

	/* �������� ��� �������� 3120 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3121 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3122 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3123 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3124 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3125 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3126 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3127 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3128 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3129 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3130 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3131 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3132 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3133 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3134 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3135 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3136 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3137 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 318 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARASTAMATH", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 3138 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3139 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3140 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3141 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3142 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3143 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3144 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3145 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3146 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3147 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3148 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3149 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3150 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2001", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3151 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3152 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3153 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3154 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3155 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3156 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 319 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOKLVNH", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 3157 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3158 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3159 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3160 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3161 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3162 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3163 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3164 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3165 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3166 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3167 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3168 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3169 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3170 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3171 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3172 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3173 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 320 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PATOYLIDOY", "PARASKEYH", &athletesBlockBuf);

	/* �������� ��� �������� 3174 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3175 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3176 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3177 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3178 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3179 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1989", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 321 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PATSOY", "EYFROSYNH", &athletesBlockBuf);

	/* �������� ��� �������� 3180 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3181 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3182 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3183 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3184 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3185 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3186 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3187 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 322 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYMNAKH", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 3188 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3189 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3190 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3191 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3192 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3193 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3194 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3195 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3196 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3197 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3198 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3199 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3200 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1990", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3201 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 323 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPOYNTA", "XARIKLEIA", &athletesBlockBuf);

	/* �������� ��� �������� 3202 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3203 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3204 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3205 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3206 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3207 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3208 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3209 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3210 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3211 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3212 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3213 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3214 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3215 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 324 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NTOBA", "DHMHTRA", &athletesBlockBuf);

	/* �������� ��� �������� 3216 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3217 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3218 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3219 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3220 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3221 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3222 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3223 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3224 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3225 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3226 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3227 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3228 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3229 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3230 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3231 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 325 ��� ������ ATHLETES */
	insertAthlete(athleteId, "IAKVBOY", "XRYSOSTOMIA", &athletesBlockBuf);

	/* �������� ��� �������� 3232 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3233 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3234 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3235 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 326 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LIKA", "BOISABA", &athletesBlockBuf);

	/* �������� ��� �������� 3236 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3237 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 327 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MANIANI", "MIRELA", &athletesBlockBuf);

	/* �������� ��� �������� 3238 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3239 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3240 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3241 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3242 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3243 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3244 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 328 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSIOLAKOYDH", "AGGELIKH", &athletesBlockBuf);

	/* �������� ��� �������� 3245 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3246 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3247 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3248 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3249 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3250 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2005", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3251 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3252 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3253 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3254 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 329 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BOGGOLH", "AIKATERINH", &athletesBlockBuf);

	/* �������� ��� �������� 3255 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3256 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3257 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3258 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3259 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3260 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3261 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3262 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3263 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3264 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3265 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3266 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3267 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3268 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3269 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3270 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 330 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KELESIDOY", "ANASTASIA", &athletesBlockBuf);

	/* �������� ��� �������� 3271 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3272 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3273 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3274 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3275 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3276 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3277 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3278 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3279 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3280 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3281 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3282 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3283 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3284 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3285 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 331 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSIKOYNA", "STYLIANH", &athletesBlockBuf);

	/* �������� ��� �������� 3286 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3287 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3288 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3289 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3290 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3291 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3292 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3293 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3294 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3295 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3296 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3297 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3298 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 332 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SKAFIDA", "AFRODITH", &athletesBlockBuf);

	/* �������� ��� �������� 3299 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3300 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1993", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3301 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3302 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3303 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3304 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3305 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3306 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3307 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3308 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3309 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3310 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3311 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3312 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3313 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3314 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3315 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3316 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3317 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3318 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 333 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSILIGKIRH", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 3319 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3320 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3321 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3322 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3323 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3324 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3325 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3326 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3327 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3328 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3329 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3330 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3331 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 334 ��� ������ ATHLETES */
	insertAthlete(athleteId, "STRATAKH", "ARGYRV", &athletesBlockBuf);

	/* �������� ��� �������� 3332 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3333 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3334 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3335 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3336 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3337 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3338 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3339 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3340 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3341 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3342 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3343 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3344 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3345 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3346 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3347 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3348 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3349 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3350 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 335 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AMPATZIDOY", "GEVRGIA", &athletesBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3351 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3352 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3353 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3354 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3355 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3356 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3357 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3358 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3359 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 336 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAFETZH", "GIANNOYLA", &athletesBlockBuf);

	/* �������� ��� �������� 3360 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3361 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3362 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3363 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3364 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3365 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3366 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3367 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3368 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3369 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3370 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3371 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3372 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3373 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3374 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3375 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3376 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3377 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1993", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 337 ��� ������ ATHLETES */
	insertAthlete(athleteId, "JANUOY", "NIKH", &athletesBlockBuf);

	/* �������� ��� �������� 3378 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3379 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3380 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3381 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3382 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3383 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3384 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3385 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3386 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3387 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3388 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3389 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3390 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3391 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3392 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3393 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3394 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 338 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PILATOY", "STYLIANH", &athletesBlockBuf);

	/* �������� ��� �������� 3395 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3396 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3397 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3398 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3399 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3400 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1993", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3401 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3402 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 339 ��� ������ ATHLETES */
	insertAthlete(athleteId, "OYZOYNH", "KALLIOPH", &athletesBlockBuf);

	/* �������� ��� �������� 3403 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3404 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3405 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3406 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3407 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3408 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3409 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3410 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3411 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3412 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3413 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3414 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3415 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 340 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TERZOGLOY", "EIRHNH", &athletesBlockBuf);

	/* �������� ��� �������� 3416 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3417 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3418 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3419 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3420 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3421 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3422 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3423 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3424 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3425 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3426 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3427 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3428 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3429 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3430 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3431 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3432 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3433 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 341 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPAGEVRGIOY", "ALEJANDRA", &athletesBlockBuf);

	/* �������� ��� �������� 3434 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3435 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3436 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3437 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 342 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOY", "STYLIANH", &athletesBlockBuf);

	/* �������� ��� �������� 3438 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 343 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSAMOGLOY", "EYDOKIA", &athletesBlockBuf);

	/* �������� ��� �������� 3439 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3440 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3441 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3442 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3443 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3444 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3445 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3446 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3447 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3448 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3449 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3450 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1992", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3451 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3452 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3453 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3454 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3455 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3456 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 344 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BASDEKH", "OLGA", &athletesBlockBuf);

	/* �������� ��� �������� 3457 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 345 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DEBETZH", "XRYSOPHGH", &athletesBlockBuf);

	/* �������� ��� �������� 3458 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3459 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3460 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3461 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3462 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3463 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3464 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3465 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3466 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 346 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PERRA", "AUANASIA", &athletesBlockBuf);

	/* �������� ��� �������� 3467 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3468 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3469 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3470 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3471 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3472 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3473 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3474 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3475 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3476 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3477 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 347 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MHTROPOYLOY", "NIKOLITSA", &athletesBlockBuf);

	/* �������� ��� �������� 3478 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3479 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3480 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 348 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UEODVRIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3481 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3482 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3483 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3484 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3485 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3486 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3487 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3488 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3489 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3490 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3491 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3492 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3493 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3494 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3495 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3496 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3497 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3498 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3499 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 349 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XOIDHS", "XRISTOFOROS", &athletesBlockBuf);

	/* �������� ��� �������� 3500 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1990", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3501 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3502 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3503 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3504 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3505 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3506 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3507 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3508 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3509 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3510 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3511 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3512 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3513 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3514 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3515 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 350 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PIETRHS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3516 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3517 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3518 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3519 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3520 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3521 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3522 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3523 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3524 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3525 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3526 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 351 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UANOPOYLOS", "ELEYUERIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3527 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3528 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3529 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3530 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3531 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3532 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3533 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3534 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3535 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3536 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3537 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3538 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3539 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3540 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3541 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3542 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3543 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 352 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GKOYSHS", "ANASTASIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3544 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3545 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3546 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3547 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3548 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3549 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3550 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2005", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3551 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1993", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 353 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KENTERHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 3552 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3553 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3554 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3555 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3556 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 354 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SARRHS", "PANAGIVTHS", &athletesBlockBuf);

	/* �������� ��� �������� 3557 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3558 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3559 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3560 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3561 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3562 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3563 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3564 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3565 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3566 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3567 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3568 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3569 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3570 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3571 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3572 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3573 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3574 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3575 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3576 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 355 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DHMOTSIOS", "STYLIANOS", &athletesBlockBuf);

	/* �������� ��� �������� 3577 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3578 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3579 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3580 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3581 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 356 ��� ������ ATHLETES */
	insertAthlete(athleteId, "IAKVBAKHS", "PERIKLHS", &athletesBlockBuf);

	/* �������� ��� �������� 3582 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3583 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3584 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3585 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3586 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3587 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3588 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3589 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3590 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3591 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3592 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3593 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3594 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3595 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 357 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GRABALOS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3596 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3597 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3598 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3599 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3600 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/2003", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3601 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3602 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3603 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3604 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3605 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3606 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 358 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NTOYPHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3607 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3608 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3609 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3610 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3611 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3612 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3613 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 359 ��� ������ ATHLETES */
	insertAthlete(athleteId, "OIKONOMIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3614 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3615 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3616 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3617 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3618 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3619 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3620 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3621 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3622 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3623 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3624 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3625 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3626 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3627 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 360 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ARGYROPOYLOS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3628 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3629 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3630 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3631 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3632 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3633 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 361 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KASTANHS", "SPYRIDVN", &athletesBlockBuf);

	/* �������� ��� �������� 3634 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3635 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3636 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3637 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3638 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3639 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3640 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3641 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3642 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3643 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3644 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3645 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3646 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3647 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3648 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3649 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3650 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1999", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3651 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 362 ��� ������ ATHLETES */
	insertAthlete(athleteId, "STAMATOPOYLOS", "UEODVROS", &athletesBlockBuf);

	/* �������� ��� �������� 3652 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3653 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3654 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3655 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3656 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3657 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3658 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3659 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3660 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3661 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3662 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3663 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3664 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3665 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3666 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3667 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3668 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 363 ��� ������ ATHLETES */
	insertAthlete(athleteId, "STROYMPAKOS", "PANAGIVTHS", &athletesBlockBuf);

	/* �������� ��� �������� 3669 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3670 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3671 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3672 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3673 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3674 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3675 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3676 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3677 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3678 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3679 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3680 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3681 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3682 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3683 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3684 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 364 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KORKIZOGLOY", "PRODROMOS", &athletesBlockBuf);

	/* �������� ��� �������� 3685 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3686 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3687 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3688 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3689 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 365 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PANABOGLOY", "SABBAS", &athletesBlockBuf);

	/* �������� ��� �������� 3690 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3691 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3692 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3693 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3694 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3695 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3696 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 366 ��� ������ ATHLETES */
	insertAthlete(athleteId, "EYAGGELOY", "MARIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3697 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3698 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3699 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3700 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3701 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3702 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3703 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3704 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 367 ��� ������ ATHLETES */
	insertAthlete(athleteId, "POLIAS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 3705 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3706 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3707 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3708 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3709 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3710 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3711 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 368 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SERELHS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3712 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3713 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3714 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3715 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3716 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3717 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3718 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3719 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3720 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3721 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3722 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3723 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3724 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3725 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/2002", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 369 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSATOYMAS", "LOYHS", &athletesBlockBuf);

	/* �������� ��� �������� 3726 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3727 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3728 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3729 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3730 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3731 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3732 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3733 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 370 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FILINDRAS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3734 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3735 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3736 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3737 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3738 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3739 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3740 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 371 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPADHMHTRIOY", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 3741 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3742 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3743 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3744 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3745 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3746 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3747 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3748 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3749 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3750 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1995", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3751 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3752 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3753 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3754 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3755 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3756 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 372 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MELETOGLOY", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 3757 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3758 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3759 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3760 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3761 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3762 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3763 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3764 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3765 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3766 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3767 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3768 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3769 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3770 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/2005", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 30 ��� ������ EVENT */
	insertEvent(eventId, "TZOYNTO", &eventsBlockBuf);

	/* �������� ��� �������� 373 ��� ������ ATHLETES */
	insertAthlete(athleteId, "IVANNOY", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 3771 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3772 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3773 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3774 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3775 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3776 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3777 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3778 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3779 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3780 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3781 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3782 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3783 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3784 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3785 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3786 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 374 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARAGIANNOPOYLOY", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 3787 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3788 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3789 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3790 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3791 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3792 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3793 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3794 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3795 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3796 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3797 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3798 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3799 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3800 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1990", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3801 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 375 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSELARIDOY", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 3802 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3803 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3804 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3805 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3806 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3807 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3808 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3809 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3810 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3811 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3812 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3813 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3814 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3815 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3816 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 376 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MPOYKOYBALA", "IOYLIETA", &athletesBlockBuf);

	/* �������� ��� �������� 3817 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3818 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3819 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3820 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3821 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3822 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3823 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3824 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3825 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 377 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TAMPASH", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 3826 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3827 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3828 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3829 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3830 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3831 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3832 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3833 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3834 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3835 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3836 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3837 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3838 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3839 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3840 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3841 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2001", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 378 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOYRTELESH", "ALEJIA", &athletesBlockBuf);

	/* �������� ��� �������� 3842 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3843 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3844 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3845 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3846 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 379 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AKRITIDOY", "BARBARA", &athletesBlockBuf);

	/* �������� ��� �������� 3847 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3848 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3849 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3850 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2003", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3851 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3852 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3853 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3854 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3855 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3856 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3857 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3858 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3859 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3860 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3861 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3862 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3863 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3864 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3865 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3866 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 380 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPAIVANNOY", "XARALAMPOS", &athletesBlockBuf);

	/* �������� ��� �������� 3867 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3868 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3869 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3870 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3871 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3872 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3873 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3874 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3875 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3876 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3877 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3878 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3879 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3880 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3881 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 381 ��� ������ ATHLETES */
	insertAthlete(athleteId, "HLIADHS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3882 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3883 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3884 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3885 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3886 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3887 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3888 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3889 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3890 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3891 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3892 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3893 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/2002", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 382 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ZINTIRIDHS", "REBAZI", &athletesBlockBuf);

	/* �������� ��� �������� 3894 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3895 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3896 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3897 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3898 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3899 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3900 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2002", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3901 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3902 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3903 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3904 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3905 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3906 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3907 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3908 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3909 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3910 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3911 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3912 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3913 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 383 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BAZAGKASBILI", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3914 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3915 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3916 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3917 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3918 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3919 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 384 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ALEJANIDHS", "LAYRENTI", &athletesBlockBuf);

	/* �������� ��� �������� 3920 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3921 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3922 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 3923 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3924 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3925 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3926 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3927 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3928 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2002", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 385 ��� ������ ATHLETES */
	insertAthlete(athleteId, "HLIADHS", "HLIAS", &athletesBlockBuf);

	/* �������� ��� �������� 3929 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3930 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3931 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3932 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3933 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3934 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3935 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3936 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3937 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3938 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3939 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3940 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3941 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3942 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3943 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3944 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3945 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3946 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 386 ��� ������ ATHLETES */
	insertAthlete(athleteId, "HLIADHS", "DIONYSIOS", &athletesBlockBuf);

	/* �������� ��� �������� 3947 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3948 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3949 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3950 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 3951 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3952 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 3953 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3954 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 3955 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3956 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3957 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3958 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/2002", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 31 ��� ������ EVENT */
	insertEvent(eventId, "KALAUOSFAIRISH", &eventsBlockBuf);

	/* �������� ��� �������� 387 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BASILEIOY", "ELENH", &athletesBlockBuf);

	/* �������� ��� �������� 3959 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3960 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3961 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 3962 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3963 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3964 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 3965 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3966 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3967 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 388 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DELH", "AIKATERINH", &athletesBlockBuf);

	/* �������� ��� �������� 3968 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 3969 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 3970 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 3971 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3972 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3973 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3974 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3975 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 3976 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3977 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 3978 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3979 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1990", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 389 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KABBADIA", "TATIANA", &athletesBlockBuf);

	/* �������� ��� �������� 3980 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3981 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 3982 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3983 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3984 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 3985 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 390 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KALENTZOY", "DHMHTRA", &athletesBlockBuf);

	/* �������� ��� �������� 3986 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 3987 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3988 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3989 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3990 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 3991 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 3992 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 3993 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 3994 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 3995 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3996 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3997 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1991", &participationsBlockBuf);

	/* �������� ��� �������� 3998 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 3999 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4000 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1987", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4001 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 391 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KLIGKOPOYLOY", "SOFIA", &athletesBlockBuf);

	/* �������� ��� �������� 4002 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4003 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4004 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4005 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4006 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4007 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4008 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4009 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 392 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KVSTAKH", "ANASTASIA", &athletesBlockBuf);

	/* �������� ��� �������� 4010 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4011 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 393 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MALTSH", "EYANUIA", &athletesBlockBuf);

	/* �������� ��� �������� 4012 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4013 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4014 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4015 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4016 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 394 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SAMOROYKOBA", "MARIA", &athletesBlockBuf);

	/* �������� ��� �������� 4017 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4018 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4019 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4020 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4021 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4022 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4023 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4024 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4025 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4026 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4027 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4028 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4029 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4030 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4031 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4032 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 395 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SAREGKOY", "POLYMNIA", &athletesBlockBuf);

	/* �������� ��� �������� 4033 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4034 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4035 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4036 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4037 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4038 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4039 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4040 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4041 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4042 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4043 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4044 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4045 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2000", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 396 ��� ������ ATHLETES */
	insertAthlete(athleteId, "STAXTIARH", "EIRHNH", &athletesBlockBuf);

	/* �������� ��� �������� 4046 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4047 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4048 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4049 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4050 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1999", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4051 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1999", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 397 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TASOYLH", "ATALANTH-MARI", &athletesBlockBuf);

	/* �������� ��� �������� 4052 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4053 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4054 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4055 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 398 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XRISTOFORAKH", "AUHNA", &athletesBlockBuf);

	/* �������� ��� �������� 4056 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4057 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4058 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4059 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4060 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4061 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4062 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4063 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 399 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GLYNIADAKHS", "ANDREAS", &athletesBlockBuf);

	/* �������� ��� �������� 4064 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4065 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4066 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4067 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4068 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4069 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4070 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4071 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4072 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4073 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4074 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4075 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4076 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4077 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4078 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4079 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4080 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4081 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 400 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DIAMANTIDHS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4082 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4083 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4084 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4085 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4086 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4087 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4088 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4089 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4090 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4091 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4092 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4093 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4094 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4095 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4096 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4097 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4098 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1993", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 401 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ZHSHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 4099 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4100 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/2004", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4101 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4102 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4103 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4104 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4105 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4106 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4107 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 402 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KAKIOYZHS", "MIXAHL", &athletesBlockBuf);

	/* �������� ��� �������� 4108 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4109 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4110 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4111 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4112 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4113 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4114 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4115 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4116 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 403 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NTIKOYDHS", "DHMOSUENHS", &athletesBlockBuf);

	/* �������� ��� �������� 4117 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4118 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4119 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4120 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4121 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4122 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4123 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 404 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPALOYKAS", "UEODVROS", &athletesBlockBuf);

	/* �������� ��� �������� 4124 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4125 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4126 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4127 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4128 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4129 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4130 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4131 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4132 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4133 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 405 ��� ������ ATHLETES */
	insertAthlete(athleteId, "PAPANIKOLAOY", "DHMHTRHS", &athletesBlockBuf);

	/* �������� ��� �������� 4134 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4135 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 406 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SPANOYLHS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4136 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4137 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4138 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4139 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4140 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4141 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4142 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4143 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4144 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4145 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4146 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4147 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 407 ��� ������ ATHLETES */
	insertAthlete(athleteId, "TSARTSARHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 4148 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4149 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1998", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 408 ��� ������ ATHLETES */
	insertAthlete(athleteId, "FVTSHS", "ANTVNIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4150 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1987", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4151 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4152 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4153 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4154 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4155 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4156 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4157 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1989", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 409 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XARISHS", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 4158 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4159 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4160 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4161 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4162 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4163 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4164 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4165 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4166 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4167 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4168 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4169 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 410 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XATZHBRETTAS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 4170 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4171 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4172 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4173 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4174 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4175 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4176 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2003", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 32 ��� ������ EVENT */
	insertEvent(eventId, "TOJOBOLIA", &eventsBlockBuf);

	/* �������� ��� �������� 411 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BABATSH", "FVTEINH", &athletesBlockBuf);

	/* �������� ��� �������� 4177 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4178 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4179 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4180 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4181 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4182 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4183 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4184 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4185 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4186 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 412 ��� ������ ATHLETES */
	insertAthlete(athleteId, "RVMANTZH", "ELPIDA", &athletesBlockBuf);

	/* �������� ��� �������� 4187 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4188 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4189 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4190 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4191 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4192 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4193 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4194 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4195 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4196 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 413 ��� ������ ATHLETES */
	insertAthlete(athleteId, "CARRA", "EYAGGELIA", &athletesBlockBuf);

	/* �������� ��� �������� 4197 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4198 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4199 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4200 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1986", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4201 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4202 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1994", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 414 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KALOGIANNIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4203 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4204 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4205 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4206 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4207 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4208 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4209 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4210 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4211 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4212 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4213 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4214 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4215 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4216 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4217 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4218 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4219 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1991", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 415 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARAGEVRGIOY", "ALEJANDROS", &athletesBlockBuf);

	/* �������� ��� �������� 4220 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4221 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 416 ��� ������ ATHLETES */
	insertAthlete(athleteId, "NANOS", "APOSTOLOS", &athletesBlockBuf);

	/* �������� ��� �������� 4222 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �� ����� ��� ������� EVENTS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(eventsFd, eventsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on EVENTS.");

	/* �������� ��� ��� ����� ��� �� ������ EVENTS. */
	callAllocBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf, "EVENTS");

	/* �������� ��� �������� 33 ��� ������ EVENT */
	insertEvent(eventId, "TRIAULO", &eventsBlockBuf);

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 417 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KROMMYDAS", "BASILEIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4223 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4224 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4225 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4226 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4227 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4228 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4229 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4230 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4231 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4232 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4233 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/2004", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 34 ��� ������ EVENT */
	insertEvent(eventId, "PODHLASIA PISTAS", &eventsBlockBuf);

	/* �������� ��� �������� 418 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KVNSTANTINIDOY", "KYRIAKH", &athletesBlockBuf);

	/* �������� ��� �������� 4234 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4235 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4236 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4237 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4238 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4239 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4240 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4241 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4242 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4243 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 419 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BASILOPOYLOS", "LAMPROS", &athletesBlockBuf);

	/* �������� ��� �������� 4244 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4245 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 420 ��� ������ ATHLETES */
	insertAthlete(athleteId, "GEVRGALHS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4246 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4247 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4248 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4249 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4250 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1989", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4251 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4252 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4253 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4254 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4255 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4256 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4257 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4258 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4259 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4260 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4261 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4262 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4263 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 421 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XEIMVNETOS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4264 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4265 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4266 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4267 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4268 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4269 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4270 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4271 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4272 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4273 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4274 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4275 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4276 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4277 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4278 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4279 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4280 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4281 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4282 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1995", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 35 ��� ������ EVENT */
	insertEvent(eventId, "YDATOSFAIRISH", &eventsBlockBuf);

	/* �������� ��� �������� 422 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ASILIAN", "DHMHTRA", &athletesBlockBuf);

	/* �������� ��� �������� 4283 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4284 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4285 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4286 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4287 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4288 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4289 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4290 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4291 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4292 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4293 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4294 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4295 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4296 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4297 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4298 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4299 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4300 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1989", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4301 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4302 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 423 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ELLHNAKH", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 4303 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4304 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4305 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4306 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4307 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4308 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4309 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4310 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 424 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARAGIANNH", "EYTYXIA", &athletesBlockBuf);

	/* �������� ��� �������� 4311 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4312 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4313 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4314 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4315 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 425 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KARAPATAKH", "AGGELIKH", &athletesBlockBuf);

	/* �������� ��� �������� 4316 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4317 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4318 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4319 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4320 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4321 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4322 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4323 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4324 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4325 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4326 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4327 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4328 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4329 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4330 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4331 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4332 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4333 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4334 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4335 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 426 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KOZOMPOLH", "STAYROYLA", &athletesBlockBuf);

	/* �������� ��� �������� 4336 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4337 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4338 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4339 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4340 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4341 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4342 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4343 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4344 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4345 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4346 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4347 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4348 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4349 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4350 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1989", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4351 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 427 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LARA", "GEVRGIA", &athletesBlockBuf);

	/* �������� ��� �������� 4352 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4353 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4354 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4355 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4356 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4357 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4358 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4359 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4360 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4361 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4362 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4363 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4364 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4365 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4366 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4367 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4368 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4369 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4370 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4371 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 428 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LIOSH", "KYRIAKH", &athletesBlockBuf);

	/* �������� ��� �������� 4372 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4373 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4374 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4375 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4376 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4377 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4378 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4379 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4380 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4381 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4382 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4383 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4384 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 429 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MELIDVNH", "ANTIOPH", &athletesBlockBuf);

	/* �������� ��� �������� 4385 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4386 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4387 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4388 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4389 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4390 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4391 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4392 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4393 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 430 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MYLVNAKH", "ANUOYLA", &athletesBlockBuf);

	/* �������� ��� �������� 4394 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4395 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4396 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4397 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4398 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4399 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4400 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1989", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4401 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 431 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MVRAITH", "ANTVNIA", &athletesBlockBuf);

	/* �������� ��� �������� 4402 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4403 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4404 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4405 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4406 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4407 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4408 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4409 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4410 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4411 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4412 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4413 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4414 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4415 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4416 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1996", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 432 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MVRAITIDOY", "EYAGGELIA", &athletesBlockBuf);

	/* �������� ��� �������� 4417 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4418 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4419 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4420 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4421 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1990", &participationsBlockBuf);

	athleteId++;

	/* �� ����� ��� ������� ATHLETES ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* �������� ��� ��� ����� ��� �� ������ ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* �������� ��� �������� 433 ��� ������ ATHLETES */
	insertAthlete(athleteId, "OIKONOMOPOYLOY", "AIKATERINH", &athletesBlockBuf);

	/* �������� ��� �������� 4422 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1997", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 434 ��� ������ ATHLETES */
	insertAthlete(athleteId, "ROYMPESH", "ANTIGONH", &athletesBlockBuf);

	/* �������� ��� �������� 4423 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4424 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4425 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4426 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4427 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4428 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4429 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2004", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 435 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AFROYDAKHS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4430 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4431 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4432 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4433 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1986", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 436 ��� ������ ATHLETES */
	insertAthlete(athleteId, "AFROYDAKHS", "XRHSTOS", &athletesBlockBuf);

	/* �������� ��� �������� 4434 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4435 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4436 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4437 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4438 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4439 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4440 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 437 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BLONTAKHS", "ANTVNIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4441 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4442 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4443 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 438 ��� ������ ATHLETES */
	insertAthlete(athleteId, "DELHGIANNHS", "NIKOLAOS", &athletesBlockBuf);

	/* �������� ��� �������� 4444 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4445 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4446 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4447 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4448 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4449 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4450 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2005", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4451 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4452 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4453 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4454 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4455 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4456 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4457 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4458 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4459 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4460 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4461 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2003", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 439 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UEODVROPOYLOS", "ARGYRHS", &athletesBlockBuf);

	/* �������� ��� �������� 4462 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4463 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4464 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4465 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4466 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4467 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4468 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4469 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4470 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4471 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4472 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4473 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4474 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4475 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4476 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4477 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4478 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4479 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4480 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1993", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 440 ��� ������ ATHLETES */
	insertAthlete(athleteId, "UVMAKOS", "IVANNHS", &athletesBlockBuf);

	/* �������� ��� �������� 4481 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4482 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4483 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4484 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4485 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4486 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4487 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4488 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4489 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4490 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4491 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4492 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4493 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4494 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4495 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4496 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 441 ��� ������ ATHLETES */
	insertAthlete(athleteId, "KALAKVNAS", "UEODVROS", &athletesBlockBuf);

	/* �������� ��� �������� 4497 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4498 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4499 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4500 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1992", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4501 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4502 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4503 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4504 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4505 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1992", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 442 ��� ������ ATHLETES */
	insertAthlete(athleteId, "LOYDHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* �������� ��� �������� 4506 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4507 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4508 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4509 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4510 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4511 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4512 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4513 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4514 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4515 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4516 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4517 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4518 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4519 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4520 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4521 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4522 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4523 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 443 ��� ������ ATHLETES */
	insertAthlete(athleteId, "MAZHS", "DHMHTRIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4524 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4525 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4526 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1995", &participationsBlockBuf);

	/* �������� ��� �������� 4527 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4528 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4529 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4530 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1994", &participationsBlockBuf);

	/* �������� ��� �������� 4531 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4532 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4533 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1995", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 444 ��� ������ ATHLETES */
	insertAthlete(athleteId, "REPPAS", "GEVRGIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4534 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4535 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4536 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2005", &participationsBlockBuf);

	/* �������� ��� �������� 4537 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1988", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 445 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SANTA", "STEFANOS-PETR", &athletesBlockBuf);

	/* �������� ��� �������� 4538 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1988", &participationsBlockBuf);

	/* �������� ��� �������� 4539 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4540 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2005", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 446 ��� ������ ATHLETES */
	insertAthlete(athleteId, "SXIZAS", "ANASTASIOS", &athletesBlockBuf);

	/* �������� ��� �������� 4541 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4542 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4543 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4544 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4545 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4546 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4547 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4548 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4549 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4550 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/2005", &participationsBlockBuf);

	/* �� ����� ��� ������� PARTICIPATIONS ����� ������ ��� ������ �� ����������. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ��� ����� ��� �� ������ PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* �������� ��� �������� 4551 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1993", &participationsBlockBuf);

	/* �������� ��� �������� 4552 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2003", &participationsBlockBuf);

	/* �������� ��� �������� 4553 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4554 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1989", &participationsBlockBuf);

	/* �������� ��� �������� 4555 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1990", &participationsBlockBuf);

	/* �������� ��� �������� 4556 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1987", &participationsBlockBuf);

	athleteId++;

	/* �������� ��� �������� 447 ��� ������ ATHLETES */
	insertAthlete(athleteId, "XATZHUEODVROY", "UEODVROS", &athletesBlockBuf);

	/* �������� ��� �������� 4557 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1996", &participationsBlockBuf);

	/* �������� ��� �������� 4558 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2001", &participationsBlockBuf);

	/* �������� ��� �������� 4559 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4560 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2003", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* �������� ��� �������� 36 ��� ������ EVENT */
	insertEvent(eventId, "ANTIPTERISH", &eventsBlockBuf);

	/* �������� ��� �������� 448 ��� ������ ATHLETES */
	insertAthlete(athleteId, "BELKOS", "UEODVROS", &athletesBlockBuf);

	/* �������� ��� �������� 4561 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1987", &participationsBlockBuf);

	/* �������� ��� �������� 4562 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/2004", &participationsBlockBuf);

	/* �������� ��� �������� 4563 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4564 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2002", &participationsBlockBuf);

	/* �������� ��� �������� 4565 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1991", &participationsBlockBuf);

	/* �������� ��� �������� 4566 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1998", &participationsBlockBuf);

	/* �������� ��� �������� 4567 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1997", &participationsBlockBuf);

	/* �������� ��� �������� 4568 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1999", &participationsBlockBuf);

	/* �������� ��� �������� 4569 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/2000", &participationsBlockBuf);

	/* �������� ��� �������� 4570 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1986", &participationsBlockBuf);

	/* �������� ��� �������� 4571 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1992", &participationsBlockBuf);

	/* �������� ��� �������� 4572 ��� ������ PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1988", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* ��������� �� ��������� ����� ���� �������� �� ������. */
	if (BF_UnpinBlock(eventsFd, eventsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on EVENTS.");
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* �������� ��� ����� �������. */
	if (BF_CloseFile(eventsFd) < 0)
		BF_PrintError("Error in BF_CloseFile called on EVENTS.");
	if (BF_CloseFile(athletesFd) < 0)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");
	if (BF_CloseFile(participationsFd) < 0)
		BF_PrintError("Error in BF_CloseFile called on PARTICIPATIONS.");

	return 0;
}

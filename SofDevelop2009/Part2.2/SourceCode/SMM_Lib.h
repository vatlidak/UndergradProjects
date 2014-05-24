/*
 * Scan Management Level lib.
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogiannopoulos Aris, Kuriazof Xristina
 * AM: 	    1115200500010, 1115200500004, 1115200600276
 * 
 *
 * Date: 6 December, 2009.
 */
 
#include "HF_Defines.h"

/* struct to keep informations */
/* about files' Scans      */
typedef struct Scan_Info{
	int 	fileDesc;
	int 	recordSize;
	char	attrType;
	int	attrLength;
	int 	attrOffset;
	int 	op;
	char    *value;
	int	lastRecId;
	int 	empty;
}Scan_Info;
Scan_Info scan_info[MAXSCANS];


void SMM_Init();
int SMM_OpenFileScan(int, int, char, int, int, int, char*);
int SMM_FindNextRec(int scanDesc, char*);
int SMM_CloseFileScan(int);
BOOLEAN SMM_hasOpenScans(int);

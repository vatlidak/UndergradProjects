#include "BF_Defines.h"

void BMM_Init();
int BMM_GetBlock(fileInfo_t, int, char**);
int BMM_AllocBlock(fileInfo_t, int, char**);
int BMM_UnpinBlock(fileInfo_t, int, BOOLEAN);
int BMM_DisposeBlock(fileInfo_t, int);
int BMM_Flush(fileInfo_t );
int BMM_Clear(char* );

/* struct to keep informations */
/* about files in memory       */
typedef struct Mem_Info{
	int 	PinCounter;
	int 	BlockNum;
	char    FileName[MAX_FILE_NAME];
	char	Block[BF_BLOCK_SIZE];
	BOOLEAN	Empty;
	BOOLEAN Dirty;
	BOOLEAN PinedBy[MAXOPENFILES];
	unsigned long int 	TimeStamp;
}Mem_Info;
Mem_Info Mem_info[BF_BUFFER_SIZE];

unsigned long int Time;				/* variable to simulate time, for LRU */


/*A.M.: 1115 2005 00010 */
/*ATLIDAKIS VAGGELIS	*/
/*std05010@di.uoa.gr	*/

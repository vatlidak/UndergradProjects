#include "BF_Defines.h"

void FMM_Init();
int FMM_Open(char* );
int FMM_Close(int );
BOOLEAN FMM_IsOpen();
BOOLEAN FMM_IsValid(int );
int FMM_GetFileInfoByName(fileInfo_t* );
int FMM_GetFileInfoByFD(fileInfo_t* );
BOOLEAN FMM_HEAD_IsValid(int, int );
int FMM_HEAD_GetFirstBlock(int );
int FMM_HEAD_GetNextBlock(int, int );
int FMM_HEAD_GetFirstEmpty(int );
int FMM_HEAD_Set(int, int, BOOLEAN);


/* struct to keep informations */
/* about file openings         */
typedef struct File_Opening{
	FILE* 	fp;
	int	empty;
	int 	header;
}File_Opening;
File_Opening file_openings[MAXOPENFILES];


/* struct to keep informations */
/* about file headers          */
typedef struct File_Header{
	char 	name[MAX_FILE_NAME];
	int  	openings;
	int 	empty;
	int 	dirty;
	unsigned char 	header[BF_BLOCK_SIZE];

}File_Header;
File_Header file_headers[MAXOPENFILES];

/*A.M.: 1115 2005 00010 */
/*ATLIDAKIS VAGGELIS	*/
/*std05010@di.uoa.gr	*/

#include "BF_Defines.h"

int HDF_OpenFile(char*, FILE** );
int HDF_CloseFile(FILE* );
int HDF_CreateFile(char* );
int HDF_DestroyFile(char* );
BOOLEAN HDF_ExistsFile(char* );
int HDF_ReadBlock(int, char*, FILE*);
int HDF_WriteBlock(int,  char*, FILE* );

/*A.M.: 1115 2005 00010 */
/*ATLIDAKIS VAGGELIS	*/
/*std05010@di.uoa.gr	*/

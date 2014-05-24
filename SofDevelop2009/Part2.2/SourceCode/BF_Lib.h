/* FileName: BF_Lib.h
 *
 * Header for Block File level contains functions to provide upper
 * levels an interface with the filed located at Hard Disk, using 
 * Block as communication unit.
 *
 *
 * author: 	Atlidakis Vaggelis 
 * 
 * std05010@di.uoa.gr
 * A.M.:1115200500010
 * 
 */
 
void BF_Init(void);
int BF_CreateFile(char*);
int BF_DestroyFile(char*);
int BF_OpenFile (char*);
int BF_CloseFile (int);
int BF_GetFirstBlock(int,int*,char**);
int BF_GetNextBlock(int,int*,char**);
int BF_GetThisBlock(int,int,char**);
int BF_AllocBlock(int,int*,char**);
int BF_DisposeBlock(int,int);
int BF_UnpinBlock(int,int,int);
void BF_PrintError(char*);

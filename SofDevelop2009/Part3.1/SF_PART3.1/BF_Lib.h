#ifndef BF_LIB_H
#define BF_LIB_H


/* Ορισμός καθολικής μεταβλητής σφάλματος */
int BF_errno;

/* Δηλώσεις συναρτήσεων Επιπέδου Block */
void BF_Init(void);
int BF_CreateFile(char *filename);
int BF_DestroyFile(char *filename);
int BF_OpenFile(char *filename);
int BF_CloseFile(int fileDesc);
int BF_GetFirstBlock(int fileDesc, int *blockNum, char **blockBuf);
int BF_GetNextBlock(int fileDesc, int *blockNum, char **blockBuf);
int BF_GetThisBlock(int fileDesc, int blockNum, char **blockBuf);
int BF_AllocBlock(int fileDesc, int *blockNum, char **blockBuf);
int BF_DisposeBlock(int fileDesc, int *blockNum);
int BF_UnpinBlock(int fileDesc, int blockNum, int dirty);
void BF_PrintError(char *errString);

#endif

/*
 * File: RMM_Lib.h
 *
 * Authors: Atlidakis Vaggelis, Aggelogiannopoulos Aris, Kuriazof Xristina
 * AM: 	    1115200500010, 1115200500004, 1115200600267
 * 
 * Date: 1.12.2009
 *
 */
int RMM_InsertRec( int ,char* ,int);
int RMM_DeleteRec( int ,int ,int);
int RMM_GetFirstRec(int ,char* ,int);
int RMM_GetNextRec(int ,int ,char* ,int);
int RMM_GetThisRec(int ,int ,char* ,int);

int HF_errno;

/*
 * FileName: ArgsManipulation_Lib.h
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogianopoulos Aris, Kuriazof Xristina
 *
 *
 * Date: Jan 2010
 *
 *
 */
#ifndef ARGSMANIPULATION_LIB_H
#define ARGSMANIPULATION_LIB_H

#include "CFM_Lib.h"

int Create_MakeArgs(char** argv,char ***myargv,int attrcnt,relDesc relRec, attrDesc* attrs,int mode);
int Insert_MakeArgs(char* record,char** argv,char ***myargv,int attrcnt,relDesc relRec, attrDesc* attrs,int mode);
int Destroy_MakeArgs(char ***myargv,char* relname,int myargc);
void free_args(char** myargv,int myargc);

#endif

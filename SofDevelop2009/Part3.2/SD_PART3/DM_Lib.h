/*
 * FileName: DM_Lib.h
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogianopoulos Aris, Kuriazof Xristina
 *
 *
 * Date: Jan 2010
 *
 *
 */
#ifndef DM_LIB_H
#define DM_LIB_H

int Operator(char* op);
int Create_MakeArgs(char** argv,char ***myargv,int attrcnt,relDesc rel, attrDesc* attrs,int mode);
int Insert_MakeArgs(char*,char** argv,char ***myargv,int attrcnt,relDesc relRec, attrDesc* attrs,int mode);
int Destroy_MakeArgs(char ***myargv,char* relname,int myargc);
void free_args(char** myargv,int myargc);


int DM_insert(int argc, char* argv[]);
int DM_select(int argc, char* argv[]);
int DM_join(int argc, char* argv[]);
int DM_insert(int argc, char* argv[]);
int DM_delete(int argc, char* argv[]);

#endif

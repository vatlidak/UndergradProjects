/*
 * FileName: SCM_Lib.h
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogianopoulos Aris, Kuriazof Xristina
 *
 *
 * Date: Jan 2010
 *
 *
 */
#include "UT_DM_Defines.h"

int SCM_create(int argc, char* argv[]);
int SCM_buildIndex(int argc, char* argv[]);
int SCM_destroy(int argc, char* argv[]);
int SCM_print(char* relName);
int SCM_insert(int argc, char* argv[]);
int SCM_delete(int argc, char* argv[]);
int SCM_select(int argc, char* argv[]);
int SCM_join(int argc, char* argv[]);

int Scan_relcat(char *);
int Scan_attrcat(char *);

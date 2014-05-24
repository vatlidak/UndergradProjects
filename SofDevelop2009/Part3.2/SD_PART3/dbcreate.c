#include <stdio.h>
#include <stdlib.h>
#include "BF_Lib.h"
#include "HF_Lib.h"
#include "CFM_Lib.h"
#ifdef WIN32
        #include <direct.h>
#else
        #include <unistd.h>
        #include <dirent.h>
#endif

int main(int argc, char* argv[]) {
    char* dbname;
    int retVal = 0;

    if (argc != 2) {
        printf("Usage: %s dbname \n", argv[0]);
        return (1);
    }

    dbname = argv[1];

#ifdef WIN32
    if (_mkdir(dbname))
#else
    if (mkdir(dbname, 0700))
#endif
    {
        printf("Database '%s' already exists!\n", dbname);
        retVal = 1;
    }

#ifdef WIN32
    if (_chdir(dbname))
#else
    if (chdir(dbname))
#endif
    {
        printf("Cannot create database '%s'\n", dbname);
        retVal = 2;
    }
    if (!retVal) {

        BF_Init();
        HF_Init();
        retVal = CFM_Create();
    }
    return retVal;
}

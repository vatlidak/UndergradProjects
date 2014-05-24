#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "BF_Defines.h"
//#include "BF_Lib.h"

//#include "HF_Defines.h"
//#include "HF_Lib.h"

#include "UT_DM_Defines.h"
#include "CFM_Lib.h"


int main(int argc, char* argv[]){
    int   rval;
    char  command[80];
    char* dbname;

    if(argc!=2){
        printf("Χρηση: %s dbname \n",argv[0]);
        return(1);
    }
   
    dbname = argv[1];
    sprintf(command,"mkdir %s",dbname);
    system(command);
   
    if(chdir(dbname)){
        printf("Δεν ειναι δυνατη η δημιουργία τησ βασης");
        return(2);
    }


    if ( (rval = CFM_Create())!= UTE_OK )
		fprintf(stderr,"ERROR: %d\n",rval);
    
    return 0;
}

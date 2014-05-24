#include<stdio.h>
#include<stdlib.h>
#include "parser4.h"
#include "UT_DM_Defines.h"

void printArgs(int argc, char **argv){
	int i;
	for(i=0;i<=argc-1;++i)
		fprintf(stderr,"argv[%d]=%s, ",i,argv[i]);
	fprintf(stderr,"argv[%d]=(null)", argc);
	printf("\n\n");
}

int main(int argc, char* argv[])
{
	char* dbname;

    if(argc!=2){
        printf("Usage: %s dbname \n",argv[0]);
        return(1);
    }
  
    dbname=argv[1];
  
    if(chdir(dbname)){
        printf("Cannot open database!");
        return(2);
    }

    /* Αρχικοποίηση προγράμματος */
    /* και άνοιγμα σχέσεων καταλόγου */
	HF_Init();
	AM_Init();
	
	relCatFd = HF_OpenFile("relCat");
	attrCatFd = HF_OpenFile("attrCat");
    /* Κλήση της συνάρτησης yyparse ή οποία */
    /* θα καλεί αυτόματα τις συναρτήσεις σας */

	while(yyparse() == RESTART);
	
	return 0;
}


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char command[80];
    char* dbname;

    if(argc!=2){
        printf("Χρηση: %s dbdestroy \n",argv[0]);
        return(1);
    }
    dbname = argv[1];
    sprintf(command,"rm -r %s",dbname);
    system(command);

    return 0;
}

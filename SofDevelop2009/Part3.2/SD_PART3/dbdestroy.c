#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char command[80];
    char* dbname;

    if (argc != 2) {
        printf("Usage: %s dbdestroy \n", argv[0]);
        return (1);
    }

    dbname = argv[1];

#ifdef WIN32
    sprintf(command, "rmdir %s /s /q", dbname);
#else
    sprintf(command, "rm -rf %s", dbname);
#endif

    system(command);

    return 0;
}

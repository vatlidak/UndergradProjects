#include "buffers.h"


int addrecord(BUFFERS *buffers, char *record, int i);
int update_vectors(char ***keys,char ***values, char *record, int *total_records, int *memsize);
int retrieve_records(BUFFERS *buffers, int i, char ***keys, char ***values, int *total_records, int *memsize);

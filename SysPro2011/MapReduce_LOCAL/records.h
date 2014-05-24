#include "buffers.h"

void addrecord(BUFFERS *buffers, char *record, int i);
void update_vectors(char ***keys,char ***values, char *record, int *total_records, int *memsize);
void retrieve_records(char *block,char ***keys, char ***values, int *total_records, int *memsize);

#ifndef _MAP_REDUCE_H_
#define _MAP_REDUCE_H_


/* Types and functions for MapReduce input */

typedef struct MRIFILE MRIFILE;

MRIFILE *input_open(const char *file_name);

char *input_next(MRIFILE *in);

void input_close(MRIFILE *in);


/* Type and function for MapReduce map */

typedef struct {
	char *key;
	char *value;
} pair;

pair map(const char *record);


/* Function for MapReduce partition */

int partition(const char *key, int reducers);


/* Function for MapReduce reduce */

char *reduce(const char *key, char **values, int values_count);


/* Function for MapReduce compare */

int compare(const char *key_1, const char *key_2);


/* Types and functions for MapReduce output */

typedef struct MROFILE MROFILE;

MROFILE *output_open(const char *file_name);

void output_next(MROFILE *out, char *record);

void output_close(MROFILE *out);


#endif

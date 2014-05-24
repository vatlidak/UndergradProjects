#ifndef _SORT_H_
#define _SORT_H_


/* Sorts by keys - compare function is given as argument */

void sort(char **keys, char **values, int size,
          int (*compare)(const char *, const char *));


#endif

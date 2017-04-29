#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <stdlib.h>
#include <stdbool.h>

char** merge_sort(char** to_sort, size_t ct);
char** merge(char** a1, char** a2, size_t l1, size_t l2);
char** find(char** array, size_t len, char* to_find, bool sorted);

#endif
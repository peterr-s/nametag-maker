#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include "class.h"

#define SORT_FORWARD 1
#define SORT_NONE 0
#define SORT_BACKWARD -1

class** merge_sort_class(class** to_sort, size_t ct);
class** merge_class(class** a1, class** a2, size_t l1, size_t l2);
class* find_class(class** array, size_t len, char* query);

#endif
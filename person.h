#ifndef PERSON_H
#define PERSON_H

#include "class.h"

typedef struct person person;
struct person
{
	char name_first[4095],
		name_last[4095];
	struct class* cl;
};

#endif
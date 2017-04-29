#ifndef PERSON_H
#define PERSON_H

#include "class.h"

typedef struct person person;
struct person
{
	char name[4095];
	struct class* cl;
};

#endif
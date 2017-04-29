#ifndef CLASS_H
#define CLASS_H

#define COLOR_CT 68
const char* colors[COLOR_CT];

typedef struct class class;
struct class
{
	char name[4095];
	char color[15]; // no color name is more than 15 characters
};

#endif
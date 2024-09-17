#ifndef __STADIUM__
#define __STADIUM__

#include "General.h"

typedef struct {
	char* name;
	char code[MAX_STAD_CODE];
	int capacity;
}Stadium;

int initStadiumNoCode(Stadium* stad);
void printStadium(const Stadium* stad);
void generalPrintStadium(const void* s1);
int compareStadByCode(const void* s1,const void* s2);
void freeStadium(Stadium* stad);

#endif


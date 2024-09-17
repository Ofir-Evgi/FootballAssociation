#ifndef __REFEREE__
#define __REFEREE__

#include "General.h"

typedef struct {
	char* name;
	int age;
	int experienceYears;
}Referee;

int initReferee(Referee* ref);
void printReferee(const Referee* ref);
void generalPrintReferee(const void* r1);
void freeReferee(Referee* ref);

#endif


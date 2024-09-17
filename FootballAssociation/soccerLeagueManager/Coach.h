#ifndef __COACH__
#define __COACH__

#include "General.h"

typedef struct
{
	char*	name;
	int		age;
	int		experienceYears;
	char*	teamName;
}Coach;


int	initCoach(Coach* coach,char* teamName);
void printCoach(const Coach* coach);
void freeCoach(Coach* coach);




#endif


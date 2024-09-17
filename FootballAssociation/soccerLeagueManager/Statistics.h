#ifndef __STATISTICS__
#define __STATISTICS__

#include "General.h"

typedef unsigned char BYTE;

typedef struct {
	int numOfRedCards;
	int numOfYellowCards;
	int numOfGoals;
	int dribbling;
	int speed;
	int physicality;
}Statistics;

int initStatistics(Statistics* stat);
void printStatistics(const Statistics* stat);
int	setStatistics(Statistics* stat);

#endif


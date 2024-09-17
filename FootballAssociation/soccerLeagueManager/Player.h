#ifndef __PLAYER__
#define __PLAYER__

#include "General.h"
#include "Statistics.h"

typedef enum {
	eGoalKeeper, eCenterBack, eMidfielder, eStriker, eNofPositions
} ePositions;

static const char* PositionsArr[eNofPositions] = {"GoalKeeper", "CenterBack","Midfielder", "Striker"};


typedef struct {
	char* name;
	int age;
	int shirtNumber;
	ePositions Position;
	Statistics playerStatistics;
}Player;


int initPlayer(Player* player);
void printPlayer(const Player* player);
void generalPrintPlayer(const void* v1);
int comparePlayerByShirtNumber(const void* p1, const void* p2);
int comparePlayerByDribbling(const void* p1, const void* p2);
int comparePlayerBySpeed(const void* p1, const void* p2);
int comparePlayerByPhysicality(const void* p1, const void* p2);
int comparePlayerByName(const void* p1, const void* p2);
void freePlayer(Player* play);
int getPosition();
int comparePlayerByPosition(const void* p1, const void* p2);

#endif


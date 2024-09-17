#ifndef __EVENTS__
#define __EVENTS__

#include "General.h"
#include "Player.h"



typedef enum {
	ePenalty, eYellowCard, eRedCard, eGoal, eNofEvents
} eMatchEvents;

static const char* MatchEventsArr[eNofEvents] = {"Penalty", "Yellow Card", "Red Card", "Goal"};

typedef struct {

	int numOfEvents;
	int minutesArr[MAX_EVENTS_IN_MATCH];
	eMatchEvents eventsArr[MAX_EVENTS_IN_MATCH];
	Player* playerArr[MAX_EVENTS_IN_MATCH];
	Player** redPlayersArr;
	int numOfRedPlayers;
}MatchEvents;

void initMatchEvents(MatchEvents* matchE);
int isPlayerRed(Player* playerIndex, Player** redPlayersArr, int countOfRed);
void freeMatchEvents(MatchEvents* maE);


#endif


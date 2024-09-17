#ifndef __MATCH__
#define __MATCH__

#include "General.h"
#include "Referee.h"
#include "Team.h"
#include "Stadium.h"
#include "MatchEvents.h"
#include "Date.h"

typedef struct {
	Team*		teamA;
	Team*		teamB;
	Stadium		matchStadium;
	Referee		matchRef;
	Date		matchDate;
	MatchEvents* matchEvents;
	int			scoreTeamA;
	int			scoreTeamB;
}Match;

void initMatch(Match* match, Team* teamA, Team* teamB, Referee ref, Stadium stad, Date date);
void printMatch(const Match* match);
void generalPrintMatch(const void* m1);
void setMatchEvents(Match* match, MatchEvents* macthE);
void printMatchEvents(const Match* match, const MatchEvents* machE);
int teamEvent(Match* match, Team* team, MatchEvents* matchE, int index, int* minute);
void freeMatch(Match* match);

#endif


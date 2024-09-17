#ifndef __GTFILE__
#define __GTFILE__

#include "LeaguesManager.h"


int	readLeaguesManagerFromTextFile(LeaguesManager* LM, FILE* tf);
int writeLeaguesManagerToTextFile(const LeaguesManager* LM, FILE* tf);

int	readLeagueFromTextFile(League* league, FILE* tf);
int	writeLeagueToTextFile(const League* league, FILE* tf);
int readTeamsArr(League* league, FILE* tf);
int readMatchesArr(League* league, FILE* tf);
int readRefereesArr(League* league, FILE* tf);
int readStadiumArr(League* league, FILE* tf);
int writeTeamsArr(const League* league, FILE* tf);
int writeMatchesArr(const League* league, FILE* tf);
int writeRefereesArr(const League* league, FILE* tf);
int writeStadiumArr(const League* league, FILE* tf);

int	readMatchFromTextFile(Match* match, FILE* tf);
int	writeMatchToTextFile(const Match* match, FILE* tf);

int	readMatchEventsFromTextFile(MatchEvents* matchE, FILE* tf);
int	writeMatchEventsToTextFile(const MatchEvents* matchE, FILE* tf);

int	readCoachFromTextFile(Coach* coach, FILE* tf);
int	writeCoachToTextFile(const Coach* coach, FILE* tf);

int	readDateFromTextFile(Date* date, FILE* tf);
int	writeDateToTextFile(const Date* date, FILE* tf);

int	readPlayerFromTextFile(Player* player, FILE* tf);
int	writePlayerToTextFile(const Player* player, FILE* tf);

int	readRefereeFromTextFile(Referee* ref, FILE* tf);
int	writeRefereeToTextFile(const Referee* ref, FILE* tf);

int	readStadiumFromTextFile(Stadium* stad, FILE* tf);
int	writeStadiumToTextFile(const Stadium* stad, FILE* tf);

int	readStatisticsFromTextFile(Statistics* stat, FILE* tf);
int writeStatisticsToTextFile(const Statistics* stat, FILE* tf);

int	readTeamFromTextFile(Team* team, FILE* tf);
int	writeTeamToTextFile(const Team* team, FILE* tf);

#endif
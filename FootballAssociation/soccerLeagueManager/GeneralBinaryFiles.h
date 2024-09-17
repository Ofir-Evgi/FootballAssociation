#ifndef __GBFILE__
#define __GBFILE__

#include "LeaguesManager.h"

int	readLeaguesManagerFromBinaryFile(LeaguesManager* LM, FILE* bf);
int writeLeaguesManagerToBinaryFile(const LeaguesManager* LM, FILE* bf);

int	readLeagueFromBinaryFile(League* league, FILE* bf);
int	writeLeagueToBinaryFile(const League* league, FILE* bf);
int readTeamsArrBin(League* league, FILE* bf);
int readMatchesArrBin(League* league, FILE* bf);
int readRefereesArrBin(League* league, FILE* bf);
int readStadiumArrBin(League* league, FILE* bf);
int writeTeamsArrBin(const League* league, FILE* bf);
int writeMatchesArrBin(const League* league, FILE* bf);
int writeRefereesArrBin(const League* league, FILE* bf);
int writeStadiumArrBin(const League* league, FILE* bf);

int	readMatchFromBinaryFile(Match* match, FILE* bf);
int	writeMatchToBinaryFile(const Match* match, FILE* bf);

int	readMatchEventsFromBinaryFile(MatchEvents* matchE, FILE* bf);
int	writeMatchEventsToBinaryFile(const MatchEvents* matchE, FILE* bf);

int	readCoachFromBinaryFile(Coach* coach, FILE* bf);
int	writeCoachToBinaryFile(const Coach* coach, FILE* bf);

int	readDateFromBinaryFile(Date* date, FILE* bf);
int	writeDateToBinaryFile(const Date* date, FILE* bf);

int	readPlayerFromBinaryFile(Player* player, FILE* bf);
int	writePlayerToBinaryFile(const Player* player, FILE* bf);

int	readRefereeFromBinaryFile(Referee* ref, FILE* bf);
int	writeRefereeToBinaryFile(const Referee* ref, FILE* bf);

int	readStadiumFromBinaryFile(Stadium* stad, FILE* bf);
int	writeStadiumToBinaryFile(const Stadium* stad, FILE* bf);

int	readStatisticsFromCompressedBinaryFile(Statistics* stat, FILE* bf);
int writeStatisticsToCompressedBinaryFile(const Statistics* stat, FILE* bf);

int	readTeamFromBinaryFile(Team* team, FILE* bf);
int	writeTeamToBinaryFile(const Team* team, FILE* bf);

#endif
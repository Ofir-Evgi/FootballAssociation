#ifndef __TEAM__
#define __TEAM__

#include "General.h"
#include "Player.h"
#include "Coach.h"

typedef struct {
	char* name;
	Player** playerArr;
	Coach* coach;
	int numOfPlayers;
	int points;
	int sortType;
	int formationType;
}Team;

int initTeam(Team* team);
void printTeam(const Team* team);
void printTeamToList(const Team* team);
int addPlayer(Team* team);
int removePlayer(Team* team, Player* playerToRemove);
int addMinPlayersToTeam(Team* team);
void swapPlayers(Team* team, int playerToRemove);
void generalPrintTeam(const void* t1);
int checkShirtNumberInArray(const Team* team,const int shirtNum);
void setPlayerShirtNum(Team* team, Player* player);
void teamMenu(Team* team);
void sortPlayers(Team* team);
Player* findPlayer(Team* team);
void freeTeam(Team* team);
int teamFormation(Team* team, int centerBacks, int midfielders, int attackingPlayers);
int setTeamFormation(Team* team, int position);
void printFormation(const Team* team, int centerBacks, int midfielders, int attackingPlayers);
void printTeamFormation(const Team* team);
int findFirstPlayerPosition(const Team* team,int position);




#endif


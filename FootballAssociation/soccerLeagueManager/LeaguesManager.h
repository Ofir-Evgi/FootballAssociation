#ifndef __LEAGUESMANAGER__
#define __LEAGUESMANAGER__

#include "General.h"
#include "League.h"

typedef struct {
	LIST leaguesArr;
}LeaguesManager;


int initLeaguesManager(LeaguesManager* LM);
void printLeaguesList(const LeaguesManager* LM);
int addLeague(LeaguesManager* LM);
int deleteLeague(LeaguesManager* LM);
void freeLeaguesManager(LeaguesManager* LM);
int	compareLeaguesByName(const void* l1, const void* l2);
void leagueManagerMenu(LeaguesManager* LM);
League* chooseLeagueFromListByName(LIST* leaguesArr , League* demoL, int(*compare)(const void*, const void*));



#endif


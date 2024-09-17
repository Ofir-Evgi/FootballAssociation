#ifndef __LEAGUE__
#define __LEAGUE__

#include "General.h"
#include "Match.h"
#include "Team.h"
#include "Date.h"
#include "Stadium.h"
#include "Referee.h"

typedef struct {
	char* name;
	char* country;
	Team** teamsArr;
	Match** matchesArr;
	Referee** refereesArr;
	Stadium* stadiumsArr;
	int numOfTeams;
	int numOfMatches;
	int numOfReferees;
	int numOfStadium;
}League;

int initLeague(League* league);
void freeLeague(League* league);
int addTeam(League* league);
int addMatch(League* league);
int addReferee(League* league);
int addStadium(League* league);
void sortTeamArrByPoints(League* league);
void sortMatchArrByDate(League* league);
void sortStadiumArrByCode(League* league);
void sortTeamArrByName(League* league);
void printAllMatches(const League* league);
void printLeague(const League* league);
void printLeagueFromList(const void* l1);
void printLeagueFromListName(const void* l1);
void printLeagueName(const League* league);
void freeLeagueFromList(const void* l1);
int checkUniqueCode(League* league, char* code);
int initStadium(Stadium* stad, League* league);
int	compareMatchByDate(const void* m1, const void* m2);
void getMatchInfoFromLeagueArrays(League* league,int* team1,int* team2,int* ref,int* stad);
void printTeamsArray(const League* league);
void printLeagueTable(const League* league);
void printRefereeArray(const League* league);
void printStadiumArray(const League* league);
int checkIfMatchDateIsUnique(League* league, Date* date);
Match* findMatchByDate(League* league, Date* date);
int compereTeamsByPoints(const void* t1, const void* t2);
void leagueMenu(League* league);
Team* findTeamByName(League* league);
int compereTeamsByName(const void* t1, const void* t2);
int	compareDate(const void* d1, const void* d2);
void swapTeams(League* league, int teamToRemove);
int deleteTeam(League* league, Team* teamToRemove);


#endif


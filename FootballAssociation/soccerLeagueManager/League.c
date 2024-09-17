#include "League.h"


int initLeague(League* league) {
	league->name = getStrExactName("Please enter the league's name: ");
	deleteAllSpaces(league->name);
	FirstCapitalLetter(league->name);
	league->country = getStrExactName("Please enter the league's country name: ");
	deleteAllSpaces(league->country);
	FirstCapitalLetter(league->country);
	league->numOfMatches = 0;
	league->numOfReferees = 0;
	league->numOfStadium = 0;
	league->numOfTeams = 0;
	league->refereesArr = NULL;
	league->stadiumsArr = NULL;
	league->matchesArr = NULL;
	league->teamsArr = NULL;
	return 1;
}

void leagueMenu(League* league) {
	int choice = 1;
	while (choice != -1) {
		printf("\nLeague menu:\n\n 1 - To print league table \n 2 - To print all teams\n 3 - To print all matches\n 4 - To print all referees\n 5 - To print all stadiums\n 6 - To add a team\n 7 - To add a match\n 8 - To add a referee\n 9 - To add a stadium\n10 - To delete a team\n11 - To print match events of a match by its date\n12 - To select a team and enter the team menu\n-1 - To exit this menu\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: {
			qsort(league->teamsArr, league->numOfTeams, sizeof(Team*), compereTeamsByPoints);
			printLeagueTable(league);
			break;
		}
		case 2: {
			if (league->numOfTeams == 0) {
				printf("\nThere's no teams in the league!\n");
			}
			else {
			generalArrayFunction(league->teamsArr, league->numOfTeams, sizeof(Team*), generalPrintTeam);
			}
			break;
		}
		case 3: {
			if (league->numOfMatches == 0) {
				printf("\nThere's no matches in the league!\n");
			}
			else {
			generalArrayFunction(league->matchesArr, league->numOfMatches, sizeof(Match*), generalPrintMatch);
			}
			break;
		}
		case 4: {
			if (league->numOfReferees == 0) {
				printf("\nThere's no referees in the league!\n");
			}
			else {
			generalArrayFunction(league->refereesArr, league->numOfReferees, sizeof(Referee*), generalPrintReferee);
			}
			break;
		}
		case 5: {
			if (league->numOfStadium == 0) {
				printf("\nThere's no stadiums in the league!\n");
			}
			else {
			generalArrayFunction(league->stadiumsArr, league->numOfStadium, sizeof(Stadium), generalPrintStadium);
			}
			break;
		}
		case 6: {
			addTeam(league);
			break;
		}
		case 7: {
			addMatch(league);
			break;
		}
		case 8: {
			addReferee(league);
			break;
		}
		case 9: {
			addStadium(league);
			break;
		}
		case 10: {
			Team* teamToDelete = findTeamByName(league);
			if (!teamToDelete) {
				printf("\nDeleting the team was not successed,\nTry again.\n");
			}
			else {
				if (!deleteTeam(league, teamToDelete)) {
					printf("ERROR!\nFailed to delete the team\n");
				}
			}
			break;
		}
		case 11: {
			if (league->numOfMatches == 0) {
				printf("\nThere's no matches in the league!\n");
			}
			else {
			Date* temp =(Date*)malloc(sizeof(Date));
			generalArrayFunction(league->matchesArr, league->numOfMatches, sizeof(Match*), generalPrintMatch);
			do {
				getCorrectDate(temp);
				if (checkIfMatchDateIsUnique(league, temp)) {
					printf("\nThere's no such match in this date, please enter again\n");
				}
				else {
					break;
				}
			} while (1);
			Match* matchSelect = findMatchByDate( league, temp);
			if (!matchSelect) {
				printf("\nFinding the match was not successed,\nTry again.\n");
			}
			else {
				printMatchEvents(matchSelect, matchSelect->matchEvents);
			}
			free(temp);
			}
			break;
		}
		case 12: {
			if (league->numOfTeams == 0) {
				printf("\nThere's no team to choose!\n");
			}
			else {
				Team* selectedTeam;
				selectedTeam = findTeamByName(league);
				if (!selectedTeam) {
					printf("\nFinding the team was not successed,\nTry again.\n");
				}
				else {
					teamMenu(selectedTeam);
				}
			}
			break;
		}
		case -1: {
			break;
		}

		default:
			printf("Invalid Input!\n");
			break;
		}
	}
}

int deleteTeam(League* league, Team* teamToRemove) {
	for (int i = 0; i < league->numOfTeams - 1; i++)
	{
		if (!compereTeamsByName(&league->teamsArr[i], &teamToRemove)) {
			swapTeams(league, i);
		}
	}
	freeTeam(league->teamsArr[league->numOfTeams - 1]);
	Team** temp = (Team**)realloc(league->teamsArr, (league->numOfTeams - 1) * sizeof(Player*));
	CHECK_RETURN_INT(temp);
	league->teamsArr = temp;
	league->numOfTeams--;
	return 1;
}

void swapTeams(League* league, int teamToRemove) {
	Team* temp;
	temp = league->teamsArr[teamToRemove];
	league->teamsArr[teamToRemove] = league->teamsArr[teamToRemove + 1];
	league->teamsArr[teamToRemove + 1] = temp;
}

void freeLeague(League* league) {
	free(league->name);
	free(league->country);
	if (league->numOfTeams > 0) {
		for (int i = 0; i < league->numOfTeams; i++)
		{
			freeTeam(league->teamsArr[i]);
		}
		free(league->teamsArr);
	}
	if (league->numOfStadium > 0) {
	for (int i = 0; i < league->numOfStadium; i++)
	{
		freeStadium(&league->stadiumsArr[i]);
	}
	free(league->stadiumsArr);
	}
	if (league->numOfReferees > 0) {
	for (int i = 0; i < league->numOfReferees; i++)
	{
		freeReferee(league->refereesArr[i]);
	}
	free(league->refereesArr);
	}
	if (league->numOfMatches > 0) {
	for (int i = 0; i < league->numOfMatches; i++)
	{
		freeMatch(league->matchesArr[i]);
	}
	free(league->matchesArr);
	}
	free(league);

}

int	addTeam(League* league) {
	Team** temp;
	Team* team = (Team*)malloc(sizeof(Team));
	CHECK_RETURN_INT(team);
	if (!initTeam(team)) {
		return 0;
	}
	league->numOfTeams++;
	temp = (Team**)realloc(league->teamsArr,league->numOfTeams*sizeof(Team*));
	if (!temp) {
		freeTeam(team);
		league->numOfTeams--;
		return 0;
	}
	league->teamsArr = temp;
	league->teamsArr[league->numOfTeams - 1] = team;
	return 1;
}
int	addMatch(League* league) {
	if (league->numOfTeams < 2) {
		printf("Cannot create a match without at least 2 teams.\n");
		return 0;
	}
	if (league->numOfReferees < 1) {
		printf("Cannot create a match without a referee.\n");
		return 0;
	}
	if (league->numOfStadium < 1) {
		printf("Cannot create a match without a stadium.\n");
		return 0;
	}
	int team1, team2, ref, stad;
	Match** temp;
	Match* mat = (Match*)malloc(sizeof(Match));
	CHECK_RETURN_INT(mat);
	Date* date = (Date*)malloc(sizeof(Date));
	CHECK_RETURN_INT(date);
	
	do {
		getCorrectDate(date);
	if (!checkIfMatchDateIsUnique(league, date)){
		printf("ERROR! There is a match in that date\n");
	}
	else {
		break;
	}
	} while (1);
	getMatchInfoFromLeagueArrays(league,&team1,&team2,&ref,&stad);
	initMatch(mat,league->teamsArr[team1-1], league->teamsArr[team2-1], *league->refereesArr[ref-1], league->stadiumsArr[stad-1],*date);
	league->numOfMatches++;
	temp = (Match**)realloc(league->matchesArr, league->numOfMatches * sizeof(Match*));
	if (!temp) {
		freeMatch(mat);
		league->numOfMatches--;
		return 0;
	}
	mat->matchEvents = (MatchEvents*)malloc(sizeof(MatchEvents));
	CHECK_RETURN_INT(mat->matchEvents);
	initMatchEvents(mat->matchEvents);
	setMatchEvents(mat, mat->matchEvents);
	league->matchesArr = temp;
	league->matchesArr[league->numOfMatches - 1] = mat;
	sortMatchArrByDate(league);
	return 1;
}
int	checkIfMatchDateIsUnique(League* league, Date* date) {
	for (int i = 0; i < league->numOfMatches; i++)
	{
		if (!compareDate(&league->matchesArr[i]->matchDate, date)) {
			return 0;
		}
	}
	return 1;
}
void getMatchInfoFromLeagueArrays(League* league,int* team1, int* team2, int* ref, int* stad) {
	printf("\nPlease choose Team A for the match:\n\n");
	printTeamsArray(league);
	scanf("%d", team1);
	do
	{
		printf("\nPlease choose Team B for the match:\n\n");
		printTeamsArray(league);
		scanf("%d", team2);
		if (*team1 == *team2) {
			printf("\nERROR! cant choose the same team!\n");
		}
	} while (*team1 == *team2);
	printf("\nPlease choose a referee for the match:\n\n");
	printRefereeArray(league);
	scanf("%d", ref);
	printf("\nPlease choose a stadium for the match:\n\n");
	printStadiumArray(league);
	scanf("%d", stad);
}
int addReferee(League* league) {
	Referee** temp;
	Referee* ref = (Referee*)malloc(sizeof(Referee));
	CHECK_RETURN_INT(ref);
	initReferee(ref);
	league->numOfReferees++;
	temp = (Referee**)realloc(league->refereesArr,league->numOfReferees*sizeof(Referee*));
	if (!temp) {
		freeReferee(ref);
		league->numOfReferees--;
		return 0;
	}
	league->refereesArr = temp;
	league->refereesArr[league->numOfReferees - 1] = ref;
	return 1;
}
int addStadium(League* league) {
	Stadium* temp;
	Stadium stad = *(Stadium*)malloc(sizeof(Stadium));
	CHECK_RETURN_INT(&stad);
	initStadium(&stad, league);
	league->numOfStadium++;
	temp = (Stadium*)realloc(league->stadiumsArr, league->numOfStadium*sizeof(Stadium));
	if (!temp) {
		freeStadium(&stad);
		league->numOfStadium--;
		return 0;
	}
	league->stadiumsArr = temp;
	league->stadiumsArr[league->numOfStadium - 1] = stad;
	sortStadiumArrByCode(league);
	return 1;
}
Team* findTeamByName(League* league) {
	sortTeamArrByName(league);
	printf("\nPlease enter the team name from the list : \n\n");
	printTeamsArray(league);
	char* selectedName = getStrExactName("\nName: \t");
	deleteAllSpaces(selectedName);
	FirstCapitalLetter(selectedName);
	Team* tempTeam = (Team*)malloc(sizeof(Team));
	CHECK_RETURN_NULL(tempTeam);
	tempTeam->name = selectedName;
	Team** selectedTeam =(Team**)bsearch(&tempTeam, league->teamsArr, league->numOfTeams, sizeof(Team*), compereTeamsByName);
	free(tempTeam->name);
	free(tempTeam);
	CHECK_RETURN_NULL(selectedTeam);
	return (*selectedTeam);
}
void sortTeamArrByPoints(League* league) {
	qsort(league->teamsArr, league->numOfTeams, sizeof(Team*), compereTeamsByPoints);
}
void sortTeamArrByName(League* league) {
	qsort(league->teamsArr, league->numOfTeams, sizeof(Team*), compereTeamsByName);
}
void sortMatchArrByDate(League* league) {
	qsort(league->matchesArr, league->numOfMatches, sizeof(Match*), compareMatchByDate);
}
Match* findMatchByDate(League* league, Date* date) {
	Match* demo = (Match*)malloc(sizeof(Match));
	CHECK_RETURN_NULL(demo);
	demo->matchDate = *date;
	Match** temp = (Match**)bsearch(&demo, league->matchesArr, league->numOfMatches, sizeof(Match*), compareMatchByDate);
	return(*temp);
}
void sortStadiumArrByCode(League* league) {
	qsort(league->stadiumsArr, league->numOfStadium, sizeof(Stadium), compareStadByCode);
}
void printAllMatches(const League* league) {
	for (int i = 0; i < league->numOfMatches; i++)
	{
		printf("%d)\t", i + 1);
		printMatch(league->matchesArr[i]);
		printf("\n");
	}
}
void printLeagueTable(const League* league) {
	printf("League's name: %s\n\n", league->name);
	PRINT_HORIZONTAL_LINE(37);
	printf("|  Pos |         Team         | PTS |\n");
	PRINT_HORIZONTAL_LINE(37);
	for (int i = 0; i < league->numOfTeams; i++)
	{
		printf("|  %2d  | %-20s | %2d  |\n", i+1, league->teamsArr[i]->name, league->teamsArr[i]->points);
		PRINT_HORIZONTAL_LINE(37);
	}
}
void printLeague(const League* league) {
	printf("\nLeague's name: %s \tLeague's country: %s \tNumber of teams: %d \n\n", league->name, league->country, league->numOfTeams);
}
void printLeagueName(const League* league) {
	printf("\nLeague's name: \t %s \n\n", league->name);
}
int compereTeamsByPoints(const void* t1,const void* t2)
{
	const Team* team1 = *(const Team**)t1;
	const Team* team2 = *(const Team**)t2;
	return team2->points - team1->points;
}
int compereTeamsByName(const void* t1, const void* t2)
{
	const Team* team1 = *(const Team**)t1;
	const Team* team2 = *(const Team**)t2;
	return strcmp( team1->name , team2->name);
}
int	compareMatchByDate(const void* m1, const void* m2) {
	const Match* pMat1 = *(const Match**)m1;
	const Match* pMat2 = *(const Match**)m2;

	return compareDate(&pMat1->matchDate, &pMat2->matchDate);

}
int	compareDate(const void* d1, const void* d2) {
	const Date* pD1 = (const Date*)d1;
	const Date* pD2 = (const Date*)d2;

	if (pD1->year != pD2->year) {
		return (pD1->year - pD2->year);
	}
	if (pD1->month != pD2->month) {
		return (pD1->month - pD2->month);
	}
	return (pD1->day - pD2->day);
}
void printLeagueFromList(const void* l1) {
	const League* lea1 = (const League*)l1;
	printLeague(lea1);
}
void printLeagueFromListName(const void* l1) {
	const League* lea1 = (const League*)l1;
	printLeagueName(lea1);
}



void freeLeagueFromList(const void* l1) {
	const League* lea1 = *(const League**)l1;
	freeLeague(lea1);
}

int initStadium(Stadium* stad, League* league) {
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Please enter stadium code  - %d UPPER CASE letters:\t", STAD_CODE);
		myGets(temp, MAX_STR_LEN);
		if (strlen(temp) != STAD_CODE)
		{
			printf("Code should be %d letters\n", STAD_CODE);
			ok = 0;
		}
		else {
			for (int i = 0; i < STAD_CODE; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Needs to be upper case letters\n");
					ok = 0;
					break;
				}
			}
		}
		if (!checkUniqueCode(league,temp)) {
			printf("Code is not unique!\n");
			ok = 0;
		}
	} while (!ok);
	strcpy(stad->code, temp);
	initStadiumNoCode(stad);
	return 1;
}

int checkUniqueCode(League* league, char* code) {
	for (int i = 0; i < league->numOfStadium; i++)
	{
		if (!strcmp(league->stadiumsArr[i].name,code)) {
			return 0;
		}
	}
	return 1;
}

void printTeamsArray(const League* league) {
	for (int i = 0; i < league->numOfTeams; i++)
	{
		printf("%d) %s\n" , i+1, league->teamsArr[i]->name);
	}
}

void printRefereeArray(const League* league) {
	for (int i = 0; i < league->numOfReferees; i++)
	{
		printf("%d) %s\n", i + 1, league->refereesArr[i]->name);
	}
}

void printStadiumArray(const League* league) {
	for (int i = 0; i < league->numOfStadium; i++)
	{
		printf("%d) %s\n", i + 1, league->stadiumsArr[i].name);
	}
}



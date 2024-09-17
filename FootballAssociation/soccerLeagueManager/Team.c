#include "Team.h"


int initTeam(Team* team) {
	do
	{
	team->name = getStrExactName("Please enter the team's name: ");
	CHECK_RETURN_INT(team->name);
	deleteAllSpaces(team->name);
	FirstCapitalLetter(team->name);
	if (strlen(team->name) > MAXIMUM) {
		printf("You cross the length limit, which is %d characters!\n", MAXIMUM);
		free(team->name);
	}
	else {
		break;
	}
	} while (1);
	team->numOfPlayers = 0;
	Coach* coa = (Coach*)malloc(sizeof(Coach));
	CHECK_RETURN_INT(coa);
	if (!initCoach(coa, team->name)) {
		return 0;
	}
	team->coach = coa;
	team->playerArr = NULL;
	do{} while (!addMinPlayersToTeam(team));
	team->points = 0;
	team->sortType = 0;
	return 1;
}

void printTeam(const Team* team) {
	printf("\n\nTeam's Name: %s\n\nNumber of players in the team: %d\n\n", team->name, team->numOfPlayers);
	printCoach(team->coach);
	PRINT_HORIZONTAL_LINE(90);
	generalArrayFunction(team->playerArr, team->numOfPlayers, sizeof(Player*), generalPrintPlayer);

}

void printTeamToList(const Team* team) {
	printf("\n\nTeam's Name: %s\n\nNumber of players in the team: %d\n", team->name, team->numOfPlayers);
	printCoach(team->coach);
	PRINT_HORIZONTAL_LINE(90);
}

int addPlayer(Team* team) {
	if (team->numOfPlayers >= MAX_TEAM_PLAYERS) {
		printf("ERROR!\nYou are in the maximum capacity of players in the team!\n");
		return 0;
	}
	Player* player = (Player*)malloc(sizeof(Player));
	CHECK_RETURN_INT(player);
	player->Position = getPosition();
	if (!initPlayer(player)) {
		return 0;
	}
	setPlayerShirtNum(team, player);
	Player** temp = (Player**)realloc(team->playerArr , (team->numOfPlayers + 1)*sizeof(Player*));
	if (!temp) {
		freePlayer(player);
		return 0;
	}
	team->playerArr = temp;
	team->playerArr[team->numOfPlayers] = player;
	team->numOfPlayers++;
	return 1;
}

void setPlayerShirtNum(Team* team, Player* player) {
	int shirtNum = 0;
	do
	{
		printf("Please enter the player's shirt number, needs to be between %d - %d: ", MIN_SHIRT_NUM, MAX_STAT);
		scanf("%d", &shirtNum);
		if (shirtNum< MIN_SHIRT_NUM || shirtNum > MAX_STAT) {
			printf("Shirt number out of range\n");
		}
		else if (checkShirtNumberInArray(team, shirtNum)) {
			printf("There is a player whis thet shirt number\n");
		}
		else {
			break;
		}
	} while (1);
	player->shirtNumber = shirtNum;
}

int checkShirtNumberInArray(const Team* team,const int shirtNum) {
	for (int i = 0; i < team->numOfPlayers; i++)
	{
		if (shirtNum == team->playerArr[i]->shirtNumber) {
			return 1;
		}
	}
	return 0;
}

int removePlayer(Team* team, Player* playerToRemove) {
	if (team->numOfPlayers <= MIN_TEAM_PLAYERS) {
		printf("ERROR!\nYou are in the minimum capacity of players in the team!\n");
		return 0;
	}
	for (int i = 0; i < team->numOfPlayers - 1; i++)
	{
		if (!comparePlayerByShirtNumber(&team->playerArr[i], &playerToRemove)) {
		swapPlayers(team,i);
		}
	}
	freePlayer(team->playerArr[team->numOfPlayers-1]);
	//free(team->playerArr[team->numOfPlayers - 1]);
	Player** temp = (Player**)realloc(team->playerArr, (team->numOfPlayers - 1) * sizeof(Player*));
	CHECK_RETURN_INT(temp);
	team->playerArr = temp;
	team->numOfPlayers--;
	return 1;
}

int addMinPlayersToTeam(Team* team) {
	printf("Min players at the team should be %d players \n", MIN_TEAM_PLAYERS);
	team->playerArr = (Player**)malloc(MIN_TEAM_PLAYERS * sizeof(Player*));
	CHECK_RETURN_INT(team->playerArr);
	int choice = 1;
	while (choice != -1) {
		printf("Please select which team's formation do you want: \n1) 4-3-3\n2) 5-4-1\n3) 4-4-2\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: {
			team->formationType = 1;
			if (!teamFormation(team, 4, 3, 3)) {
				printf("ERROR!\nThere was a problem please try again\n");
			}
			else {
			choice = -1;
			}

			break;
		}
		case 2: {
			team->formationType = 2;
			if (!teamFormation(team, 5, 4, 1)) {
				printf("ERROR!\nThere was a problem please try again\n");
			}
			else {
				choice = -1;
			}
			break;

		}
		case 3: {
			team->formationType = 3;
			if (!teamFormation(team, 4, 4, 2)) {
				printf("ERROR!\nThere was a problem please try again\n");
			}
			else {
				choice = -1;
			}
			break;
		}

		default:
			printf("Invalid Input!\nPlease enter again!\n");
			break;
		}
	}
	return 1;
}

void swapPlayers(Team* team, int playerToRemove) {
	Player* temp;
	temp = team->playerArr[playerToRemove];
	team->playerArr[playerToRemove] = team->playerArr[playerToRemove + 1];
	team->playerArr[playerToRemove + 1] = temp;
}

void generalPrintTeam(const void* t1) {
	const Team* team = *(const Team**)t1;
	printTeamToList(team);
}

void teamMenu(Team* team) {
	int choice = 1;

	while (choice != -1) {
		printf("\nTeam menu:\n\n 1 - To print the team's squad \n 2 - To add a player\n 3 - To sort the players\n 4 - To find a player\n 5 - To remove a player\n 6 - To print the team formation\n-1 - To exit this menu\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: {
			printTeam(team);
			break;
		}
		case 2: {
			addPlayer(team);
			team->sortType = 0;
			break;
		}
		case 3: {
			sortPlayers(team);
			break;
		}
		case 4: {
			Player* pTemp = findPlayer(team);
			if (!pTemp) {
				printf("Finding the player was not successed,\nTry again.\n");
			}
			else {
				printPlayer(pTemp);
			}

			break;
		}
		case 5: {
			Player* remPlayer = findPlayer(team);
			if (!remPlayer) {
				printf("Deleting the player was not successed,\nTry again.\n");
			}
			else {
			removePlayer(team, remPlayer);
			}

			break;
		}
		case 6: {
			printTeamFormation(team);
			team->sortType = -1;
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

void sortPlayers(Team* team) {
	int num = 0;
	while (num != -1) {
	printf("\nBase on which field do yo want to sort: \n1 - By Dribbling\n2 - By Physicality\n3 - By Speed\n4 - By Name\n5 - By Shirt Number\n");
	scanf("%d", &num);
	switch (num)
	{
	case 1: {
		qsort(team->playerArr, team->numOfPlayers, sizeof(Player*), comparePlayerByDribbling);
		team->sortType = num;
		num = -1;
		break;
	}
	case 2: {
		qsort(team->playerArr, team->numOfPlayers, sizeof(Player*), comparePlayerByPhysicality);
		team->sortType = num;
		num = -1;
		break;
	}
	case 3: {
		qsort(team->playerArr, team->numOfPlayers, sizeof(Player*), comparePlayerBySpeed);
		team->sortType = num;
		num = -1;
		break;
	}
	case 4: {
		qsort(team->playerArr, team->numOfPlayers, sizeof(Player*), comparePlayerByName);
		team->sortType = num;
		num = -1;
		break;
	}
	case 5: {
		qsort(team->playerArr, team->numOfPlayers, sizeof(Player*), comparePlayerByShirtNumber);
		team->sortType = num;
		num = -1;
		break;
	}

	default:
		printf("Invalid Input!\n");
		break;
	}
	}
}

void freeTeam(Team* team) {
	free(team->name);
	if (team->coach->name) {
	freeCoach(team->coach);
	}
	for (int i = 0; i < team->numOfPlayers; i++)
	{
		freePlayer(team->playerArr[i]);
	}
	free(team->playerArr);

}

Player* findPlayer(Team* team) {
	int shirtNum = 0;
	if (team->sortType != 5) {
		printf("ERROR!\nYou can find a player only by his shirt number.\n");
		return NULL;
	}
	printf("Please enter a shirt number for the search: \n");
	scanf("%d", &shirtNum);
	if (!checkShirtNumberInArray(team, shirtNum)) {
		printf("There's no such player with this number in the team!\n");
		return NULL;
	}
	Player* demo = (Player*)malloc(sizeof(Player));
	if (!demo) {
		return NULL;
	}
	demo->shirtNumber = shirtNum;
	Player** pTemp = (Player**)bsearch(&demo, team->playerArr, team->numOfPlayers, sizeof(Player*), comparePlayerByShirtNumber);
	free(demo);
	return (*pTemp);
}

int teamFormation(Team* team, int centerBacks, int midfielders, int attackingPlayers) {
	 
	printf("\nPlease enter a %s\n\n", PositionsArr[eGoalKeeper]);
	setTeamFormation( team,  eGoalKeeper);

		printf("\nPlease enter %d %ss\n\n", centerBacks, PositionsArr[eCenterBack]);
	for (int i = 0; i < centerBacks; i++)
	{
		if (!setTeamFormation(team, eCenterBack)) {
			return 0;
		}
	}
	printf("\nPlease enter %d %ss\n\n", midfielders, PositionsArr[eMidfielder]);
	for (int i = 0; i < midfielders; i++)
	{
		if (!setTeamFormation(team, eMidfielder)) {
			return 0;
		 }
	}
	printf("\nPlease enter %d %ss\n\n", attackingPlayers, PositionsArr[eStriker]);
	for (int i = 0; i < attackingPlayers; i++)
	{
		if (!setTeamFormation(team, eStriker)) {
			return 0;
		 }
	}

	if (team->numOfPlayers != MIN_TEAM_PLAYERS) {
		return 0;
	}

		return 1;
}

int setTeamFormation(Team* team, int position) {

	Player* pPlayer = (Player*)malloc(sizeof(Player));
	if (!initPlayer(pPlayer)) {
		return 0;
	}
	setPlayerShirtNum(team, pPlayer);
	pPlayer->Position = position;
	team->playerArr[team->numOfPlayers] = pPlayer;
	team->numOfPlayers++;
	return 1;
}


void printTeamFormation(const Team* team) {
	printf("The team formation:\n");
	switch (team->formationType)
	{
	case 1: {
		printFormation(team, 4, 3, 3);
		break;
	}
	case 2: {
		printFormation(team, 5, 4, 1);
		break;
	}
	case 3: {
		printFormation(team, 4, 4, 2);
		break;
	}
	default:
		break;
	}
}

void printFormation(const Team* team, int centerBacks, int midfielders, int attackingPlayers) {
	qsort(team->playerArr, team->numOfPlayers, sizeof(Player*), comparePlayerByPosition);
	int tempCenterBacks = centerBacks;
	int tempMidfielders = midfielders;
	int tempAttackingPlayers = attackingPlayers;
	int pGoalKeeper = findFirstPlayerPosition(team, 0);
	int pCenterBack = findFirstPlayerPosition(team,1);
	int pMidfielder = findFirstPlayerPosition(team, 2);
	int pAttackingPlayer = findFirstPlayerPosition(team, 3);

	for (int i = 0; i < 20; i++)
	{
		printf("\t\t|");
		for (int j = 0; j < 23; j++)
		{
			if (i == 0|| i==19 || i==9 ) { printf("--"); }
			else if((i == 2 && (j <= 23 / 2 + 2 && j >= 23 / 2 - 2))){ printf("__"); }
			else if ((i == 1 || i == 2) && (j == 23 / 2 - 2)) {printf("| ");}
			else if ((i == 1 || i == 2) && (j == 23 / 2 + 2 )) { printf(" |"); }

			else if( i == 1){
				if (j == 23 / 2) {
					if (team->playerArr[pGoalKeeper]->shirtNumber < 10 && j != 0) {
						printf("%d%d", 0, team->playerArr[pGoalKeeper]->shirtNumber);
					}
					else {
					printf("%d", team->playerArr[pGoalKeeper]->shirtNumber);
					}
				}
				else {
					printf("  ");
				}
			}
			else if (i == 4) {
				if (j % (23/(tempCenterBacks + 1)) == 0 && centerBacks > 0 && j != 0) {
					if (team->playerArr[pCenterBack + centerBacks - 1]->shirtNumber < 10) {
						printf("%d%d", 0, team->playerArr[pCenterBack + centerBacks - 1]->shirtNumber);
					}
					else {
						printf("%d", team->playerArr[pCenterBack + centerBacks - 1]->shirtNumber);
					}
					centerBacks--;
				}
				else {
					printf("  ");
				}
			}
			else if (i == 10) {
				if (j % (23 / (tempMidfielders + 1)) == 0 && midfielders > 0 && j != 0) {
					if (team->playerArr[pMidfielder + midfielders - 1]->shirtNumber < 10) {
						printf("%d%d", 0, team->playerArr[pMidfielder + midfielders - 1]->shirtNumber);
					}
					else {
						printf("%d", team->playerArr[pMidfielder + midfielders - 1]->shirtNumber);
					}
					midfielders--;
				}
				else {
					printf("  ");
				}
			}
			else if (i == 14) {
				if (j % (23 / (tempAttackingPlayers + 1)) == 0 && attackingPlayers > 0 && j != 0) {
					if (team->playerArr[pAttackingPlayer + attackingPlayers - 1]->shirtNumber < 10) {
						printf("%d%d", 0, team->playerArr[pAttackingPlayer + attackingPlayers - 1]->shirtNumber);
					}
					else {
						printf("%d", team->playerArr[pAttackingPlayer + attackingPlayers - 1]->shirtNumber);
					}
					attackingPlayers--;
				}
				else {
					printf("  ");
				}
			}
			else{ printf("  "); }
		}
		printf("|\n");
	}
}

int findFirstPlayerPosition(const Team* team, int position) {
	for (int i = 0; i < team->numOfPlayers; i++)
	{
		if (team->playerArr[i]->Position == position) {
			return i;
		}
	}
	return -1;
}


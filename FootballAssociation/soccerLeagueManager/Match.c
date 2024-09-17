#include "Match.h"

void initMatch(Match* match,Team* teamA, Team* teamB, Referee ref, Stadium stad, Date date) {
	match->teamA = teamA;
	match->teamB = teamB;
	match->matchRef = ref;
	match->matchStadium = stad;
	match->matchDate = date;
	match->scoreTeamA = 0;
	match->scoreTeamB = 0;
}

void printMatch(const Match* match) {
	printf("Match on ");
	printDate(&match->matchDate);
	printf("\n\nTeams: \t%s VS %s \tStadium: %s \tReferee: %s \tFinal Score: %d:%d\n\n", match->teamA->name, match->teamB->name,match->matchStadium.name, match->matchRef.name, match->scoreTeamA, match->scoreTeamB);
	PRINT_HORIZONTAL_LINE(120);
}
		
void setMatchEvents(Match* match, MatchEvents* matchE) {
	int minute = 0;
	matchE->numOfEvents = generateRandomNumber(2, MAX_EVENTS_IN_MATCH);
	for (int i = 0; i < matchE->numOfEvents; i++)
	{
		int teamSelect = generateRandomNumber(MINIMUM, 1);
		if (!teamSelect) {
			match->scoreTeamA += teamEvent(match, match->teamA, matchE, i, &minute);
		}
		else {
			match->scoreTeamB += teamEvent(match, match->teamB, matchE, i, &minute);
		}
	}
	if (match->scoreTeamA > match->scoreTeamB) {
		match->teamA->points += 3;
	}
	else if (match->scoreTeamA < match->scoreTeamB) {
		match->teamB->points += 3;
	}
	else {
		match->teamA->points += 1;
		match->teamB->points += 1;
	}
}

int teamEvent(Match* match, Team* team, MatchEvents* matchE, int index, int* minute) {
	int score = 0;
	*minute = generateRandomNumber(*minute + 1, MAX_MATCH_TIME - (matchE->numOfEvents - 1 - index));
	int playerIndex;
	do {
		playerIndex = generateRandomNumber(MINIMUM, team->numOfPlayers - 1);
	} while (isPlayerRed(team->playerArr[playerIndex], matchE->redPlayersArr, matchE->numOfRedPlayers));
	int event = generateRandomNumber(MINIMUM, eNofEvents - 1);
	switch (event)
	{
	case 0: { 
		int ifScore = generateRandomNumber(MINIMUM, 1);
		matchE->eventsArr[index] = event;
		if (ifScore) {
			team->playerArr[playerIndex]->playerStatistics.numOfGoals++;
			score++;
			matchE->eventsArr[index] = 3;
		}
		matchE->minutesArr[index] = *minute;
		matchE->playerArr[index] = team->playerArr[playerIndex];
		break;
	}
	case 1: { 
		Player** tempArr;
		for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
		{
			if (matchE->eventsArr[i] == 1 && !comparePlayerByName(&matchE->playerArr[i], &team->playerArr[playerIndex])) {
				team->playerArr[playerIndex]->playerStatistics.numOfRedCards++;
				tempArr = (Player**)realloc(matchE->redPlayersArr,(matchE->numOfRedPlayers + 1)*sizeof(Player*) );
				if (!tempArr) {
					break;
				}
				matchE->redPlayersArr = tempArr;
				matchE->redPlayersArr[matchE->numOfRedPlayers] = team->playerArr[playerIndex];
				matchE->numOfRedPlayers++;
				matchE->eventsArr[index] = 2;
			}
			if (matchE->eventsArr[i] == -1) {
				i = MAX_EVENTS_IN_MATCH;
			}
		}
		team->playerArr[playerIndex]->playerStatistics.numOfYellowCards++;
		matchE->minutesArr[index] = *minute;
		matchE->eventsArr[index] = event;
		matchE->playerArr[index] = team->playerArr[playerIndex];
		break;
	}

	case 2: { 
		Player** tempArr;
		tempArr = (Player**)realloc(matchE->redPlayersArr, (matchE->numOfRedPlayers+1) * sizeof(Player*));
		if (!tempArr) {
			free(tempArr);
			break;
		}
		matchE->redPlayersArr = tempArr;
		matchE->redPlayersArr[matchE->numOfRedPlayers] = team->playerArr[playerIndex];
		team->playerArr[playerIndex]->playerStatistics.numOfRedCards++;
		matchE->eventsArr[index] = event;
		matchE->minutesArr[index] = *minute;
		matchE->playerArr[index] = team->playerArr[playerIndex];
		matchE->numOfRedPlayers++;
		break;
	}

	case 3: { 
		team->playerArr[playerIndex]->playerStatistics.numOfGoals++;
		score++;
		matchE->eventsArr[index] = event;
		matchE->minutesArr[index] = *minute;
		matchE->playerArr[index] = team->playerArr[playerIndex];
		break;
	}

	default:

		break;
	}
	return score;
}

void printMatchEvents(const Match * match, const MatchEvents * matchE){
	printf("\n%s VS %s Match Events:\n\n", match->teamA->name, match->teamB->name);
	for (int i = 0; i < matchE->numOfEvents; i++)
	{
		if (matchE->eventsArr[i] == 3) {
			printf("Minute %d':\t%s scored by %s\n", matchE->minutesArr[i], MatchEventsArr[matchE->eventsArr[i]], matchE->playerArr[i]->name);
		}
		else {
			printf("Minute %d':\t%s for %s\n", matchE->minutesArr[i], MatchEventsArr[matchE->eventsArr[i]], matchE->playerArr[i]->name);
		}
	}
	printf("\nFinal Score: %d:%d\n\n", match->scoreTeamA, match->scoreTeamB);

}

void freeMatch(Match* match) {
	freeTeam(match->teamA);
	free(match->teamA);
	freeTeam(match->teamB);
	free(match->teamB);
	freeStadium(&match->matchStadium);
	free(&match->matchStadium);
	freeReferee(&match->matchRef);
	free(&match->matchRef);
	free(&match->matchDate);
	freeMatchEvents(match->matchEvents);
	free(match->matchEvents);
	free(match);
}

void generalPrintMatch(const void* m1) {
	const Match* mat1 = *(const Match**)m1;
	printMatch(mat1);
}


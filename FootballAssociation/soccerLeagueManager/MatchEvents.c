#include "MatchEvents.h"

void initMatchEvents(MatchEvents* matchE) {
	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		matchE->eventsArr[i] = -1;
		matchE->minutesArr[i] = 0;
	}
	matchE->numOfEvents = 0;
	matchE->numOfRedPlayers = 0;
	matchE->redPlayersArr = NULL;
}

int isPlayerRed(Player* playerIndex, Player** redPlayersArr, int countOfRed) {
	for (int i = 0; i < countOfRed; i++)
	{
		if (!comparePlayerByName(&playerIndex, &redPlayersArr[i])) {
			return 1;
		}
	}
	return 0;
}

void freeMatchEvents(MatchEvents* maE) {
	int i = 0;
	while (maE->playerArr[i] != NULL) {
		freePlayer(maE->playerArr[i]);
		free(maE->playerArr[i]);
		i++;
	}
	for (int i = 0; i < maE->numOfRedPlayers; i++)
	{
		freePlayer(maE->redPlayersArr[i]);
		free(maE->redPlayersArr[i]);
	}
	free(maE);
}

#include "Player.h"

int initPlayer(Player* player) {
	int num = 0;
	player->name =  getStrExactName("Please enter the player's name: ");
	CHECK_RETURN_INT(player->name);
	deleteAllSpaces(player->name);
	FirstCapitalLetter(player->name);
	do
	{
		printf("\nPlease enter player's age:\t");
		scanf("%d", &num);
	} while (num < MIN_AGE || num > MAX_PLAYER_AGE);
	player->age = num;
	player->shirtNumber = 0;
	initStatistics(&player->playerStatistics);
	setStatistics(&player->playerStatistics);
	return 1;
}

void printPlayer(const Player* player) {
	printf("Player's info:\n\nName: %s\tAge: %d \tNumber: %d\tPisition: %s" ,player->name,player->age,player->shirtNumber,PositionsArr[player->Position]);
	printStatistics(&player->playerStatistics);
	PRINT_HORIZONTAL_LINE(80);
}

void generalPrintPlayer(const void* p1) {
	const Player* play1 = *(const Player**)p1;
	printPlayer(play1);
}

int comparePlayerByShirtNumber(const void* p1, const void* p2) {
	const Player* play1 = *(const Player**)p1;
	const Player* play2 = *(const Player**)p2;
	return MINUS(play1->shirtNumber, play2->shirtNumber);

}

int comparePlayerByName(const void* p1, const void* p2) {
	const Player* play1 = *(const Player**)p1;
	const Player* play2 = *(const Player**)p2;
	return strcmp(play1->name, play2->name);
}

int comparePlayerByDribbling(const void* p1, const void* p2) {
	const Player* play1 = *(const Player**)p1;
	const Player* play2 = *(const Player**)p2;
	return MINUS(play1->playerStatistics.dribbling, play2->playerStatistics.dribbling);

}

int comparePlayerBySpeed(const void* p1, const void* p2) {
	const Player* play1 = *(const Player**)p1;
	const Player* play2 = *(const Player**)p2;
	return MINUS(play1->playerStatistics.speed, play2->playerStatistics.speed);
}

int comparePlayerByPhysicality(const void* p1, const void* p2) {
	const Player* play1 = *(const Player**)p1;
	const Player* play2 = *(const Player**)p2;
	return MINUS(play1->playerStatistics.physicality, play2->playerStatistics.physicality);
	
}

int getPosition() {
	int num = 0;
	do
	{
	printf("Please select the player's position: \n\n");
	for (int i = 0; i < eNofPositions; i++)
	{
		printf("%d) %s \n", i, PositionsArr[i]);
	}
	scanf("%d", &num);
	} while (num < 0 || num > eNofPositions-1);
	return num;
}

void freePlayer(Player* player) {
	free(player->name);
	free(player);
}

int comparePlayerByPosition(const void* p1, const void* p2) {
	const Player* play1 = *(const Player**)p1;
	const Player* play2 = *(const Player**)p2;
	return MINUS(play1->Position, play2->Position);

}

#include "LeaguesManager.h"
#include "GeneralTextFiles.h"
#include "GeneralBinaryFiles.h"

#define TEXT_FILE "FootballAssociation.txt"
#define BIN_FILE "FootballAssociation.bin"

void main()
{
	srand((unsigned int)time(NULL));
	int choice = 1;
	LeaguesManager* leagueManager = (LeaguesManager*)malloc(sizeof(LeaguesManager));
	initLeaguesManager(leagueManager);
	while (choice != -1) {
		printf("Please select which way do you want to create a leagues manager: \n 1 - To upload leagues manager from a text file \n 2 - To upload leagues manager from a binary file \n-1 - To close this menu\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: {
			FILE* readFromTextFile = fopen(TEXT_FILE, "r");
			if (!readLeaguesManagerFromTextFile(leagueManager, readFromTextFile)) {
				printf("\nFailed reading the league manager\n");
			}
			leagueManagerMenu(leagueManager);
			fclose(readFromTextFile);
			break;
		}
		case 2: {
			FILE* readFromBinaryFile = fopen(BIN_FILE, "rb");
			if (!readLeaguesManagerFromBinaryFile(leagueManager, readFromBinaryFile)) {
				printf("\nFailed reading the league manager\n");
			}
			leagueManagerMenu(leagueManager);
			fclose(readFromBinaryFile);
			break;
		}
		case -1: {
			FILE* writeToTextFile = fopen(TEXT_FILE, "w");
			FILE* writeToBinaryFile = fopen(BIN_FILE, "wb");
			writeLeaguesManagerToTextFile(leagueManager, writeToTextFile);
			writeLeaguesManagerToBinaryFile(leagueManager, writeToBinaryFile);
			fclose(writeToTextFile);
			fclose(writeToBinaryFile);
			printf("\nGoodBye!\n");
			break;
		}
		default:
			printf("\nInvalid Input!\n");
			break;
		}
	 }
}
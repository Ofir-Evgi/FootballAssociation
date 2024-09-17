#include "Statistics.h"

int initStatistics(Statistics* stat) {
	stat->numOfGoals = 0;
	stat->numOfRedCards = 0;
	stat->numOfYellowCards = 0;
	stat->physicality = 0;
	stat->dribbling = 0;
	stat->speed = 0;
	return 1;
}

void printStatistics(const Statistics* stat) {
	printf("\n\nStatistics:\n\nPhisicality: %d \tDribbling: %d\t Speed: %d", stat->physicality, stat->dribbling,stat->speed);
	printf("\n\nGoals: %d \tYellow Cards: %d \t Red Cards: %d\n\n\n", stat->numOfGoals, stat->numOfYellowCards, stat->numOfRedCards);
}

int	setStatistics(Statistics* stat) {
	int bool = 1;
	int physicality = 0, dribbling = 0, speed = 0;
	while (bool) {
		printf("Please enter player's statistics, between %d - %d: " , MIN_STAT, MAX_STAT);
		printf("\nPhysicality, Dribbling, Speed:\n");
		scanf("%d %d %d" , &physicality, &dribbling, &speed);
		if (physicality < MIN_STAT || physicality > MAX_STAT || dribbling < MIN_STAT || dribbling > MAX_STAT || speed < MIN_STAT || speed > MAX_STAT) {
			printf("\nInvalid STAT!\n");
		}
		else {
			bool = 0;
		}
	}
	stat->physicality = physicality;
	stat->dribbling = dribbling;
	stat->speed = speed;
	return 1;
}
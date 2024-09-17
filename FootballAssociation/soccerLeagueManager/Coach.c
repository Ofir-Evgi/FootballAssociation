#include "Coach.h"


int	initCoach(Coach* coach, char* teamName) {
	int age = 0;
	int expYears = 0;
	coach->name = getStrExactName("\nPlease enter the coach's name: ");
	CHECK_RETURN_INT(coach->name);
	deleteAllSpaces(coach->name);
	FirstCapitalLetter(coach->name);
	do
	{
		printf("\nPlease enter coach's age: ");
		scanf("%d", &age);
	} while (age < MIN_AGE || age > MAX_AGE);
	coach->age = age;

	do
	{
		printf("\nPlease enter coach experience years: ");
		scanf("%d", &expYears);
		if (expYears > (coach->age / 2)) {
			printf("\nERROR!\nExperience years cannot be over half of the coach's age!\n");
			expYears = -1;
		}
	} while ((expYears < MINIMUM || expYears > MAX_EXPERIENCE_YEARS));
	coach->experienceYears = expYears;
	coach->teamName = teamName;
	return 1;
}

void printCoach(const Coach* coach) {
	printf("\nThe coach info:\n\nName: %s\tExperinece Years: %d\tAge: %d\tTeam: %s\n",coach->name,coach->experienceYears,coach->age,coach->teamName);
}

void freeCoach(Coach* coach) {
	free(coach->name);
	free(coach->teamName);
}
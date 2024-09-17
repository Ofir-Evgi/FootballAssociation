#include "Referee.h"

int initReferee(Referee* ref) {
	int age = 0;
	int expYears = 0;
	ref->name = getStrExactName("\nPlease enter the referee's name: ");
	CHECK_RETURN_INT(ref->name);
	deleteAllSpaces(ref->name);
	FirstCapitalLetter(ref->name);
	do
	{
		printf("\nPlease enter referee's age: ");
		scanf("%d", &age);
	} while (age < MIN_AGE || age > MAX_AGE);
	ref->age = age;
	do
	{
		printf("\nPlease enter referee experience years: ");
		scanf("%d", &expYears);
		if (expYears > (ref->age / 2)) {
			printf("\nERROR!\nExperience years cannot be over half of the referee's age!\n");
			expYears = -1;
		}
	} while ( expYears < MINIMUM || expYears > MAX_EXPERIENCE_YEARS );
	ref->experienceYears = expYears;
	return 1;
}

void printReferee(const Referee* ref) {
	printf("\nReferee info:\n\nName: %s \tAge: %d \tExperience Years: %d\n", ref->name, ref->age, ref->experienceYears);
	PRINT_HORIZONTAL_LINE(70);
}

void generalPrintReferee(const void* r1) {
	const Referee* ref1 = *(const Referee**)r1;
	printReferee(ref1);
}

void freeReferee(Referee* ref) {
	free(ref->name);
	free(ref);
}

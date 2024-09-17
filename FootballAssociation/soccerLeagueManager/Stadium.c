#include "Stadium.h"

int initStadiumNoCode(Stadium* stad) {
	stad->name = getStrExactName("\nPlease enter the stadium name: ");
	CHECK_RETURN_INT(stad->name);
	deleteAllSpaces(stad->name);
	FirstCapitalLetter(stad->name);
	int capacity = 0;
	do
	{
		printf("\nPlease enter stadium capacity : ");
		scanf("%d", &capacity);
		if (capacity < MIN_STAD_CAPACITY || capacity > MAX_STAD_CAPACITY) {
			printf("\nInvalid Input!");
		}
	} while (capacity < MIN_STAD_CAPACITY || capacity > MAX_STAD_CAPACITY);
	stad->capacity = capacity;
	return 1;
}

void printStadium(const Stadium* stad) {
	printf("\nStadium info:\n\nName: %s\t Code: %s \tCapacity: %d\n", stad->name, stad->code, stad->capacity);
	PRINT_HORIZONTAL_LINE(70);
}

void generalPrintStadium(const void* s1) {
	const Stadium* stad1 = (const Stadium*)s1;
	printStadium(stad1);
}

int compareStadByCode(const void* s1, const void* s2) {
	const Stadium* stad1 = (const Stadium*)s1;
	const Stadium* stad2 = (const Stadium*)s2;
	return strcmp(stad1->code, stad2->code);
}

void freeStadium(Stadium* stad) {
	free(stad->name);
	free(stad);
}
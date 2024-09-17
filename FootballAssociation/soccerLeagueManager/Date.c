#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("\nEnter Date dd%cmm%cyyyy\t", SPECIAL_TAV, SPECIAL_TAV);
		myGets(date, MAX_STR_LEN);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}

int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10) {
		return 0;
	}
	if (date[2] != SPECIAL_TAV || date[5] != SPECIAL_TAV) {
		return 0;
	}
	sscanf(date, "%d%*c%d%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12) {
		return 0;
	}

	if (day > DAY_MONTHS[month - 1]) {
		return 0;
	}
	if (year < MIN_YEAR || year > MAX_YEAR) {
		return 0;
	}

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;
	return 1;
}

void	printDate(const Date* pDate)
{
	if (pDate->day < 10) {
		printf("Date: %d%d/", 0, pDate->day);
	}
	else {
		printf("Date: %d/", pDate->day);
	}
	if (pDate->month < 10) {
		printf("%d%d/%d", 0, pDate->month, pDate->year);
	}
	else {
		printf("%d/%d",pDate->month, pDate->year);
	}

}

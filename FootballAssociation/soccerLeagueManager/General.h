#ifndef __GENERAL__
#define __GENERAL__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Macros.h"
#include "List.h"

#define MIN_YEAR 2024
#define MAX_YEAR 2040
#define SPECIAL_TAV '/'
#define MAX_STR_LEN 255
#define MINIMUM 0
#define MAXIMUM 20
#define MAX_EXPERIENCE_YEARS 50
#define MIN_AGE 18
#define MAX_AGE 75
#define MAX_PLAYER_AGE 40
#define MIN_STAT 50
#define MAX_STAT 99
#define STAD_CODE 3
#define MIN_STAD_CAPACITY 5000
#define MAX_STAD_CAPACITY 99999
#define MIN_TEAM_PLAYERS 11 
#define MAX_TEAM_PLAYERS 20
#define MAX_EVENTS_IN_MATCH 7
#define MAX_MATCH_TIME 90
#define MAX_STAD_CODE 4
#define	MAX_CARDS 32
#define MIN_SHIRT_NUM 1



char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void	generalArrayFunction(const void* arr, int size, size_t sizeElement, void(*function)(void* v1));
int		generateRandomNumber(int min, int max);
void	deleteAllSpaces(char* inputName);
void	FirstCapitalLetter(char* inputName);



#endif



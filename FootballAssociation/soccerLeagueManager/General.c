
#include "General.h"



char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { 
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char** splitCharsToWords(char* str, int* pCount, int* pTotalLength)
{
	char temp[255];
	char* delimiters = " ";
	char* word;
	int count = 0;

	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}

void	generalArrayFunction(const void* arr, int size, size_t sizeElement, void(*function)(void* v1)) {
	char* pArr = (char*)arr;
	for (int i = 0; i < size; ++i)
	{
		function(pArr);
		pArr += sizeElement;
	}
}

int generateRandomNumber(int min, int max) {
	int number = (int)((rand() % (max - min + 1)) + min);
	return number;
}

void deleteAllSpaces(char* inputName)
{
	while (*inputName != '\0' && isspace(inputName[strlen(inputName) - 1]))
	{
		inputName[strlen(inputName) - 1] = '\0';
	}
}

void FirstCapitalLetter(char* inputName)
{
	if (inputName[0] >= 'a' && inputName[0] <= 'z') inputName[0] = toupper(inputName[0]);
	for (int i = 1; i < strlen(inputName); i++)
		if (inputName[i] >= 'a' && inputName[i] <= 'z' && inputName[i - 1] == ' ') inputName[i] = toupper(inputName[i]);
}



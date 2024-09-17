#include "LeaguesManager.h"


int initLeaguesManager(LeaguesManager* LM) {
	if (!L_init(&LM->leaguesArr)) {
		return 0;
	}
	return 1;
}
void leagueManagerMenu(LeaguesManager* LM) {
	int choice = 1;
	League* chooseLeague = (League*)malloc(sizeof(League*));
	while (choice != -1) {
		printf("\nPlease select which way do you want to create a leagues manager: \n 1 - To print leagues manager \n 2 - To add league\n 3 - To delete league\n 4 - To choose league and open the league menu\n-1 - To close this menu\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1: {
			printLeaguesList(LM);
			break;
		}
		case 2: {
			if (!addLeague(LM)) {
				printf("ERROR!\nAdding the league dosent succeed, please try again\n");
			}
			break;
		}
		case 3: {
			if (!LM->leaguesArr.head.next) {
				printf("ERROR!\nThere's no leagues in the list\n");
			}
			else {
				if (!deleteLeague(LM)) {
					printf("ERROR!\nDeleting the league dosent succeed, please try again\n");
				}
			}
			break;
		}
		case 4: {
			L_print(&LM->leaguesArr, printLeagueFromListName);
			do {
			char* name = getStrExactName("Please enter the name of the league that you want to choose: \t");
			deleteAllSpaces(name);
			FirstCapitalLetter(name);
			League* demoL = (League*)malloc(sizeof(League));
			if (!demoL) {
				break;
			}
			demoL->name = name;
			chooseLeague = chooseLeagueFromListByName(&LM->leaguesArr,demoL, compareLeaguesByName);
			if (!chooseLeague) {
				printf("There is no league with this name, try again!\n");
			}
			else {
				break;
			}
			} while (1);
			leagueMenu(chooseLeague);
			break;
		}
		case -1: {
			break;
		}

		default:
			printf("Invalid Input!\n");
			break;
		}



	}
}

League* chooseLeagueFromListByName(LIST* leaguesArr, League* demoL, int(*compare)(const void*, const void*)){
	League* tempLeague;
	NODE* temp = L_find(&leaguesArr->head, demoL, compare);
	if (temp->next) {
		tempLeague = (League*)temp->next->key;
	}
	else {
		tempLeague = (League*)temp->key;
	}
	if (strcmp(tempLeague->name, demoL->name) == 0 ) {
		return tempLeague;
	}
	return NULL;
}

void printLeaguesList(const LeaguesManager* LM) {
	L_print(&LM->leaguesArr, printLeagueFromList);
}



int addLeague(LeaguesManager* LM) {
	League* pLeague = (League*)calloc(1, sizeof(League));
	CHECK_RETURN_INT(pLeague);

	if (!initLeague(pLeague))
	{
		freeLeague(pLeague);
		free(pLeague);
		return 0;
	}
	NODE* pNode = L_find(&LM->leaguesArr.head, pLeague, compareLeaguesByName);
	NODE* pNodeD = (NODE*)malloc(sizeof(NODE));
	CHECK_RETURN_INT(pNodeD);
	pNodeD->key = pLeague;
	pNodeD->next = pNode->next;
	pNode->next = pNodeD;
	return 1;
}

int deleteLeague(LeaguesManager* LM) {
	League* temp = (League*)malloc(sizeof(League));
	CHECK_RETURN_INT(temp);
	printf("\nTo delete the league\n");
	initLeague(temp);
	NODE* leagueToDelete = L_find(&LM->leaguesArr.head, temp, compareLeaguesByName);
	freeLeague(temp);
	if (!L_delete(leagueToDelete, freeLeagueFromList)) {
		return 0;
	}
	return 1;
}


int	compareLeaguesByName(const void* l1, const void* l2) {
	const League* lea1 = (const League*)l1;
	const League* lea2 = (const League*)l2;
	return strcmp(lea1->name, lea2->name);
}



void freeLeaguesManager(LeaguesManager* LM) {
	L_free(&LM->leaguesArr, freeLeagueFromList);
}

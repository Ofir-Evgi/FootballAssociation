#include "GeneralTextFiles.h"


int	readLeaguesManagerFromTextFile(LeaguesManager* LM, FILE* tf) {
	int numOfLeagues = 0;
	if (fscanf(tf, "%d\n", &numOfLeagues) != 1) {
		return 0;
	}
	if (!L_init(&LM->leaguesArr)) {
		return 0;
	}
	for (int i = 0; i < numOfLeagues; i++)
	{
		League* league = (League*)malloc(sizeof(League));
		if (!league) {
			freeLeaguesManager(LM);
			return 0;
		}
		if (!readLeagueFromTextFile(league, tf)) {
			return 0;
		}

		NODE* newNode = L_find(&LM->leaguesArr.head, league, compareLeaguesByName);
		L_insert(newNode, league);
	}
	return 1;
}
int writeLeaguesManagerToTextFile(const LeaguesManager* LM, FILE* tf) {
	int count = countNodesInList(&LM->leaguesArr);
	if (fprintf(tf, "%d\n", count) < 1) {
		return 0;
	}
	NODE* temp = LM->leaguesArr.head.next;
	for (int i = 0; i < count; i++)
	{
		League* lea = (League*)temp->key;
		if (!writeLeagueToTextFile(lea, tf)) {
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}

int	readLeagueFromTextFile(League* league, FILE* tf) {
	char tempName[MAX_STR_LEN] = { 0 };
	char tempCountry[MAX_STR_LEN] = { 0 };
	if (fscanf(tf, "%[^\n]\n%[^\n]\n%d\n", tempName, tempCountry, &league->numOfTeams) != 3) {
		return 0;
	}
	league->name = strdup(tempName);
	league->country = strdup(tempCountry);
	if (!readTeamsArr(league, tf)) {
		return 0;
	}

	if (fscanf(tf, "%d\n", &league->numOfMatches) != 1) {
		return 0;
	}
	if (!readMatchesArr(league, tf)) {
		return 0;
	}
	if (fscanf(tf, "%d\n", &league->numOfReferees) != 1) {
		return 0;
	}

	if (!readRefereesArr(league, tf)) {
		return 0;
	}

	if (fscanf(tf, "%d\n", &league->numOfStadium) != 1) {
		return 0;
	}

	if (!readStadiumArr(league, tf)) {
		return 0;
	}

	return 1;

}
int	writeLeagueToTextFile(const League* league, FILE* tf) {
	if (fprintf(tf, "%s\n%s\n%d\n", league->name, league->country, league->numOfTeams) < 0) {
		return 0;
	}
	if (!writeTeamsArr(league, tf)) {
		return 0;
	}
	if (fprintf(tf, "%d\n", league->numOfMatches) < 0) {
		return 0;
	}
	if (!writeMatchesArr(league, tf)) {
		return 0;
	}
	if (fprintf(tf, "%d\n", league->numOfReferees) < 0) {
		return 0;
	}
	if (!writeRefereesArr(league, tf)) {
		return 0;
	}
	if (fprintf(tf, "%d\n", league->numOfStadium) < 0) {
		return 0;
	}
	if (!writeStadiumArr(league, tf)) {
		return 0;
	}

	return 1;
}

int readTeamsArr(League* league, FILE* tf) {
	league->teamsArr = (Team**)malloc(league->numOfTeams * sizeof(Team*));
	CHECK_RETURN_INT(league->teamsArr);
	for (int i = 0; i < league->numOfTeams; i++)
	{
		Team* team = (Team*)malloc(sizeof(Team));
		CHECK_RETURN_INT(league->teamsArr[i]);
		if (!readTeamFromTextFile(team, tf)) {
			return 0;
		}
		league->teamsArr[i] = team;
	}
	return 1;
}
int readMatchesArr(League* league, FILE* tf) {
	league->matchesArr = (Match**)malloc(league->numOfMatches * sizeof(Match*));
	CHECK_RETURN_INT(league->matchesArr);
	for (int i = 0; i < league->numOfMatches; i++)
	{
		Match* match = (Match*)malloc(sizeof(Match));
		CHECK_RETURN_INT(match);
		if (!readMatchFromTextFile(match, tf)) {
			return 0;
		}
		league->matchesArr[i] = match;
	}
	return 1;

}
int readRefereesArr(League* league, FILE* tf) {
	league->refereesArr = (Referee**)malloc(league->numOfReferees * sizeof(Referee*));
	CHECK_RETURN_INT(league->refereesArr);
	for (int i = 0; i < league->numOfReferees; i++)
	{
		Referee* referee = (Referee*)malloc(sizeof(Referee));
		CHECK_RETURN_INT(referee);
		if (!readRefereeFromTextFile(referee, tf)) {
			return 0;
		}
		league->refereesArr[i] = referee;
	}
	return 1;

}
int readStadiumArr(League* league, FILE* tf) {
	league->stadiumsArr = (Stadium*)malloc(league->numOfStadium * sizeof(Stadium));
	CHECK_RETURN_INT(league->stadiumsArr);
	for (int i = 0; i < league->numOfStadium; i++)
	{
		Stadium stadium = *(Stadium*)malloc(sizeof(Stadium));
		CHECK_RETURN_INT(&stadium);
		if (!readStadiumFromTextFile(&stadium, tf)) {
			return 0;
		}
		league->stadiumsArr[i] = stadium;
	}
	return 1;
}

int writeTeamsArr(const League* league, FILE* tf) {
	for (int i = 0; i < league->numOfTeams; i++)
	{
		if (!writeTeamToTextFile(league->teamsArr[i], tf)) {
			return 0;
		}
	}
	return 1;
}
int writeMatchesArr(const League* league, FILE* tf) {
	for (int i = 0; i < league->numOfMatches; i++)
	{
		if (!writeMatchToTextFile(league->matchesArr[i], tf)) {
			return 0;
		}
	}
	return 1;
}
int writeRefereesArr(const League* league, FILE* tf) {
	for (int i = 0; i < league->numOfReferees; i++)
	{
		if (!writeRefereeToTextFile(league->refereesArr[i], tf)) {
			return 0;
		}
	}
	return 1;
}
int writeStadiumArr(const League* league, FILE* tf) {
	for (int i = 0; i < league->numOfStadium; i++)
	{
		if (!writeStadiumToTextFile(&league->stadiumsArr[i], tf)) {
			return 0;
		}
	}
	return 1;
}

int	readMatchFromTextFile(Match* match, FILE* tf) {
	match->teamA = (Team*)malloc(sizeof(Team));
	CHECK_RETURN_INT(match->teamA);
	match->teamB = (Team*)malloc(sizeof(Team));
	CHECK_RETURN_INT(match->teamB);
	match->matchStadium = *(Stadium*)malloc(sizeof(Stadium));
	CHECK_RETURN_INT(&match->matchStadium);
	match->matchRef = *(Referee*)malloc(sizeof(Referee));
	CHECK_RETURN_INT(&match->matchRef);
	match->matchDate = *(Date*)malloc(sizeof(Date));
	CHECK_RETURN_INT(&match->matchDate);
	match->matchEvents = (MatchEvents*)malloc(sizeof(MatchEvents));
	CHECK_RETURN_INT(&match->matchEvents);

	if (!readTeamFromTextFile(match->teamA, tf)) {
		return 0;
	}

	if (!readTeamFromTextFile(match->teamB, tf)) {
		return 0;
	}
	if (!readStadiumFromTextFile(&match->matchStadium, tf)) {
		return 0;
	}

	if (!readRefereeFromTextFile(&match->matchRef, tf)) {
		return 0;
	}
	if (!readDateFromTextFile(&match->matchDate, tf)) {
		return 0;
	}
	if (!readMatchEventsFromTextFile(match->matchEvents, tf)) {
		return 0;
	}
	if (fscanf(tf, "%d\n%d\n", &match->scoreTeamA, &match->scoreTeamB) != 2) {
		return 0;
	}
	return 1;


}
int	writeMatchToTextFile(const Match* match, FILE* tf) {
	if (!writeTeamToTextFile(match->teamA, tf)) {
		return 0;
	}
	if (!writeTeamToTextFile(match->teamB, tf)) {
		return 0;
	}
	if (!writeStadiumToTextFile(&match->matchStadium, tf)) {
		return 0;
	}
	if (!writeRefereeToTextFile(&match->matchRef, tf)) {
		return 0;
	}
	if (!writeDateToTextFile(&match->matchDate, tf)) {
		return 0;
	}
	if (!writeMatchEventsToTextFile(match->matchEvents, tf)) {
		return 0;
	}
	if (fprintf(tf, "%d\n%d\n", match->scoreTeamA, match->scoreTeamB) < 1) {
		return 0;
	}
	return 1;
}

int	writeCoachToTextFile(const Coach* coach, FILE* tf) {
	if (fprintf(tf, "%s\n%d\n%d\n%s\n", coach->name, coach->age, coach->experienceYears, coach->teamName) < 0) {
		return 0;
	}
	return 1;
}
int	readCoachFromTextFile(Coach* coach, FILE* tf) {
	char tempName[MAX_STR_LEN] = { 0 };
	char tempTeam[MAX_STR_LEN] = { 0 };
	if (fscanf(tf, "%[^\n]\n%d\n%d\n%[^\n]\n", tempName, &coach->age, &coach->experienceYears, tempTeam) != 4) {
		return 0;
	}
	coach->name = strdup(tempName);
	coach->teamName = strdup(tempTeam);
	return 1;
}

int	readDateFromTextFile(Date* date, FILE* tf) {
	if (fscanf(tf, "%d\n%d\n%d\n", &date->day, &date->month, &date->year) != 3) {
		return 0;
	}
	return 1;
}
int	writeDateToTextFile(const Date* date, FILE* tf) {
	if (fprintf(tf, "%d\n%d\n%d\n", date->day, date->month, date->year) < 1) {
		return 0;
	}
	return 1;
}

int	readMatchEventsFromTextFile(MatchEvents* matchE, FILE* tf) {
	initMatchEvents(matchE);
	if (fscanf(tf, "%d\n", &matchE->numOfEvents) != 1) {
		return 0;
	}

	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fscanf(tf, "%d\n", &matchE->minutesArr[i]) != 1) {
			return 0;
		}
	}
	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fscanf(tf, "%d\n", &matchE->eventsArr[i]) != 1) {
			return 0;
		}
	}
	for (int i = 0; i < matchE->numOfEvents; i++)
	{
		matchE->playerArr[i] = (Player*)malloc(sizeof(Player));
		CHECK_RETURN_INT(matchE->playerArr[i]);
		if (!readPlayerFromTextFile(matchE->playerArr[i], tf)) {
			return 0;
		}
	}
	if (fscanf(tf, "%d\n", &matchE->numOfRedPlayers) != 1) {
		return 0;
	}
	if (matchE->numOfRedPlayers == 0) {
		matchE->redPlayersArr = (Player**)malloc(sizeof(Player*));
		CHECK_RETURN_INT(matchE->redPlayersArr);
	}
	else {
		matchE->redPlayersArr = (Player**)malloc(matchE->numOfRedPlayers * sizeof(Player*));
		CHECK_RETURN_INT(matchE->redPlayersArr);
	}
	for (int i = 0; i < matchE->numOfRedPlayers; i++)
	{
		matchE->redPlayersArr[i] = (Player*)malloc(sizeof(Player));
		CHECK_RETURN_INT(matchE->redPlayersArr[i]);
		if (!readPlayerFromTextFile(matchE->redPlayersArr[i], tf)) {
			return 0;
		}
	}
	return 1;
}
int	writeMatchEventsToTextFile(const MatchEvents* matchE, FILE* tf) {
	if (fprintf(tf, "%d\n", matchE->numOfEvents) < 1) {
		return 0;
	}

	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fprintf(tf, "%d\n", matchE->minutesArr[i]) < 1) {
			return 0;
		}
	}
	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fprintf(tf, "%d\n", matchE->eventsArr[i]) < 1) {
			return 0;
		}
	}
	for (int i = 0; i < matchE->numOfEvents; i++)
	{
		if (!writePlayerToTextFile(matchE->playerArr[i], tf)) {
			return 0;
		}
	}
	if (fprintf(tf, "%d\n", matchE->numOfRedPlayers) < 1) {
		return 0;
	}

	for (int i = 0; i < matchE->numOfRedPlayers; i++)
	{
		if (!writePlayerToTextFile(matchE->redPlayersArr[i], tf)) {
			return 0;
		}
	}
	return 1;
}

int	readPlayerFromTextFile(Player* player, FILE* tf) {
	char temp[MAX_STR_LEN] = { 0 };
	if (fscanf(tf, "%[^\n]\n%d\n%d\n%d\n", temp, &player->age, &player->shirtNumber, &player->Position) != 4) {
		return 0;
	}
	player->name = strdup(temp);
	CHECK_RETURN_INT(player->name);
	player->playerStatistics = *(Statistics*)malloc(sizeof(Statistics));
	CHECK_RETURN_INT(&player->playerStatistics);
	if (!readStatisticsFromTextFile(&player->playerStatistics, tf)) {
		return 0;
	}
	return 1;
}
int	writePlayerToTextFile(const Player* player, FILE* tf) {
	if (fprintf(tf, "%s\n%d\n%d\n%d\n", player->name, player->age, player->shirtNumber, player->Position) < 0) {
		return 0;
	}
	if (!writeStatisticsToTextFile(&player->playerStatistics, tf)) {
		return 0;
	}
	return 1;
}

int	readRefereeFromTextFile(Referee* ref, FILE* tf) {
	char temp[MAX_STR_LEN] = { 0 };
	if (fscanf(tf, "%[^\n]\n%d\n%d\n", temp, &ref->age, &ref->experienceYears) != 3) {
		return 0;
	}
	ref->name = strdup(temp);
	CHECK_RETURN_INT(ref->name);
	return 1;
}
int	writeRefereeToTextFile(const Referee* ref, FILE* tf) {
	if (fprintf(tf, "%s\n%d\n%d\n", ref->name, ref->age, ref->experienceYears) < 0) {
		return 0;
	}
	return 1;
}

int	readStadiumFromTextFile(Stadium* stad, FILE* tf) {
	char temp[MAX_STR_LEN] = { 0 };
	if (fscanf(tf, "%[^\n]\n%s\n%d\n", temp, stad->code, &stad->capacity) != 3) {
		return 0;
	}
	stad->name = strdup(temp);
	CHECK_RETURN_INT(stad->name);
	return 1;
}
int	writeStadiumToTextFile(const Stadium* stad, FILE* tf) {
	if (fprintf(tf, "%s\n%s\n%d\n", stad->name, stad->code, stad->capacity) < 0) {
		return 0;
	}
	return 1;
}


int	readStatisticsFromTextFile(Statistics* stat, FILE* tf) {
	if (fscanf(tf, "%d\n%d\n%d\n%d\n%d\n%d\n", &stat->numOfGoals, &stat->numOfRedCards, &stat->numOfYellowCards, &stat->dribbling, &stat->physicality, &stat->speed) != 6) {
		return 0;
	}
	return 1;
}
int writeStatisticsToTextFile(const Statistics* stat, FILE* tf) {
	if (fprintf(tf, "%d\n%d\n%d\n%d\n%d\n%d\n", stat->numOfGoals, stat->numOfRedCards, stat->numOfYellowCards, stat->dribbling, stat->physicality, stat->speed) < 0) {
		return 0;
	}
	return 1;
}

int	readTeamFromTextFile(Team* team, FILE* tf) {
	char temp[MAX_STR_LEN] = { 0 };
	if (fscanf(tf, "%[^\n]\n%d\n%d\n%d\n%d\n", temp, &team->points, &team->numOfPlayers, &team->sortType, &team->formationType) != 5) {
		return 0;
	}
	team->name = strdup(temp);
	CHECK_RETURN_INT(team->name);

	team->playerArr = (Player**)malloc(team->numOfPlayers * sizeof(Player*));
	CHECK_RETURN_INT(team->playerArr);
	for (int i = 0; i < team->numOfPlayers; i++)
	{
		team->playerArr[i] = (Player*)malloc(sizeof(Player));
		CHECK_RETURN_INT(team->playerArr[i]);
		if (!readPlayerFromTextFile(team->playerArr[i], tf)) {
			return 0;
		}
	}
	team->coach = (Coach*)malloc(sizeof(Coach));
	CHECK_RETURN_INT(team->coach);
	if (!readCoachFromTextFile(team->coach, tf)) {
		return 0;
	}
	return 1;
}
int	writeTeamToTextFile(const Team* team, FILE* tf) {
	if (fprintf(tf, "%s\n%d\n%d\n%d\n%d\n", team->name, team->points, team->numOfPlayers, team->sortType,team->formationType) < 0) {
		return 0;
	}
	for (int i = 0; i < team->numOfPlayers; i++)
	{
		if (!writePlayerToTextFile(team->playerArr[i], tf)) {
			return 0;
		}
	}
	if (!writeCoachToTextFile(team->coach, tf)) {
		return 0;
	}
	return 1;
}



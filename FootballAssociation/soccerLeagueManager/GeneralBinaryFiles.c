#include "GeneralBinaryFiles.h"

int	readLeaguesManagerFromBinaryFile(LeaguesManager* LM, FILE* bf) {
	int numOfLeagues;
	if (fread(&numOfLeagues, sizeof(int), 1, bf) != 1) {
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
		if (!readLeagueFromBinaryFile(league, bf)) {
			return 0;
		}

		NODE* newNode = L_find(&LM->leaguesArr.head, league, compareLeaguesByName);
		L_insert(newNode, league);
	}
	return 1;
}
int writeLeaguesManagerToBinaryFile(const LeaguesManager* LM, FILE* bf) {
	int numOfLeagues = countNodesInList(&LM->leaguesArr);
	if (fwrite(&numOfLeagues, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	NODE* temp = LM->leaguesArr.head.next;
	for (int i = 0; i < numOfLeagues; i++)
	{
		League* lea = (League*)temp->key;
		if (!writeLeagueToBinaryFile(lea, bf)) {
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}

int	writeLeagueToBinaryFile(const League* league, FILE* bf) {
	int nameLen = (int)strlen(league->name) + 1;
	int countryLen = (int)strlen(league->country) + 1;
	if (fwrite(&nameLen, sizeof(int), 1, bf) != 1)
		return 0;


	if (fwrite(league->name, sizeof(char), nameLen, bf) != nameLen)
		return 0;


	if (fwrite(&countryLen, sizeof(int), 1, bf) != 1)
		return 0;


	if (fwrite(league->country, sizeof(char), countryLen, bf) != countryLen)
		return 0;


	if (fwrite(&league->numOfTeams, sizeof(int), 1, bf) != 1)
		return 0;


	if (!writeTeamsArrBin(league, bf))
		return 0;


	if (fwrite(&league->numOfMatches, sizeof(int), 1, bf) != 1)
		return 0;


	if (!writeMatchesArrBin(league, bf))
		return 0;


	if (fwrite(&league->numOfReferees, sizeof(int), 1, bf) != 1)
		return 0;


	if (!writeRefereesArrBin(league, bf))
		return 0;


	if (fwrite(&league->numOfStadium, sizeof(int), 1, bf) != 1)
		return 0;


	if (!writeStadiumArrBin(league, bf))
		return 0;


	return 1;
}
int	readLeagueFromBinaryFile(League* league, FILE* bf) {
	int nameLen;
	int countryLen;
	if (fread(&nameLen, sizeof(int), 1, bf) != 1)
		return 0;

	league->name = (char*)malloc(nameLen * sizeof(char));
	CHECK_RETURN_INT(league->name);


	if (fread(league->name, sizeof(char), nameLen, bf) != nameLen)
		return 0;


	if (fread(&countryLen, sizeof(int), 1, bf) != 1)
		return 0;


	league->country = (char*)malloc(countryLen * sizeof(char));
	CHECK_RETURN_INT(league->country);

	if (fread(league->country, sizeof(char), countryLen, bf) != countryLen)
		return 0;


	if (fread(&league->numOfTeams, sizeof(int), 1, bf) != 1)
		return 0;


	if (!readTeamsArrBin(league, bf))
		return 0;


	if (fread(&league->numOfMatches, sizeof(int), 1, bf) != 1)
		return 0;


	if (!readMatchesArrBin(league, bf))
		return 0;


	if (fread(&league->numOfReferees, sizeof(int), 1, bf) != 1)
		return 0;


	if (!readRefereesArrBin(league, bf))
		return 0;


	if (fread(&league->numOfStadium, sizeof(int), 1, bf) != 1)
		return 0;


	if (!readStadiumArrBin(league, bf))
		return 0;


	return 1;
}

int readTeamsArrBin(League* league, FILE* bf) {
	league->teamsArr = (Team**)malloc(league->numOfTeams * sizeof(Team*));
	CHECK_RETURN_INT(league->teamsArr);
	for (int i = 0; i < league->numOfTeams; i++)
	{
		league->teamsArr[i] = (Team*)malloc(sizeof(Team));
		CHECK_RETURN_INT(league->teamsArr[i]);
		if (!readTeamFromBinaryFile(league->teamsArr[i], bf))
			return 0;
	}
	return 1;
}
int readMatchesArrBin(League* league, FILE* bf) {
	league->matchesArr = (Match**)malloc(league->numOfMatches * sizeof(Match*));
	CHECK_RETURN_INT(league->matchesArr);
	for (int i = 0; i < league->numOfMatches; i++)
	{
		league->matchesArr[i] = (Match*)malloc(sizeof(Match));
		CHECK_RETURN_INT(league->matchesArr[i]);
		if (!readMatchFromBinaryFile(league->matchesArr[i], bf))
			return 0;
	}
	return 1;
}
int readRefereesArrBin(League* league, FILE* bf) {
	league->refereesArr = (Referee**)malloc(league->numOfReferees * sizeof(Referee*));
	CHECK_RETURN_INT(league->refereesArr);
	for (int i = 0; i < league->numOfReferees; i++)
	{
		league->refereesArr[i] = (Referee*)malloc(sizeof(Referee));
		CHECK_RETURN_INT(league->refereesArr[i]);
		if (!readRefereeFromBinaryFile(league->refereesArr[i], bf))
			return 0;
	}
	return 1;
}
int readStadiumArrBin(League* league, FILE* bf) {
	league->stadiumsArr = (Stadium*)malloc(league->numOfStadium * sizeof(Stadium));
	CHECK_RETURN_INT(league->stadiumsArr);
	for (int i = 0; i < league->numOfStadium; i++)
	{
		league->stadiumsArr[i] = *(Stadium*)malloc(sizeof(Stadium));
		CHECK_RETURN_INT(&league->stadiumsArr[i]);
		if (!readStadiumFromBinaryFile(&league->stadiumsArr[i], bf))
			return 0;
	}
	return 1;
}

int writeTeamsArrBin(const League* league, FILE* bf) {
	for (int i = 0; i < league->numOfTeams; i++)
	{
		if (!writeTeamToBinaryFile(league->teamsArr[i], bf))
			return 0;
	}
	return 1;
}
int writeMatchesArrBin(const League* league, FILE* bf) {
	for (int i = 0; i < league->numOfMatches; i++)
	{
		if (!writeMatchToBinaryFile(league->matchesArr[i], bf))
			return 0;
	}
	return 1;
}
int writeRefereesArrBin(const League* league, FILE* bf) {
	for (int i = 0; i < league->numOfReferees; i++)
	{
		if (!writeRefereeToBinaryFile(league->refereesArr[i], bf))
			return 0;
	}
	return 1;
}
int writeStadiumArrBin(const League* league, FILE* bf) {
	for (int i = 0; i < league->numOfStadium; i++)
	{
		if (!writeStadiumToBinaryFile(&league->stadiumsArr[i], bf))
			return 0;
	}
	return 1;
}

int	readMatchFromBinaryFile(Match* match, FILE* bf) {
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

	if (!readTeamFromBinaryFile(match->teamA, bf)) {
		return 0;
	}
	if (!readTeamFromBinaryFile(match->teamB, bf)) {
		return 0;
	}
	if (!readStadiumFromBinaryFile(&match->matchStadium, bf)) {
		return 0;
	}
	if (!readRefereeFromBinaryFile(&match->matchRef, bf)) {
		return 0;
	}
	if (!readDateFromBinaryFile(&match->matchDate, bf)) {
		return 0;
	}
	if (!readMatchEventsFromBinaryFile(match->matchEvents, bf)) {
		return 0;
	}
	if (fread(&match->scoreTeamA, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fread(&match->scoreTeamB, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	return 1;
}
int	writeMatchToBinaryFile(const Match* match, FILE* bf) {
	if (!writeTeamToBinaryFile(match->teamA, bf)) {
		return 0;
	}
	if (!writeTeamToBinaryFile(match->teamB, bf)) {
		return 0;
	}
	if (!writeStadiumToBinaryFile(&match->matchStadium, bf)) {
		return 0;
	}
	if (!writeRefereeToBinaryFile(&match->matchRef, bf)) {
		return 0;
	}
	if (!writeDateToBinaryFile(&match->matchDate, bf)) {
		return 0;
	}
	if (!writeMatchEventsToBinaryFile(match->matchEvents, bf)) {
		return 0;
	}
	if (fwrite(&match->scoreTeamA, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&match->scoreTeamB, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	return 1;
}

int	writeCoachToBinaryFile(const Coach* coach, FILE* bf) {
	int nameLen =(int) strlen(coach->name) + 1;
	int teamLen =(int) strlen(coach->teamName) + 1;
	if (fwrite(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(coach->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}

	if (fwrite(&coach->age, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&coach->experienceYears, sizeof(int), 1, bf) != 1) {
		return 0;
	}

	if (fwrite(&teamLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(coach->teamName, sizeof(char), teamLen, bf) != teamLen) {
		return 0;
	}

	return 1;
}
int	readCoachFromBinaryFile(Coach* coach, FILE* bf) {
	int nameLen;
	int teamLen;
	if (fread(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}

	coach->name = (char*)malloc(nameLen * sizeof(char));
	CHECK_RETURN_INT(coach->name);

	if (fread(coach->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}

	if (fread(&coach->age, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fread(&coach->experienceYears, sizeof(int), 1, bf) != 1) {
		return 0;
	}

	if (fread(&teamLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}

	coach->teamName = (char*)malloc(teamLen * sizeof(char));
	CHECK_RETURN_INT(coach->teamName);

	if (fread(coach->teamName, sizeof(char), teamLen, bf) != teamLen) {
		return 0;
	}
	return 1;
}

int		readDateFromBinaryFile(Date* date, FILE* bf) {
	int day = 0, month = 0, year = 0;
	if (fread(&day, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	date->day = day;

	if (fread(&month, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	date->month = month;

	if (fread(&year, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	date->year = year;
	return 1;
}
int		writeDateToBinaryFile(const Date* date, FILE* bf) {
	if (fwrite(&date->day, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&date->month, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&date->year, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	return 1;
}

int	readMatchEventsFromBinaryFile(MatchEvents* matchE, FILE* bf) {
	if (fread(&matchE->numOfEvents, sizeof(int), 1, bf) != 1) {
		return 0;
	}

	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fread(&matchE->minutesArr[i], sizeof(int), 1, bf) != 1) {
			return 0;
		}
	}
	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fread(&matchE->eventsArr[i], sizeof(int), 1, bf) != 1) {
			return 0;
		}
	}
	for (int i = 0; i < matchE->numOfEvents; i++)
	{
		matchE->playerArr[i] = (Player*)malloc(sizeof(Player));
		CHECK_RETURN_INT(matchE->playerArr[i]);
		if (!readPlayerFromBinaryFile(matchE->playerArr[i], bf)) {
			return 0;
		}
	}
	if (fread(&matchE->numOfRedPlayers, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	matchE->redPlayersArr = (Player**)malloc(sizeof(Player));
	CHECK_RETURN_INT(matchE->redPlayersArr);
	for (int i = 0; i < matchE->numOfRedPlayers; i++)
	{
		matchE->redPlayersArr[i] = (Player*)malloc(sizeof(Player));
		CHECK_RETURN_INT(matchE->redPlayersArr[i]);
		if (!readPlayerFromBinaryFile(matchE->redPlayersArr[i], bf)) {
			return 0;
		}
	}
	return 1;
}
int	writeMatchEventsToBinaryFile(const MatchEvents* matchE, FILE* bf) {
	if (fwrite(&matchE->numOfEvents, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fwrite(&matchE->minutesArr[i], sizeof(int), 1, bf) != 1) {
			return 0;
		}
	}
	for (int i = 0; i < MAX_EVENTS_IN_MATCH; i++)
	{
		if (fwrite(&matchE->eventsArr[i], sizeof(int), 1, bf) != 1) {
			return 0;
		}
	}
	for (int i = 0; i < matchE->numOfEvents; i++)
	{
		if (!writePlayerToBinaryFile(matchE->playerArr[i], bf)) {
			return 0;
		}
	}
	if (fwrite(&matchE->numOfRedPlayers, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	for (int i = 0; i < matchE->numOfRedPlayers; i++)
	{
		if (!writePlayerToBinaryFile(matchE->redPlayersArr[i], bf)) {
			return 0;
		}
	}
	return 1;
}

int	readPlayerFromBinaryFile(Player* player, FILE* bf) {
	int nameLen;
	if (fread(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	player->name = (char*)malloc(nameLen * sizeof(char));
	CHECK_RETURN_INT(player->name);
	if (fread(player->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}
	if (fread(&player->age, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fread(&player->shirtNumber, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fread(&player->Position, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	player->playerStatistics = *(Statistics*)malloc(sizeof(Statistics));
	CHECK_RETURN_INT(&player->playerStatistics);
	if (!readStatisticsFromCompressedBinaryFile(&player->playerStatistics, bf)) {
		return 0;
	}
	return 1;
}
int	writePlayerToBinaryFile(const Player* player, FILE* bf) {
	int nameLen = (int)strlen(player->name) + 1;
	if (fwrite(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(player->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}
	if (fwrite(&player->age, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&player->shirtNumber, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&player->Position, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (!writeStatisticsToCompressedBinaryFile(&player->playerStatistics, bf)) {
		return 0;
	}
	return 1;
}

int	readRefereeFromBinaryFile(Referee* ref, FILE* bf) {
	int nameLen;
	if (fread(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	ref->name = (char*)malloc(nameLen * sizeof(char));
	CHECK_RETURN_INT(ref->name);
	if (fread(ref->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}
	if (fread(&ref->age, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fread(&ref->experienceYears, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	return 1;



}
int	writeRefereeToBinaryFile(const Referee* ref, FILE* bf) {
	int nameLen = (int)strlen(ref->name) + 1;
	if (fwrite(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(ref->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}
	if (fwrite(&ref->age, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&ref->experienceYears, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	return 1;
}

int	readStadiumFromBinaryFile(Stadium* stad, FILE* bf) {
	int nameLen;
	if (fread(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	stad->name = (char*)malloc(nameLen * sizeof(char));
	CHECK_RETURN_INT(stad->name);
	if (fread(stad->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}
	if (fread(stad->code, sizeof(char), MAX_STAD_CODE, bf) != MAX_STAD_CODE) {
		return 0;
	}
	if (fread(&stad->capacity, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	return 1;
}
int	writeStadiumToBinaryFile(const Stadium* stad, FILE* bf) {
	int nameLen = (int)strlen(stad->name) + 1;
	if (fwrite(&nameLen, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(stad->name, sizeof(char), nameLen, bf) != nameLen) {
		return 0;
	}
	if (fwrite(stad->code, sizeof(char), MAX_STAD_CODE, bf) != MAX_STAD_CODE) {
		return 0;
	}
	if (fwrite(&stad->capacity, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	return 1;
}

int	readStatisticsFromCompressedBinaryFile(Statistics* stat, FILE* bf) {
	BYTE data[5];
	if (fread(data, sizeof(BYTE), 5, bf) != 5)
	{
		return 0;
	}
	stat->numOfYellowCards = data[0] >> 3;
	stat->numOfRedCards = ((data[0] << 2) | (data[1] >> 6)) & 0x1F;
	stat->numOfGoals = ((data[1] << 1) | (data[2] >> 7)) & 0x7F;
	stat->speed = data[2] & 0x7F;
	stat->dribbling = (data[3] >> 1) & 0x7F;
	stat->physicality = ((data[3] << 6) | (data[4] >> 2)) & 0x7F;
	return 1;
}
int writeStatisticsToCompressedBinaryFile(const Statistics* stat, FILE* bf) {
	BYTE data[5] = { 0 };
	data[0] = (stat->numOfYellowCards << 3) | (stat->numOfRedCards >> 2);
	data[1] = (stat->numOfRedCards << 6) | (stat->numOfGoals >> 1);
	data[2] = (stat->numOfGoals << 7) | (stat->speed);
	data[3] = (stat->dribbling << 1) | (stat->physicality >> 6);
	data[4] = (stat->physicality << 2);

	if (fwrite(data, sizeof(BYTE), 5, bf) != 5) {
		return 0;
	}
	return 1;
}

int	readTeamFromBinaryFile(Team* team, FILE* bf) {
	int len;
	if (fread(&len, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	team->name = (char*)malloc(len * sizeof(char));
	CHECK_RETURN_INT(team->name);

	if (fread(team->name, sizeof(char), len, bf) != len) {
		return 0;
	}
	if (fread(&team->points, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fread(&team->numOfPlayers, sizeof(int), 1, bf) != 1) {
		return 0;
	}	
	if (fread(&team->sortType, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fread(&team->formationType, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	team->playerArr = (Player**)malloc(team->numOfPlayers * sizeof(Player*));
	CHECK_RETURN_INT(team->playerArr);
	for (int i = 0; i < team->numOfPlayers; i++)
	{
		team->playerArr[i] = (Player*)malloc(sizeof(Player));
		CHECK_RETURN_INT(team->playerArr[i]);
		if (!readPlayerFromBinaryFile(team->playerArr[i], bf)) {
			return 0;
		}
	}
	team->coach = (Coach*)malloc(sizeof(Coach));
	CHECK_RETURN_INT(team->coach);
	if (!readCoachFromBinaryFile(team->coach, bf)) {
		return 0;
	}
	return 1;
}
int	writeTeamToBinaryFile(const Team* team, FILE* bf) {
	int len = (int)strlen(team->name) + 1;
	if (fwrite(&len, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(team->name, sizeof(char), len, bf) != len) {
		return 0;
	}
	if (fwrite(&team->points, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&team->numOfPlayers, sizeof(int), 1, bf) != 1) {
		return 0;
	}
	if (fwrite(&team->sortType, sizeof(int), 1, bf) != 1) {
		return 0;
	}	
	if (fwrite(&team->formationType, sizeof(int), 1, bf) != 1) {
		return 0;
	}

	for (int i = 0; i < team->numOfPlayers; i++)
	{
		if (!writePlayerToBinaryFile(team->playerArr[i], bf)) {
			return 0;
		}
	}
	if (!writeCoachToBinaryFile(team->coach, bf)) {
		return 0;
	}
	return 1;
}


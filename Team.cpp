//
// Created by omerd on 21/11/2022.
//
#include "Team.h"

//****************************** COMPLETE players FIELD!!!! **********************************************************//

Team::Team() : teamID(NULL), points(NULL) {}

Team::Team(int teamID, int points) : teamID(teamID), players(AVL<PointerPlayer>()), points(points), totalGoals(0),
                                    totalCards(0), numPlayers(0), numGuards(0)   , numGames(0), bestGoals(nullptr) {}

int Team::getTeamID() const
{
    return teamID;
}
bool Team::isEmpty() const {
{
    return players.AVL::isEmpty();
}






int Team::getTeamID() const
{
    return teamID;
}

int Team::getTotalGoals() const
{
    return totalGoals;
}

int Team::getTotalCards() const
{
    return totalCards;
}

int Team::getNumPlayers() const
{
    return numPlayers;
}

Player* Team::getBestGoals() const
{
    return bestGoals;
}

void Team::setTotalGoals(int totalGoals)
{
    this->totalGoals = totalGoals;
}

void Team::setTotalCards(int totalCards)
{
    this->totlaCards = totalCards;
}

void Team::setNumPlayers(int numPlayers)
{
    this->numPlayers = numPlayers;
}

bool Team::hasGaurd() const
{
    return (numGuards >0);
}
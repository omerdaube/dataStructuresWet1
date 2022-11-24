//
// Created by omerd on 21/11/2022.
//
#include "Team.h"

//****************************** COMPLETE players FIELD!!!! **********************************************************//

Team::Team() : teamID(0), points(0), players(AVL<shared_ptr<Player>>()), totalGoals(0), totalCards(0), numPlayers(0), numGuards(0), numGames(0), bestGoals(shared_ptr<Player>())  {}

Team::Team(int teamID, int points) : teamID(teamID), points(points), players(AVL<shared_ptr<Player>>()), totalGoals(0),
                                    totalCards(0), numPlayers(0), numGuards(0), numGames(0), bestGoals(shared_ptr<Player>()) {}

int Team::getTeamID() const
{
    return teamID;
}
bool Team::isEmpty() const
{
    return players.AVL::isEmpty();
}

int Team::getNumGuards() const
{
    return numGuards;
}

int Team::getNumGames() const
{
    return numGames;
}

AVL<shared_ptr<Player>> Team::getPlayers() const
{
    return players;
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

shared_ptr<Player> Team::getBestGoals() const
{
    return bestGoals;
}

void Team::setTotalGoals(int totalGoals)
{
    this->totalGoals = totalGoals;
}

void Team::setTotalCards(int totalCards)
{
    this->totalCards = totalCards;
}

void Team::setNumPlayers(int numPlayers)
{
    this->numPlayers = numPlayers;
}

void Team::setNumGuards(int numGuards)
{
    this->numGuards = numGuards;
}

void Team::setBestGoals(shared_ptr<Player> newB)
{
    bestGoals = newB;
}

bool Team::hasGuard() const
{
    return (numGuards > 0);
}

void Team::setPoints(int p) {
    this->points = p;
}

int Team::getPoints() const {
    return this->points;
}

void Team::setNumGames(int numGames) {
    this->numGames = numGames;
}

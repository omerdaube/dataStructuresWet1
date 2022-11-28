//
// Created by omerd on 21/11/2022.
//
#include "Team.h"

//****************************** COMPLETE players FIELD!!!! **********************************************************//

Team::Team() : teamID(0), points(0), players(AVL<shared_ptr<Player>, PlayersByGoals>()), totalGoals(0), totalCards(0), numPlayers(0), numGuards(0), numGames(0), bestGoals(shared_ptr<Player>())  {}

Team::Team(int teamID, int points) : teamID(teamID), points(points), players(AVL<shared_ptr<Player>, PlayersByGoals>()), totalGoals(0),
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
void Team::addPlayerToAvl(shared_ptr<Player> p){
    this->players.add(p);
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

int Team::getCompetitionPlayMatchScore() const
{
    return this->competitionPlayMatchScore;
}

void Team::setNextTeam(shared_ptr<Team> nextTeam)
{
    this->nextTeam = nextTeam;
}

void Team::setNextTeamInCompetition(shared_ptr<Team> nextTeamInCompetition)
{
    this->nextTeamInCompetition = nextTeamInCompetition;
}

void Team::setPrevTeamInCompetition(shared_ptr<Team> nextTeamInCompetition)
{
    this->prevTeamInCompetition = prevTeamInCompetition;
}

AVL<shared_ptr<Player>, PlayersByGoals> Team::getPlayers() const
{
    return this->players;
}

shared_ptr<Team> Team::getNextTeam() const
{
    return this->nextTeam;
}
shared_ptr<Team> Team::getNextInCompetition() const
{
    return this->nextTeamInCompetition;
}

shared_ptr<Team> Team::getPrevInCompetition() const
{
    return this->prevTeamInCompetition;
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

void Team::setCompetitionPlayMatchScore(int competitionPlayMatchScore)
{
    this->competitionPlayMatchScore = -competitionPlayMatchScore;
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

void Team::removePlayerFromAvl(shared_ptr<Player> p) {
    this->players.remove(p);
}

shared_ptr<Player> Team::getMostRightFromAvl() {
    return this->players.getMostRight()->getData();
}

void Team::deleteTree() {
    this->players.deleteAll();
}

AVL<shared_ptr<Player>, PlayersByGoals>** Team::getArrOfAvl() {
    return players.avlToArr();
}

AVL<shared_ptr<Player>, PlayersByGoals> **Team::avlToArrTeam() {
    return players.avlToArr();
}

Team::Team(int teamID, int points, AVL<shared_ptr<Player>, PlayersByGoals> players, int totalGoals, int totalCards,
           int numPlayers, int numGuards, int numGames, shared_ptr<Player> bestGoals) :
           teamID(teamID), points(points), players(players), totalGoals(totalGoals), totalCards(totalCards),
           numPlayers(numPlayers), numGuards(numGuards), numGames(numGames), bestGoals(bestGoals){

}

void Team::addGamesPlayedToEachPlayer() {
    rec(players);
    this->numGames = 0;
}

void Team::rec(AVL<shared_ptr<Player>, PlayersByGoals> a){
    if(a.getLeft()){
        rec(a.getLeft());
    }
    if(a.getData()) {
        a.getData()->setNumGames(a.getData()->getNumGames() + this->numGames);
    }
    if(a.getRight()){
        rec(a.getRight());
    }
}

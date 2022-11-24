//
// Created by omerd on 21/11/2022.
//

#include "Player.h"
#include "PointerPlayer.h"
#include "Team.h"
/*
bool operator<(const Player& p1, const Player& p2){
    if(p1.getGoals() < p2.getGoals())
        return true;
    else if(p1.getGoals() == p2.getGoals()){
        if(p1.getCards() > p2.getCards())
            return true;
        else if(p1.getCards() == p2.getCards()){
            if(p1.getPalyerID() < p2.getPlayerID())
                return true;
            return false;
        }
        return false;
    }
    return false;

}
 */

//bool operator==(const Player& p1, const Player& p2){
//    return p1.playerID == p2.playerID;
//}
//
//bool Player::operator>(const Player& p2) const{
//    return !(*this == p2) && !(*this < p2);
//}


Player::Player() : playerID(NULL), numCards(0), numGoals(0), isGuard(false), numGames(0), myTeam(shared_ptr<Team>()){}

Player::Player(int playerID, int numCards, int numGoals, bool isGaurd, int gamesPlayed, shared_ptr<Team> myTeam) :
    playerID(playerID), numCards(numCards), numGoals(numGoals), isGuard(isGaurd), numGames(gamesPlayed), myTeam(myTeam){}

//bool Player::operator==(int iden) const{
//    return this->playerID == iden;
//}
//
//bool Player::operator<(int iden) const{
//    return this->playerID < iden;
//}

int Player::getNumCards() const {
    return this->numCards;
}

int Player::getNumGoals() const {
    return this->numGoals;
}

int Player::getPlayerID() const {
    return this->playerID;
}

int Player::getNumGames() const
{
    return this->numGames;
}

shared_ptr<Team> Player::getTeam() const {
    return this->myTeam;
}

void Player::setNumGames(int num)
{
    this->numGames = num;
}

void Player::setNumGoals(int num)
{
    this->numGoals = num;
}

void Player::setNumCards(int num)
{
    this->numCards = num;
}

int Player::getIsGuard() const
{
    return isGuard;
}

void Player::eraseTeam() {
    this->myTeam.reset();
}


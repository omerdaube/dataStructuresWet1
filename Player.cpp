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


Player::Player() : playerID(NULL), numCards(0), numGoals(0), isGaurd(false), myTeam(nullptr){}

Player::Player(int ID, int numCards, int numGoals, bool isGaurd, Team* myTeam) :
    playerID(ID), numCards(numCards), numGoals(numGoals), isGaurd(isGaurd), myTeam(myTeam){}

bool Player::operator==(int iden) const{
    return this->playerID == iden;
}

bool Player::operator<(int iden) const{
    return this->playerID < iden;
}

int Player::getCards() const {
    return this->numCards;
}

int Player::getGoals() const {
    return this->numGoals;
}

int Player::getPlayerID() const {
    return this->playerID;
}

Team* Player::getTeam() const {
    return myTeam;
}

PointerPlayer* Player::getPlayerPointer() const {
    return playerInTeam;
}
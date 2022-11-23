//
// Created by mayan on 23-Nov-22.
//

#include "Player.h"
#include "PointerPlayer.h"

PointerPlayer::PointerPlayer() {}

PointerPlayer::PointerPlayer(Player* playerP) : playerP(playerP) {}

const Player* PointerPlayer::getPlayerP() const
{
    return playerP;
}

bool PointerPlayer::operator<(int iden) const
{
    const Player* playerPointer = this->getPlayerP();
    return (playerPointer->getPlayerID() < iden);
}

bool PointerPlayer::operator==(int iden) const
{
    const Player* playerPointer = this->getPlayerP();
    return (playerPointer->getPlayerID() == iden);
}


bool operator<(const PointerPlayer& pointerP1, const PointerPlayer& pointerP2)
{
    const Player *p1 = pointerP1.getPlayerP(), *p2 = pointerP2.getPlayerP();
    if (p1->getGoals() < p2->getGoals()) {
        return true;
    }
    if (p1->getGoals() == p2->getGoals()) {
        if(p1->getCards() > p2->getCards()) {
            return true;
        }
        else if(p1->getCards() == p2->getCards()) {
            if(p1->getPlayerID() < p2->getPlayerID())
                return true;
            return false;
        }
        return false;
    }
    return false;
}

bool operator==(const PointerPlayer& pointerP1, const PointerPlayer& pointerP2)
{
    const Player *p1 = pointerP1.getPlayerP(), *p2 = pointerP2.getPlayerP();
    return (p1->getPlayerID() == p2->getPlayerID());
}
//
// Created by mayan on 24-Nov-22.
//

#include "PlayersByID.h"

PlayersByID::PlayersByID(shared_ptr<Player> player1, shared_ptr<Player> player2, Condition c) : player1(player1),
                            player2(player2), c(c) {}

bool PlayersByID::operator() () const
{
    bool toRet;
    Player p1 = *player1, p2 = *player2;
    switch(c) {
        case Equals:
            toRet = p1.getPlayerID() == p2.getPlayerID();
            break;
        case GreaterThan:
            toRet = p1.getPlayerID() > p2.getPlayerID();
            break;
        default:
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
            toRet = false;
            break;
    }
    return toRet;
}
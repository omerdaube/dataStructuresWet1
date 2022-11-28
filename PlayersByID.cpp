//
// Created by mayan on 24-Nov-22.
//

#include "PlayersByID.h"

PlayersByID::PlayersByID(shared_ptr<Player> player1, shared_ptr<Player> player2, int c) : player1(player1),
                                                                                          player2(player2), c(c) {}
PlayersByID::PlayersByID(shared_ptr<Player> player1, int player2, int c) : player1(player1),
                                                                                          player2(make_shared<Player>(player2)), c(c) {}

bool PlayersByID::operator() () const
{
    bool toRet;
    if(!player1 || !player2){
        return false;
    }
    Player p1 = *player1, p2 = *player2;
    switch(c) {
        case 0:
            toRet = p1.getPlayerID() == p2.getPlayerID();
            break;
        case 1:
            toRet = p1.getPlayerID() > p2.getPlayerID();
            break;
        default:
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
            toRet = false;
            break;
    }
    return toRet;
}
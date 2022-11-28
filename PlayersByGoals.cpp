//
// Created by mayan on 24-Nov-22.
//

#include "PlayersByGoals.h"

PlayersByGoals::PlayersByGoals(shared_ptr<Player> player1, shared_ptr<Player> player2, int c) : player1(player1),
                                player2(player2), c(c) {}

bool PlayersByGoals::operator() () const
{
    bool toRet = false;

    if(!player1 || !player2){
        switch (c) {
            case 0:
                if(!player1 && !player2)
                    toRet = true;
                break;
            case 1:
                if(!player2)
                    toRet = true;
                break;
            default:
                break;
        }
    }
    else{
        Player p1 = *player2, p2 = *player1;
        switch(c) {
            case 0:
                toRet = p1.getPlayerID() == p2.getPlayerID();
                break;
            case 1:
                if(p1.getNumGoals() < p2.getNumGoals()) {
                    toRet = true;
                }
                else if(p1.getNumGoals() == p2.getNumGoals()){
                    if(p1.getNumCards() > p2.getNumCards()) {
                        toRet = true;
                    }
                    else if(p1.getNumCards() == p2.getNumCards()){
                        if(p1.getPlayerID() < p2.getPlayerID()) {
                            toRet = true;
                        }
                    }
                }
                break;
            default:
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                toRet = false;
                break;
        }
    }

    return toRet;
}

//
// Created by mayan on 24-Nov-22.
//

#ifndef DATASTRUCTURESWET1_PLAYERSBYGOALS_H
#define DATASTRUCTURESWET1_PLAYERSBYGOALS_H

#include "Player.h"

class PlayersByGoals {
private:
    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
public:
    int c;
    PlayersByGoals(shared_ptr<Player> player1, shared_ptr<Player> player2, int c);

    bool operator() () const;

};

#endif //DATASTRUCTURESWET1_PLAYERSBYGOALS_H
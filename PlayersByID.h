//
// Created by mayan on 24-Nov-22.
//

#ifndef DATASTRUCTURESWET1_PLAYERSBYID_H
#define DATASTRUCTURESWET1_PLAYERSBYID_H

#include "Player.h"

class PlayersByID {
private:
    enum Condition {Equals, GreaterThan};
    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
    Condition c;
public:
    PlayersByID(shared_ptr<Player> player1, shared_ptr<Player> player2, Condition c);

    bool operator() () const;

};

#endif //DATASTRUCTURESWET1_PLAYERSBYID_H
//
// Created by mayan on 24-Nov-22.
//

#ifndef DATASTRUCTURESWET1_PLAYERSBYID_H
#define DATASTRUCTURESWET1_PLAYERSBYID_H

#include "Player.h"

class PlayersByID {
private:
    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
public:
    int c;

    PlayersByID(shared_ptr<Player> player1, shared_ptr<Player> player2, int c);
    PlayersByID(shared_ptr<Player> player1, int player2, int c);

    bool operator() () const;

};

#endif //DATASTRUCTURESWET1_PLAYERSBYID_H
//
// Created by mayan on 24-Nov-22.
//

#ifndef DATASTRUCTURESWET1_TEAMSBYID_H
#define DATASTRUCTURESWET1_TEAMSBYID_H

#include "Team.h"

class TeamsByID {
private:
    shared_ptr<Team> team1;
    shared_ptr<Team> team2;
public:
    int c;
    TeamsByID(shared_ptr<Team> team1, shared_ptr<Team> team2, int c);
    TeamsByID(shared_ptr<Team> team1, int team2, int c);

    bool operator() () const;

};

#endif //DATASTRUCTURESWET1_TEAMSBYID_H
//
// Created by mayan on 24-Nov-22.
//

#ifndef DATASTRUCTURESWET1_TEAMSBYID_H
#define DATASTRUCTURESWET1_TEAMSBYID_H

#include "Team.h"

class TeamsByID {
private:
    enum Condition {Equals, GreaterThan};
    shared_ptr<Team> team1;
    shared_ptr<Team> team2;
    Condition c;
public:
    TeamsByID(shared_ptr<Team> team1, shared_ptr<Team> team2, Condition c);

    bool operator() () const;

};

#endif //DATASTRUCTURESWET1_TEAMSBYID_H
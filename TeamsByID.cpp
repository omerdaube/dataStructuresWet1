//
// Created by mayan on 24-Nov-22.
//

#include "TeamsByID.h"

TeamsByID::TeamsByID(shared_ptr<Team> team1, shared_ptr<Team> team2, Condition c) : team1(team1), team2(team2), c(c) {}

bool TeamsByID::operator() () const
{
    bool toRet;
    Team t1 = *team1, t2 = *team2;
    switch(c) {
        case Equals:
            toRet = (t1.getTeamID() == t2.getTeamID());
            break;
        case GreaterThan:
            toRet = (t1.getTeamID() > t2.getTeamID());
            break;
        default:
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            toRet = false;
            break;
    }
    return toRet;
}
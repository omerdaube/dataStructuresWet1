//
// Created by mayan on 24-Nov-22.
//

#include "TeamsByID.h"

TeamsByID::TeamsByID(shared_ptr<Team> team1, shared_ptr<Team> team2, int c) : team1(team1), team2(team2), c(c) {}

bool TeamsByID::operator() () const
{
    bool toRet;
    if(!team1 || !team2){
        return false;
    }
    Team t1 = *team1, t2 = *team2;
    switch(c) {
        case 0:
            toRet = (t1.getTeamID() == t2.getTeamID());
            break;
        case 1:
            toRet = (t1.getTeamID() > t2.getTeamID());
            break;
        default:
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            toRet = false;
            break;
    }
    return toRet;
}

TeamsByID::TeamsByID(shared_ptr<Team> team1, int team2, int c) : team1(team1), team2(make_shared<Team>(team2, 0)), c(c){

}

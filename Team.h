//
// Created by omerd on 21/11/2022.
//

#ifndef MIVNY1_TEAM_H
#define MIVNY1_TEAM_H

#include "AVL.h"
#include "PointerPlayer.h"

class Team {
private:
    int teamID;
    AVL<PointerPlayer> players;
    int points;
    int totalGoals;
    int totalCards;
    int numPlayers;
    int numGuards;
    int numGames;
    PointerPlayer* bestGoals;
public:
    Team();
    Team(int teamID, int points);
    int getTeamID() const;
    bool operator>(const Team&) const;
    bool operator==(int i) const;
    friend bool operator<(const Team&, const Team&);
    friend bool operator==(const Team&, const Team&);
};


#endif //MIVNY1_TEAM_H

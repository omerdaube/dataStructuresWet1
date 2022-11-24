//
// Created by omerd on 21/11/2022.
//

#ifndef MIVNY1_TEAM_H
#define MIVNY1_TEAM_H

#include "AVL.h"
#include "PointerPlayer.h"
#include "PointerTeam.h"

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
    PointerTeam* nonEmpty;
    Player* bestGoals;
public:
    Team();
    Team(int teamID, int points);
    int getTeamID() const;
    int getTotalGoals() const;
    int getTotalCards() const;
    int getNumPlayers() const;
    int getNumGuards() const;
    int getNumGames() const;
    AVL<PointerPlayer> getPlayers() const;
    Player* getBestGoals() const;
    void setTotalGoals(int totalGoals);
    void setTotalCards(int totalCards);
    void setNumPlayers(int numPlayers);
    void setNumGuards(int numCards);
    void setBestGoals(Player* bestGoals);
    bool hasGaurd() const;
    AVL<PointerPlayer> getAVL() const;
    bool isEmpty() const;
    bool operator>(const Team&) const;
    bool operator==(int) const;
    bool operator>(int);
    friend bool operator<(const Team&, const Team&);
    friend bool operator==(const Team&, const Team&);
};

bool Team::operator==(int i) const{
    return *this == Team(i,0);
}

bool operator<(const Team& t1, const Team& t2){
    return t1.teamID < t2.teamID;
}

bool operator==(const Team& t1, const Team& t2){
    return t1.teamID == t2.teamID;
}

bool Team::operator>(const Team& t2) const{
    return !(*this == t2 && *this < t2);
}

bool Team::operator>(int i){
    return *this > Team(i,0);
}

AVL<PointerPlayer> Team::getAVL() const{
    return players;
}
#endif //MIVNY1_TEAM_H

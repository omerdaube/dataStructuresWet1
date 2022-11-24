//
// Created by omerd on 21/11/2022.
//

#ifndef MIVNY1_TEAM_H
#define MIVNY1_TEAM_H

#include "AVL.h"
#include "Player.h"
#include <memory>
using namespace std;

class Team {
private:
    int teamID;
    int points;
    AVL<shared_ptr<Player>> players;
    int totalGoals;
    int totalCards;
    int numPlayers;
    int numGuards;
    int numGames;
    shared_ptr<Player> bestGoals;

public:
    Team();
    Team(int teamID, int points);
    int getTeamID() const;
    int getPoints() const;
    int getTotalGoals() const;
    int getTotalCards() const;
    int getNumPlayers() const;
    int getNumGuards() const;
    int getNumGames() const;
    shared_ptr<Player> getBestGoals() const;
    void setPoints(int);
    void setTotalGoals(int totalGoals);
    void setTotalCards(int totalCards);
    void setNumPlayers(int numPlayers);
    void setNumGuards(int numCards);
    void setNumGames(int numGames);
    void setBestGoals(shared_ptr<Player> bestGoals);
    bool hasGuard() const;
    bool isEmpty() const;
    AVL<shared_ptr<Player>> getPlayers() const;

//    bool operator>(const Team&) const;
//    bool operator==(int) const;
//    bool operator>(int);
//    friend bool operator<(const Team&, const Team&);
//    friend bool operator==(const Team&, const Team&);
};

//bool Team::operator==(int i) const{
//    return *this == Team(i,0);
//}
//
//bool operator<(const Team& t1, const Team& t2){
//    return t1.teamID < t2.teamID;
//}
//
//bool operator==(const Team& t1, const Team& t2){
//    return t1.teamID == t2.teamID;
//}
//
//bool Team::operator>(const Team& t2) const{
//    return !(*this == t2 && *this < t2);
//}
//
//bool Team::operator>(int i){
//    return *this > Team(i,0);
//}


#endif //MIVNY1_TEAM_H

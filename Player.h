//
// Created by omerd on 21/11/2022.
//

#ifndef MIVNY1_PLAYER_H
#define MIVNY1_PLAYER_H
#include <memory>
#include "DoublyLinkedList.h"
class Team;
using namespace std;

class Player {
private:
    int playerID;
    int numGames;
    int numCards;
    int numGoals;
    bool isGuard;
    DoublyLinkedList<shared_ptr<Player>> placeInGoalList;
    shared_ptr<Team> myTeam;

public:
    Player();
    Player(int playerID, int numCards, int numGoals, bool isGaurd, int gamesPlayed, shared_ptr<Team> myTeam);
    Player(int playerID);
    int getNumCards() const;
    int getNumGoals() const;
    int getPlayerID() const;
    DoublyLinkedList<shared_ptr<Player>> getPlace() const;
    int getNumGames() const;
    int getIsGuard() const;
    shared_ptr<Team> getTeam() const;
    void setNumGames(int);
    void eraseTeam();
    void setNumGoals(int);
    void setPlace(DoublyLinkedList<shared_ptr<Player>>);
    void setNumCards(int);
//    bool operator>(const Player&) const;
//    friend bool operator<(const Player&, const Player&);
//    friend bool operator==(const Player&, const Player&);
//    bool operator==(int) const;
//    bool operator<(int) const;
};


#endif //MIVNY1_PLAYER_H

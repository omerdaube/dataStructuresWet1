//
// Created by omerd on 21/11/2022.
//

#ifndef MIVNY1_TEAM_H
#define MIVNY1_TEAM_H

#include "AVL.h"
#include "Player.h"
#include "PlayersByGoals.h"
#include <memory>
using namespace std;

class Team {
private:
    int teamID;
    int points;
    AVL<shared_ptr<Player>, PlayersByGoals> players;
    int totalGoals;
    int totalCards;
    int numPlayers;
    int numGuards;
    int numGames;
    shared_ptr<Player> bestGoals;
    shared_ptr<Team> nextTeam;
    shared_ptr<Team> nextTeamInCompetition;
    shared_ptr<Team> prevTeamInCompetition;
    int competitionPlayMatchScore;

public:
    Team();
    Team(int teamID, int points);
    Team(int teamID, int points, AVL<shared_ptr<Player>, PlayersByGoals> players, int totalGoals, int totalCards, int numPlayers, int numGuards, int numGames, shared_ptr<Player> bestGoals);
    AVL<shared_ptr<Player>, PlayersByGoals> getPlayers() const;
    shared_ptr<Team> getNextTeam() const;
    shared_ptr<Team> getNextInCompetition() const;
    shared_ptr<Team> getPrevInCompetition() const;
    int getTeamID() const;
    int getPoints() const;
    void addGamesPlayedToEachPlayer();
    void updatePlayersTeam(shared_ptr<Team> nt);
    void rec2(AVL<shared_ptr<Player>, PlayersByGoals> a, shared_ptr<Team> nt);
    void rec(AVL<shared_ptr<Player>, PlayersByGoals> a);
    int getTotalGoals() const;
    int getTotalCards() const;
    int getNumPlayers() const;
    int getNumGuards() const;
    int getNumGames() const;
    shared_ptr<Player> getBestGoals() const;
    int getCompetitionPlayMatchScore() const;
    void setNextTeam(shared_ptr<Team> nextTeam);
    void setNextTeamInCompetition(shared_ptr<Team> nextTeamInCompetition);
    void setPrevTeamInCompetition(shared_ptr<Team> nextTeamInCompetition);
    void setPoints(int);
    void setTotalGoals(int totalGoals);
    void setTotalCards(int totalCards);
    void setNumPlayers(int numPlayers);
    void setNumGuards(int numCards);
    void setNumGames(int numGames);
    void setBestGoals(shared_ptr<Player> bestGoals);
    void setCompetitionPlayMatchScore(int competitionPlayMatchScore);
    bool hasGuard() const;
    bool isEmpty() const;
    void deleteTree();
    //AVL<shared_ptr<Player>, PlayersByGoals> getPlayers() const;
    void addPlayerToAvl(shared_ptr<Player> p);
    shared_ptr<AVL<shared_ptr<Player>, PlayersByGoals>>* getArrOfAvl();
    void removePlayerFromAvl(shared_ptr<Player> p);
    shared_ptr<AVL<shared_ptr<Player>, PlayersByGoals>>* avlToArrTeam();
    shared_ptr<Player> getMostRightFromAvl();
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

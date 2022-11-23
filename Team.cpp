//
// Created by omerd on 21/11/2022.
//
#include "Team.h"

//****************************** COMPLETE players FIELD!!!! **********************************************************//

Team::Team() : teamID(NULL), points(NULL) {}

Team::Team(int teamID, int points) : teamID(teamID), players(AVL<PointerPlayer>()), points(points), totalGoals(0),
                                    totalCards(0), numPlayers(0), numGuards(0)   , numGames(0), bestGoals(nullptr) {}

int Team::getTeamID() const
{
    return teamID;
}

bool Team::operator>(const Team&) const{

}

bool Team::operator==(int i) const{

}

bool operator<(const Team&, const Team&){

}

bool operator==(const Team&, const Team&){

}



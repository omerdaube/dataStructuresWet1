//
// Created by omerd on 21/11/2022.
//

#ifndef MIVNY1_PLAYER_H
#define MIVNY1_PLAYER_H

class Team;
class PointerPlayer;

class Player {
private:
    int playerID;
    Team* myTeam;
    PointerPlayer* playerInTeam;
    PointerPlayer* playerInGoals;
    int numGames;
    int numCards;
    int numGoals;
    bool isGaurd;
    Player* closestPlayer;

public:
    Player();
    Player(int playerID, int numCards, int numGoals, bool isGaurd, Team* myTeam);
    int getCards() const;
    int getGoals() const;
    int getPlayerID() const;
    PointerPlayer* getPlayerPointer() const;
    Team* getTeam() const;
    bool operator>(const Player&) const;
    friend bool operator<(const Player&, const Player&);
    friend bool operator==(const Player&, const Player&);
    bool operator==(int) const;
    bool operator<(int) const;
};


#endif //MIVNY1_PLAYER_H

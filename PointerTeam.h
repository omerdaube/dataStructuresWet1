//
// Created by mayan on 23-Nov-22.
//

#ifndef MIVNY1_POINTERTEAM_H
#define MIVNY1_POINTERTEAM_H

class Team;

class PointerTeam {
private:
    Team* teamP;
public:
    PointerTeam();
    explicit PointerTeam(Team* teamP);
    Team* getTeamP() const;
    bool operator<(int iden) const;
    bool operator==(int iden) const;
    friend bool operator<(const PointerTeam& pointerT1, const PointerTeam& pointerT2);
    friend bool operator==(const PointerTeam& pointerT1, const PointerTeam& pointerT2);
    //bool operator>(const Player&) const;
};

#endif //MIVNY1_POINTERTEAM_H
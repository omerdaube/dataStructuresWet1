//
// Created by mayan on 23-Nov-22.
//

//
// Created by mayan on 23-Nov-22.
//

#include "Player.h"
#include "Team.h"
#include "PointerTeam.h"

PointerTeam::PointerTeam() : teamP(nullptr) {}

PointerTeam::PointerTeam(Team* teamP) : teamP(teamP) {}

Team* PointerTeam::getTeamP() const
{
    return teamP;
}

bool PointerTeam::operator<(int iden) const
{
    Team* teamPointer = this->getTeamP();
    return (teamPointer->getTeamID() < iden);
}

bool PointerTeam::operator==(int iden) const
{
    const Team* teamPointer = this->getTeamP();
    return (teamPointer->getTeamID() == iden);
}


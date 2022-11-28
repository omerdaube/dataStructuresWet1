#include "worldcup23a1.h"
//#include "PlayersByGoals.h"
#include <cstdlib>

world_cup_t::world_cup_t() : avlPlayersByID(), avlPlayersByGoals(), teams(), nonEmptyTeams(), playersByGoalsList(), totalPlayers(0), totalTeams(0), bestPlayer()
{

}

world_cup_t::~world_cup_t()
{
    removeTeamPtrInPlayers(&avlPlayersByID);
    deleteInnerTeams(teams);
    avlPlayersByID.deleteAll();
    avlPlayersByGoals.deleteAll();
    teams.deleteAll();
    nonEmptyTeams.deleteAll();
}

StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId <= 0 || points < 0) {
        return StatusType::INVALID_INPUT;
    }
    if(teams.search(teamId) != nullptr) {
        return StatusType::FAILURE;
    }
    shared_ptr<Team> newTeam = make_shared<Team>(teamId, points);
    teams.add(newTeam);
    totalTeams++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    AVL<shared_ptr<Team>, TeamsByID> *ret = teams.search(teamId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    if(ret->getData()->isEmpty()){
        return StatusType::FAILURE;
    }
    teams.remove(ret->getData());
    totalTeams--;
    return StatusType::SUCCESS;
}
/*
void world_cup_t::updateClosestBelow(shared_ptr<Player> newPlayer, shared_ptr<Player> current)
{
    if (closestBelow == nullptr) {
        return closestAbove->getPlayerID();
    }
    if (closestAbove == nullptr) {
        return closestBelow->getPlayerID();
    }
    if (abs(newPlayer->getClosestBelow()->getNumGoals() - newPlayer->getNumGoals()) < abs(current->getNumGoals() - newPlayer->getNumGoals())) {
        return;
    }
    if (abs(newPlayer->getClosestBelow()->getNumGoals() - newPlayer->getNumGoals()) > abs(current->getNumGoals() - newPlayer->getNumGoals())) {
        newPlayer->setClosestBelow(current);
        current->setClosestAbove(newPlayer);
        return;
    }
    if (abs(newPlayer->getClosestBelow()->getNumCards() - newPlayer->getNumCards()) < abs(current->getNumCards() - newPlayer->getNumCards())) {
        return;
    }
    if (abs(newPlayer->getClosestBelow()->getNumCards() - newPlayer->getNumCards()) > abs(current->getNumCards() - newPlayer->getNumCards())) {
        newPlayer->setClosestBelow(current);
        current->setClosestAbove(newPlayer);
        return;
    }
    if (newPlayer->getClosestBelow()->getPlayerID() < current->getPlayerID()) {
        newPlayer->setClosestBelow(current);
        current->setClosestAbove(newPlayer);
        return;
    }
    return closestAbove->getPlayerID();
}
*/
void world_cup_t::updateClosestPlayers(shared_ptr<Player> newPlayer)
{
    AVL<shared_ptr<Player>, PlayersByGoals>* player = avlPlayersByGoals.search(newPlayer->getPlayerID());
    newPlayer->setClosestBelow(player->getPrevInorder()->getData());
    (newPlayer->getClosestBelow())->setClosestAbove(newPlayer);
    newPlayer->setClosestAbove(player->getNextInorder()->getData());
    (newPlayer->getClosestAbove())->setClosestBelow(newPlayer);



    /*
    AVL<shared_ptr<Player>, PlayersByGoals>* player = avlPlayersByGoals.search(newPlayer->getPlayerID());
    AVL<shared_ptr<Player>, PlayersByGoals>* current = player;
    while ((current->getFather() != nullptr) && ((current->getFather())->getRight() == current)) {
        updateClosestBelow()


        if(current->getData()->getNumGoals() < player->getData()->getNumGoals()) {
            if (abs(current->getData()->getNumGoals() - player->getData()->getNumGoals()) < abs(newPlayer->getClosest() < player->getData()->getNumGoals()))
        }
        else if(p1.getNumGoals() == p2.getNumGoals()){
            if(p1.getNumCards() > p2.getNumCards()) {
                toRet = true;
            }
            else if(p1.getNumCards() == p2.getNumCards()){
                if(p1.getPlayerID() < p2.getPlayerID()) {
                    toRet = true
                }
                toRet = false;
            }
            toRet = false;
        }
        toRet = false;
    }
    */
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper)
{
    if ((playerId <= 0) || (teamId <= 0) || (gamesPlayed < 0) || (goals < 0) ||
        (cards < 0) || ((gamesPlayed == 0) && ((goals > 0) || (cards > 0)))) {
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID>* playerTeam = teams.search(teamId);
    if (avlPlayersByID.search(playerId) || !playerTeam) {
        return StatusType::FAILURE;
    }
    try {
        shared_ptr<Player> newPlayer = make_shared<Player>(playerId, cards, goals, goalKeeper, gamesPlayed - playerTeam->getData()->getNumGames(), playerTeam->getData());
        avlPlayersByID.add(newPlayer);

        avlPlayersByGoals.add(newPlayer);
        updateClosestPlayers(newPlayer);
//        newPlayer->setClosestBelow(avlPlayersByGoals.findPrevInorder());
//        (newPlayer->getClosestBelow())->setClosestAbove(newPlayer);
//        newPlayer->setClosestAbove(newPlayer->findNextInorder());
//        (newPlayer->getClosestAbove())->setClosestBelow(newPlayer);
        playerTeam->getData()->setTotalGoals(playerTeam->getData()->getTotalGoals() + goals);
        playerTeam->getData()->setTotalCards(playerTeam->getData()->getTotalCards() + cards);
        playerTeam->getData()->setNumPlayers(playerTeam->getData()->getNumPlayers() + 1);
        playerTeam->getData()->addPlayerToAvl(newPlayer);
        if (goalKeeper) {
            playerTeam->getData()->setNumGuards(playerTeam->getData()->getNumGuards() + 1);
        }
        this->totalPlayers++;
        if(!playerTeam->getData()->getBestGoals()){
            playerTeam->getData()->setBestGoals(newPlayer);
        }
        else if ((PlayersByGoals(newPlayer, playerTeam->getData()->getBestGoals(), 1))()){
            playerTeam->getData()->setBestGoals(newPlayer);
        }
//        else if (newPlayer->getNumGoals() > playerTeam->getData()->getBestGoals()->getNumGoals()) {
//            playerTeam->getData()->setBestGoals(newPlayer);
//        }
        if(!bestPlayer){
            bestPlayer = newPlayer;
        }
        else if(PlayersByGoals(newPlayer, bestPlayer, 1)()){
            bestPlayer = newPlayer;
        }
        if ((playerTeam->getData()->getNumPlayers() >= 11) && (playerTeam->getData()->getNumGuards() > 0)) {
            nonEmptyTeams.add(playerTeam->getData());
        }
    } catch(const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    bool check1 = false, check2 = false;
	if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Player>, PlayersByID> *ret = avlPlayersByID.search(playerId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    shared_ptr<Player> player1 = ret->getData();
    shared_ptr<Team> team1 = player1->getTeam();
    if(team1->getNumPlayers() >= 11 && team1->hasGuard()) {
        check1 = true;
    }
    team1->removePlayerFromAvl(player1);
    totalPlayers -= 1;
    team1->setTotalGoals(team1->getTotalGoals() - player1->getNumGoals());
    team1->setTotalCards(team1->getTotalCards() - player1->getNumCards());
    team1->setNumPlayers(team1->getNumPlayers() - 1);
    if(player1->getIsGuard()) {
        team1->setNumGuards(team1->getNumGuards() - 1);
    }
    if(team1->getNumPlayers() < 11 || !(team1->hasGuard())) {
        check2 = true;
    }
    if(check1 && check2){
        nonEmptyTeams.remove(team1);
    }
    if(player1 == team1->getBestGoals()) {
        team1->setBestGoals(team1->getMostRightFromAvl());
    }
    if(player1 == bestPlayer){
        bestPlayer = avlPlayersByGoals.getMostRight()->getData();
    }
    avlPlayersByGoals.remove(player1);
    avlPlayersByID.remove(player1);
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if(scoredGoals<0 || gamesPlayed<0 || cardsReceived<0 || playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Player>, PlayersByID> *ret = avlPlayersByID.search(playerId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    avlPlayersByGoals.remove(ret->getData());
    shared_ptr<Team> t = ret->getData()->getTeam();
    t->removePlayerFromAvl(ret->getData());
    t->setTotalCards(t->getTotalCards() + cardsReceived);
    t->setTotalGoals(t->getTotalGoals() + scoredGoals);
    ret->getData()->setNumCards(ret->getData()->getNumCards() + cardsReceived);
    ret->getData()->setNumGames(ret->getData()->getNumGames() + gamesPlayed);
    ret->getData()->setNumGoals(ret->getData()->getNumGoals() + scoredGoals);
//    if(ret->getData()->getNumGoals() > ret->getData()->getTeam()->getBestGoals()->getNumGoals()){
//        ret->getData()->getTeam()->setBestGoals(ret->getData());
//        if(ret->getData()->getNumGoals() > bestPlayer->getNumGoals()){
//            bestPlayer = ret->getData();
//        }
//    }
    if(PlayersByGoals(ret->getData(),ret->getData()->getTeam()->getBestGoals(),1)())
    {
        ret->getData()->getTeam()->setBestGoals(ret->getData());
        if(PlayersByGoals(ret->getData(), bestPlayer, 1)()){
            bestPlayer = ret->getData();
        }
    }
    t->addPlayerToAvl(ret->getData());
    avlPlayersByGoals.add(ret->getData());
    updateClosestPlayers(ret->getData());
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID> *retT1 = teams.search(teamId1);
    AVL<shared_ptr<Team>, TeamsByID> *retT2 = teams.search(teamId2);
    if (retT1 == nullptr || retT2 == nullptr){
        return StatusType::FAILURE;
    }
    if (retT1->getData()->getNumPlayers() < 11 ||
        retT2->getData()->getNumPlayers() < 11 ||
        !(retT1->getData()->hasGuard()) ||
        !(retT2->getData()->hasGuard())){
        return StatusType::FAILURE;
    }
    int calc1 = retT1->getData()->getTotalGoals() - retT1->getData()->getTotalCards() + retT1->getData()->getPoints();
    int calc2 = retT2->getData()->getTotalGoals() - retT2->getData()->getTotalCards() + retT2->getData()->getPoints();
    if(calc1 == calc2){
        retT1->getData()->setPoints(retT1->getData()->getPoints() + 1);
        retT2->getData()->setPoints(retT2->getData()->getPoints() + 1);
    }
    else if (calc1 < calc2){
        retT2->getData()->setPoints(retT2->getData()->getPoints() + 3);
    }
    else{
        retT1->getData()->setPoints(retT1->getData()->getPoints() + 3);
    }
    retT1->getData()->setNumGames(retT1->getData()->getNumGames() + 1);
    retT2->getData()->setNumGames(retT2->getData()->getNumGames() + 1);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if (playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Player>, PlayersByID> *ret = avlPlayersByID.search(playerId);
    if (ret == nullptr) {
        return StatusType::FAILURE;
    }
    shared_ptr<Player> p = ret->getData();
    shared_ptr<Team> t = p->getTeam();
    return output_t<int>(p->getNumGames() + t->getNumGames());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID> *ret = teams.search(teamId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    return output_t<int>(ret->getData()->getPoints());
}
/*
AVL<shared_ptr<Player>> world_cup_t::BetterTeamPlayer(AVL<shared_ptr<Player>> p1, AVL<shared_ptr<Player>> p2)
{
    if (p1->getNumGoals() > p2->getNumGoals()) {
        return p1;
    }
    return p2;
}
 */

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if ((newTeamId <= 0) || (teamId2 <= 0) || (teamId2 == teamId1) || (teamId1 <= 0)) {
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID> *team1 = teams.search(teamId1), *team2 = teams.search(teamId2), *newTeam;
    if ((!team1) || (!team2) || (teams.search(newTeamId) && newTeamId != teamId1 && newTeamId != teamId2)) {
        return StatusType::FAILURE;
    }
    updateInorder(updatePlayerPointsAccordingToGroup<team1->getPoints()>(team1);
    updateInorder(updatePlayerPointsAccordingToGroup<team2->getPoints()>(team2);
    newTeam = uniteTrees(team1, team1->getNumPlayers(), team2, team2->getNumPlayers());
    newTeam->setPoints(team1->getPoints() + team2->getPoints());
    newTeam->setNumCards(team1->getNumCards() + team2->getNumCards());
    newTeam->setNumGuards(team1->getNumGuards() + team2->getNumGuards());
    newTeam->setNumPlayers(team1->getNumPlayers() + team2->getNumPlayers());
    newTeam->setNumGoals(team1->getNumGoals() + team2->getNumGoals());
    newTeam->setNumGames(0);
    newTeam->setBestGoals(BetterTeamPlayer(team1->getBestGoals() + team2->getBestGoals()));
    teams.remove(team1->data);
    teams.remove(team2->data);
    nonEmptyTeams.remove(team1->data);
    nonEmptyTeams.remove(team2->data);
    teams.add(newTeam);
    if ((newTeams->getNumPlayers() >= 11) && (newTeams->hasGaurd())) {
        nonEmptyTeams.add(newTeam);
    }
    return StatusType::SUCCESS;
    return output_t<int>(ret->getData()->getPoints());
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    else if(teamId > 0){
        AVL<shared_ptr<Team>, TeamsByID> *ret = teams.search(teamId);
        if(ret == nullptr) {
            return StatusType::FAILURE;
        }
        return output_t<int>(ret->getData()->getBestGoals()->getPlayerID());
    }
    if(totalPlayers <= 0){
        return StatusType::FAILURE;
    }
    return output_t<int>(bestPlayer->getPlayerID());

}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    else if(teamId > 0){
        AVL<shared_ptr<Team>, TeamsByID> *ret = teams.search(teamId);
        if(ret == nullptr) {
            return StatusType::FAILURE;
        }
        return output_t<int>(ret->getData()->getNumPlayers());
    }
    return output_t<int>(totalPlayers);
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if (teamId == 0 || output == NULL){
        return StatusType::INVALID_INPUT;
    }
    output_t<int> retVal = get_all_players_count(teamId);
    int num = retVal.ans();
    if(teamId < 0){
        if(totalPlayers <= 0){
            return StatusType::FAILURE;
        }
        AVL<shared_ptr<Player>, PlayersByGoals>** a = avlPlayersByGoals.avlToArr();
        for (int i = 0; i < num; ++i) {
            output[i] = a[i]->getData()->getPlayerID();
        }
    }
    else{
        AVL<shared_ptr<Team>, TeamsByID> *ret = teams.search(teamId);
        if(ret == nullptr) {
            return StatusType::FAILURE;
        }
        AVL<shared_ptr<Player>, PlayersByGoals>** a = ret->getData()->getArrOfAvl();
        for (int i = 0; i < num; ++i) {
            output[i] = a[i]->getData()->getPlayerID();
        }
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    shared_ptr<Player> closestBelow, closestAbove;
    AVL<shared_ptr<Team>, TeamsByID>* team;
    AVL<shared_ptr<Player>, PlayersByGoals>* player;
    if ((playerId <= 0) || (teamId <= 0)) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    team = teams.search(teamId);
    if (!team) {
        return output_t<int>(StatusType::FAILURE);
    }
    player = team->getData()->getPlayers().search(playerId);
    if (!(player)) {
        return output_t<int>(StatusType::FAILURE);
    }
    if (totalPlayers <= 1) {
        return output_t<int>(StatusType::FAILURE);
    }
    closestBelow = player->getData()->getClosestBelow();
    closestAbove = player->getData()->getClosestAbove();
    if (closestBelow == nullptr) {
        return output_t<int>(closestAbove->getPlayerID());
    }
    if (closestAbove == nullptr) {
        return output_t<int>(closestBelow->getPlayerID());
    }
    if (abs(closestBelow->getNumGoals() - player->getData()->getNumGoals()) > abs(closestAbove->getNumGoals() - player->getData()->getNumGoals())) {
        return output_t<int>(closestAbove->getPlayerID());
    }
    if (abs(closestBelow->getNumGoals() - player->getData()->getNumGoals()) < abs(closestAbove->getNumGoals() - player->getData()->getNumGoals())) {
        return output_t<int>(closestBelow->getPlayerID());
    }
    if (abs(closestBelow->getNumCards() - player->getData()->getNumCards()) > abs(closestAbove->getNumCards() - player->getData()->getNumCards())) {
        return output_t<int>(closestAbove->getPlayerID());
    }
    if (abs(closestBelow->getNumCards() - player->getData()->getNumCards()) < abs(closestAbove->getNumCards() - player->getData()->getNumCards())) {
        return output_t<int>(closestBelow->getPlayerID());
    }
    if (closestBelow->getPlayerID() > closestAbove->getPlayerID()) {
        return output_t<int>(closestBelow->getPlayerID());
    }
    return output_t<int>(closestAbove->getPlayerID());
}


output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId) {
    if (minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId) {
        return StatusType::INVALID_INPUT;
    }
    /*
    AVL<shared_ptr<Team>, TeamsByID> *ret = nonEmptyTeams.getClosestAndBigger(minTeamId);
    if (ret == nullptr) {
        return StatusType::FAILURE;
    }
    if (ret->getData()->getTeamID() > maxTeamId) {
        return StatusType::FAILURE;
    }
     */

    //int currentScore, nextScore;

    AVL<shared_ptr<Team>, TeamsByID> *team = nonEmptyTeams.search(minTeamId), *next;
    shared_ptr<Team> teamP, firstTeam, current;
    if (!team) {
        try {
            teamP = make_shared<Team>(minTeamId, 0);
            nonEmptyTeams.add(teamP); ///////////////////////////////
            team = nonEmptyTeams.search(minTeamId);
            team = team->getNextInorder();
            nonEmptyTeams.remove(teamP);
        }
        catch (const std::exception &e) {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    if ((!team) || (team->getData()->getTeamID() > maxTeamId)) {
        return StatusType::FAILURE;
    }
    firstTeam = team->getData();
    current = firstTeam;
    while ((team != nullptr) && (team->getData() != nullptr) &&
           (team->getData()->getTeamID() <= maxTeamId)) {
        next = team->getNextInorder();
        if (next) {
            team->getData()->setNextTeamInCompetition(next->getData());
        } else {
            team->getData()->setNextTeamInCompetition(nullptr);
        }
        team->getData()->setCompetitionPlayMatchScore(team->getData()->getTotalGoals() -
                                                      team->getData()->getTotalCards() + team->getData()->getPoints());
    }
    while ((firstTeam) && (firstTeam->getNextInCompetition() != nullptr)) {
        current = firstTeam;
        while ((current != nullptr) && (current->getNextInCompetition() != nullptr) &&
               (current->getNextInCompetition()->getTeamID() <= maxTeamId)) {
            //currentScore = current->getTotalGoals() - current->getTotalCards() + current->getPoints();
            //nextScore = current->getNextInCompetition()->getTotalGoals()
            //- current->getNextInCompetition()->getTotalCards() + current->getNextInCompetition()->getPoints();
            if (current->getCompetitionPlayMatchScore() <
                current->getNextInCompetition()->getCompetitionPlayMatchScore()) {
                current->getNextInCompetition()->setCompetitionPlayMatchScore(current->getCompetitionPlayMatchScore() +
                                                                              current->getNextInCompetition()->getCompetitionPlayMatchScore() +
                                                                              3);
                if (current == firstTeam) {
                    firstTeam = current->getNextInCompetition();
                }
                else {
                    (current->getPrevInCompetition())->setNextTeamInCompetition(current->getNextInCompetition());
                }
                current = current->getNextInCompetition()->getNextInCompetition();
            } else if (current->getCompetitionPlayMatchScore() >
                       current->getNextInCompetition()->getCompetitionPlayMatchScore()) {
                current->setCompetitionPlayMatchScore(current->getCompetitionPlayMatchScore() +
                                                      current->getNextInCompetition()->getCompetitionPlayMatchScore() +
                                                      3);
                current->setNextTeamInCompetition(current->getNextInCompetition()->getNextInCompetition());
                current = current->getNextInCompetition();
            } else {
                if (current->getTeamID() < current->getNextInCompetition()->getTeamID()) {
                    current->getNextInCompetition()->setCompetitionPlayMatchScore(
                            current->getCompetitionPlayMatchScore() +
                            current->getNextInCompetition()->getCompetitionPlayMatchScore() + 3);
                    if (current == firstTeam) {
                        firstTeam = current->getNextInCompetition();
                    }
                    else {
                        (current->getPrevInCompetition())->setNextTeamInCompetition(current->getNextInCompetition());
                    }
                    current = current->getNextInCompetition()->getNextInCompetition();
                } else {
                    current->setCompetitionPlayMatchScore(current->getCompetitionPlayMatchScore() +
                          current->getNextInCompetition()->getCompetitionPlayMatchScore() + 3);
                    current->setNextTeamInCompetition(current->getNextInCompetition()->getNextInCompetition());
                    current = current->getNextInCompetition();
                }
            }
        }
    }
    return firstTeam->getTeamID();
}


    /*
//    DoublyLinkedList<Team> dllR = DoublyLinkedList<Team>();
//    while (v != nullptr){
//        if(la)
//        Team nt = *(v->getData());
//        dllR.addNext(nt);
//        ret = v->getNextInorder();
//    }
//    */
//}

void world_cup_t::removeTeamPtrInPlayers(AVL<shared_ptr<Player>, PlayersByID> * avlPlayersID) {
    if(avlPlayersID == nullptr){
        return;
    }
    avlPlayersID->getData()->eraseTeam();
    removeTeamPtrInPlayers(avlPlayersID->getRight());
    removeTeamPtrInPlayers(avlPlayersID->getLeft());
}

void world_cup_t::deleteInnerTeams(AVL<shared_ptr<Team>, TeamsByID> teams2){
    if(teams2.getLeft())
        deleteInnerTeams(teams2.getLeft());
    teams2.getData()->deleteTree();
    if(teams2.getRight())
        deleteInnerTeams(teams2.getRight());
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId) {
    if ((newTeamId <= 0) || (teamId2 <= 0) || (teamId2 == teamId1) || (teamId1 <= 0)) {
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID> *team1 = teams.search(teamId1), *team2 = teams.search(teamId2);
    if ((!team1) || (!team2) || (teams.search(newTeamId) && newTeamId != teamId1 && newTeamId != teamId2)) {
        return StatusType::FAILURE;
    }
    shared_ptr<Team> t1 = team1->getData(), t2 = team2->getData();
    t1->addGamesPlayedToEachPlayer();
    t2->addGamesPlayedToEachPlayer();
    AVL<shared_ptr<Player>, PlayersByGoals>** arrOf1 = t1->avlToArrTeam();
    AVL<shared_ptr<Player>, PlayersByGoals>** arrOf2 = t2->avlToArrTeam();

    int na = team1->getData()->getNumPlayers(), nb = team2->getData()->getNumPlayers();
    AVL<shared_ptr<Player>, PlayersByGoals>** merged =
            new AVL<shared_ptr<Player>, PlayersByGoals>*[sizeof(AVL<shared_ptr<Player>, PlayersByGoals>*) * (na + nb)];
    int ia, ib, ic;
    for(ia = ib = ic = 0; (ia < na) && (ib < nb); ic++)
    {
        if (PlayersByGoals(arrOf2[ib]->getData(), arrOf1[ia]->getData(), 1)()) {
            merged[ic] = arrOf1[ia];
            ia++;
        }
        else {
            merged[ic] = arrOf2[ib];
            ib++;
        }
    }
    for(;ia < na; ia++, ic++) merged[ic] = arrOf1[ia];
    for(;ib < nb; ib++, ic++) merged[ic] = arrOf2[ib];
    AVL<shared_ptr<Player>, PlayersByGoals> newPlayers;
    newPlayers.arrToAvl(merged, na+nb);
    shared_ptr<Player> bestInBoth = PlayersByGoals(t1->getBestGoals(), t2->getBestGoals(), 1)()
            ? t1->getBestGoals() : t2->getBestGoals();
    shared_ptr<Team> newTeam = make_shared<Team>(newTeamId,
                 t1->getPoints() + t2->getPoints(),
                 newPlayers,
                 t1->getTotalGoals() + t2->getTotalGoals(),
                 t1->getTotalCards() + t2->getTotalCards(),
                 t1->getNumPlayers() + t2->getNumPlayers(),
                 t1->getNumGuards() + t2->getNumGuards(),
                 0,
                 bestInBoth);
    teams.remove(t1);
    teams.remove(t2);
    nonEmptyTeams.remove(t1);
    nonEmptyTeams.remove(t2);
    teams.add(newTeam);
    if ((newTeam->getNumPlayers() >= 11) && (newTeam->hasGuard())) {
        nonEmptyTeams.add(newTeam);
    }
    delete merged;
    return StatusType::SUCCESS;
}
#include "worldcup23a1.h"

world_cup_t::world_cup_t() : avlPlayersByID(), avlPlayersByGoals(), teams(), nonEmptyTeams(), playersByGoalsList(), totalPlayers(0), totalTeams(0), bestPlayer()
{

}

world_cup_t::~world_cup_t()
{
    removeTeamPtrInPlayers(&avlPlayersByID);
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

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper)
{
    if ((playerId <= 0) || (teamId <= 0) || (gamesPlayed < 0) || (goals < 0) ||
        (cards < 0) || ((gamesPlayed = 0) && ((goals > 0) || (cards > 0)))) {
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID>* playerTeam = teams.search(teamId);
    if (avlPlayersByID.search(playerId) || !playerTeam) {
        return StatusType::FAILURE;
    }
    try {
        shared_ptr<Player> newPlayer = make_shared<Player>(playerId, cards, goals, goalKeeper, gamesPlayed - playerTeam->getData()->getNumGames(), playerTeam->getData());
        avlPlayersByID.add(newPlayer);
        playerTeam->getData()->getPlayers().add(newPlayer);
        avlPlayersByGoals.add(newPlayer);
        playerTeam->getData()->setTotalGoals(playerTeam->getData()->getTotalGoals() + goals);
        playerTeam->getData()->setTotalCards(playerTeam->getData()->getTotalCards() + cards);
        playerTeam->getData()->setNumPlayers(playerTeam->getData()->getNumPlayers() + 1);
        if (goalKeeper) {
            playerTeam->getData()->setNumGuards(playerTeam->getData()->getNumGuards() + 1);
        }
        this->totalPlayers++;
        if (newPlayer->getNumGoals() > playerTeam->getData()->getBestGoals()->getNumGoals()) {
            playerTeam->getData()->setBestGoals(newPlayer);
            if (newPlayer->getNumGoals() > bestPlayer->getNumGoals()) {
                bestPlayer = newPlayer;
            }
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
    team1->getPlayers().remove(player1);
    totalPlayers -= 1;
    team1->setTotalGoals(team1->getTotalGoals() - player1->getNumGoals());
    team1->setTotalCards(team1->getTotalCards() - player1->getNumGoals());
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
        team1->setBestGoals(team1->getPlayers().getMostRight()->getData());
    }
    if(player1 == bestPlayer){
        bestPlayer = avlPlayersByGoals.getMostRight()->getData();
    }
    avlPlayersByGoals.remove(player1);
    avlPlayersByID.remove(player1);
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
    ret->getData()->setNumCards(ret->getData()->getNumCards() + cardsReceived);
    ret->getData()->setNumGames(ret->getData()->getNumGames() + gamesPlayed);
    ret->getData()->setNumGoals(ret->getData()->getNumGoals() + scoredGoals);
    if(ret->getData()->getNumGoals() > ret->getData()->getTeam()->getBestGoals()->getNumGoals()){
        ret->getData()->getTeam()->setBestGoals(ret->getData());
        if(ret->getData()->getNumGoals() > bestPlayer->getNumGoals()){
            bestPlayer = ret->getData();
        }
    }
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
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Player>, PlayersByID> *ret = avlPlayersByID.search(playerId);
    if(ret == nullptr) {
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
    if(teamId == 0 || output == NULL){
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
        AVL<shared_ptr<Player>, PlayersByGoals>** a = ret->getData()->getPlayers().treeToArray();
        for (int i = 0; i < num; ++i) {
            output[i] = a[i]->getData()->getPlayerID();
        }
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{

}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>, TeamsByID> *ret = nonEmptyTeams.getClosestAndBigger(minTeamId);
    if (ret == nullptr){
        return StatusType::FAILURE;
    }
    if (ret->getData()->getTeamID() > maxTeamId){
        return StatusType::FAILURE;
    }

    DoublyLinkedList<Team> dllR = DoublyLinkedList<Team>();
    while (v != nullptr){
        if(la)
        Team nt = *(v->getData());
        dllR.addNext(nt);
        ret = v->getNextInorder();
    }

}

void world_cup_t::removeTeamPtrInPlayers(AVL<shared_ptr<Player>, PlayersByID> * avlPlayersID) {
    if(avlPlayersID == nullptr){
        return;
    }
    avlPlayersID->getData()->eraseTeam();
    removeTeamPtrInPlayers(avlPlayersID->getRight());
    removeTeamPtrInPlayers(avlPlayersID->getLeft());
}

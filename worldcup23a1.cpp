#include "worldcup23a1.h"
world_cup_t::world_cup_t() : playersByID(), playersByGoals(), teams(), nonEmptyTeams(), playersByGoalsList(), totalPlayers(0), totalTeams(0), bestPlayer()
{

}

world_cup_t::~world_cup_t()
{
    removeTeamPtrInPlayers(&playersByID);
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
    AVL<shared_ptr<Team>> *ret = teams.search(teamId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    if(ret->data->isEmpty()){
        return StatusType::FAILURE;
    }
    teams.remove(ret->data);
    totalTeams--;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    AVL<Team>* playerTeam;
    PointerPlayer *teamPointerPlayer, *goalsPointerPlayer;
    if ((playerId <= 0) || (teamId <= 0) || (gamesPlayed < 0) || (goals < 0) ||
        (cards < 0) || ((gamesPlayed = 0) && ((goals > 0) || (cards > 0)))) {
        return StatusType::INVALID_INPUT;
    }
    playerTeam = teams.search(teamId);
    if (playersByID.search(playerId) || !playerTeam) {
        return StatusType::FAILURE;
    }
    try {
        Player *newPlayer = new Player(playerId, cards, goals, goalKeeper, gamesPlayed,
                                       &(playerTeam->data));
        playersByID.add(*newPlayer);
        teamPointerPlayer = new PointerPlayer(newPlayer);
        playerTeam->data.getPlayers().add(*teamPointerPlayer);
        goalsPointerPlayer = new PointerPlayer(newPlayer);
        playersByGoals.add(*goalsPointerPlayer);
        newPlayer->setPlayerInTeam(teamPointerPlayer);
        newPlayer->setNumGames(newPlayer->getNumGames() - playerTeam->data.getNumGames());
        playerTeam->totalGoals += goals;
        playerTeam->totalCards += cards;
        if (goalKeeper) {
            playerTeam->numGaurds++;
        }
        playerTeam->numPlayers++;
        totalPlayers++;
        if (newPlayer->getNumGoals()> playerTeam->bestGoals->getNumGoals()) {
            playerTeam->bestGoals = newPlayer;
            if (newPlayer->getNumGoals() > bestPlayer->getNumGoals()) {
                bestPlayer = newPlayer;
            }
        }
        if ((playerTeam->numPlayers >= 11) && (playerTeam->getNumGuards() > 0)) {
            nonEmptyTeams.add(new PointerTeam(playerTeam));
        }
    } catch(const std::exception& e) {
        return StatusType::ALLOCATION_ERROR; //???
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    bool check1 = false, check2 = false;
	if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Player>> *ret = playersByID.search(playerId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    shared_ptr<Player> player1 = ret->data;
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
        team1->setBestGoals(team1->getPlayers().getMostRight()->data);
    }
    if(player1 == bestPlayer){
        bestPlayer = playersByGoals.getMostRight()->data;
    }
    playersByGoals.remove(player1);
    playersByID.remove(player1);
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if(scoredGoals<0 || gamesPlayed<0 || cardsReceived<0 || playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Player>> *ret = playersByID.search(playerId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    ret->data->setNumCards(ret->data->getNumCards() + cardsReceived);
    ret->data->setNumGames(ret->data->getNumGames() + gamesPlayed);
    ret->data->setNumGoals(ret->data->getNumGoals() + scoredGoals);
    //NOTDONE

}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>> *retT1 = teams.search(teamId1);
    AVL<shared_ptr<Team>> *retT2 = teams.search(teamId2);
    if (retT1 == nullptr || retT2 == nullptr){
        return StatusType::FAILURE;
    }
    if (retT1->data->getNumPlayers() < 11 ||
        retT2->data->getNumPlayers() < 11 ||
        !(retT1->data->hasGuard()) ||
        !(retT2->data->hasGuard())){
        return StatusType::FAILURE;
    }
    int calc1 = retT1->data->getTotalGoals() - retT1->data->getTotalCards() + retT1->data->getPoints();
    int calc2 = retT2->data->getTotalGoals() - retT2->data->getTotalCards() + retT2->data->getPoints();
    if(calc1 == calc2){
        retT1->data->setPoints(retT1->data->getPoints() + 1);
        retT2->data->setPoints(retT2->data->getPoints() + 1);
    }
    else if (calc1 < calc2){
        retT2->data->setPoints(retT2->data->getPoints() + 3);
    }
    else{
        retT1->data->setPoints(retT1->data->getPoints() + 3);
    }
    retT1->data->setNumGames(retT1->data->getNumGames() + 1);
    retT2->data->setNumGames(retT2->data->getNumGames() + 1);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Player>> *ret = playersByID.search(playerId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    shared_ptr<Player> p = ret->data;
    shared_ptr<Team> t = p->getTeam();
    return output_t<int>(p->getNumGames() + t->getNumGames());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<shared_ptr<Team>> *ret = teams.search(teamId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    return output_t<int>(ret->data->getPoints());
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{

}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    else if(teamId > 0){
        AVL<shared_ptr<Team>> *ret = teams.search(teamId);
        if(ret == nullptr) {
            return StatusType::FAILURE;
        }
        return output_t<int>(ret->data->getBestGoals()->getPlayerID());
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
        AVL<shared_ptr<Team>> *ret = teams.search(teamId);
        if(ret == nullptr) {
            return StatusType::FAILURE;
        }
        return output_t<int>(ret->data->getNumPlayers());
    }
    return output_t<int>(totalPlayers);
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{

}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{

}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    //ani
}

void world_cup_t::removeTeamPtrInPlayers(AVL<shared_ptr<Player>> * avlPlayersID) {
    if(avlPlayersID == nullptr){
        return;
    }
    avlPlayersID->data->eraseTeam();
    removeTeamPtrInPlayers(avlPlayersID->right);
    removeTeamPtrInPlayers(avlPlayersID->left);
}

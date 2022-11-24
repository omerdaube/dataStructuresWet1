#include "worldcup23a1.h"
world_cup_t::world_cup_t() : playersByID(), playersByGoals(), teams(), nonEmptyTeams(), playersByGoalsList(), totalPlayers(0), totalTeams(0), bestPlayer(nullptr)
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId <= 0 || points < 0) {
        return StatusType::INVALID_INPUT;
    }
    if(teams.search(teamId) != nullptr) {
        return StatusType::FAILURE;
    }
    Team newTeam = Team(teamId, points);
    teams.add(newTeam);
    totalTeams++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    AVL<Team> *ret = teams.search(teamId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    if(ret->data.isEmpty()){
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
        throw StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    bool check1 = false, check2 = false;
	if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AVL<Player> *ret = playersByID.search(playerId);
    if(ret == nullptr) {
        return StatusType::FAILURE;
    }
    Player p = ret->data;
    PointerPlayer* pp = p.getPlayerPointer();
    Team* t = p.getTeam();
    if(t->getNumPlayers() >= 11 && t->hasGaurd() == true) {
        check1 = true;
    }
    t->getAVL().remove(*pp);
    delete pp;
    totalPlayers -= 1;
    t->setTotalGoals(t->getTotalGoals() - p.getGoals());
    t->setTotalCards(t->getTotalCards() - p.getCards());
    t->setNumPlayers(t->getNumPlayers() - 1);
    if(p->getIsGaurd()) {
        t->setNumGuards(t->getNumGuards() - 1);
    }
    if(t->getNumPlayers() < 11 || t->hasGaurd() == false) {
        check2 = true;
    }
    if(check1 && check2){
        PointerTeam* pt = t->getNonEmpty()
        nonEmptyTeams.remove(pt);
        delete pt;
    }
    if(p == t->getBestGoals()) {
        t->setBestGoals(t->getAVL().getMostRight()->data->getPlayerP());
    }
    if(p == bestPlayer){
        bestPlayer = playersByGoals->getMostRight()->data->getPlayerP();
    }
    PointerPlayer* ppGoal = p->getPlayerInGoals();
    playersByGoals.remove(ppGoal);
    delete ppGoal;
    playersByID.remove(p);
    delete p;

}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}
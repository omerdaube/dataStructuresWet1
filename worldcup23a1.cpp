#include "worldcup23a1.h"
#include <memory>

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    AVL<Team>* = playerTeam;
    AVL<PointerPlayer>* teamPointerPlayer;
    if ((playerID <= 0) || (teamID <= 0) || (gamesPlayed < 0) || (goals < 0) ||
        (cards < 0) || ((gamesPlayed = 0) && ((goals > 0) || (cards > 0)))) {
        return StatusType::INVALID_INPUT;
    }
    playerTeam = teams.search(teamID);
    if (playersByID.search(playerID) || !playerTeam) {
        return StatusType::FAILURE;
    }
    try {
        Player *newPlayer = new Player(playerID, cards, goals, goalKeeper, gamesPlayed, playerTeam->getTeamID());
        playersByID.add(*newPlayer);
        teamPointerPlayer = new PointerPlayer(newPlayer);
        playerTeams->players->add(teamPointerPlayer);
        goalsPointerPlayer = new PointerPlayer(newPlayer);
        playersByGoals.add(goalsPointerPlayer);
        newPlayer->teamPlayer = teamPointerPlayer;
        newPlayer->gamesPlayed -= playerTeam->numGames;
        playerTeam->totalGoals += goals;
        playerTeam->totalCards += cards;
        if (goalKeeper) {
            playerTeam->numGaurds++;
        }
        playerTeam->numPlayers++;
        totalPlayers++;
        if (newPlayer->goals > playerTeam->bestGoals->goals) {
            playerTeam->bestGoals = newPlayer;
            if (newPlayer->goals > bestPlayer->goals) {
                bestPlayer = newPlayer;
            }
        }
        if ((playerTeam->numPlayers >= 11) && (playerTeam->numGuards > 0)) {
            nonEmptyTeams.add(new PointerTeam(playerTeam));
        }
    } catch(const std::exception& e) {
        throw StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
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


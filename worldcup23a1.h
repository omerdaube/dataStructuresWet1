// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef WORLDCUP23A1_H_
#define WORLDCUP23A1_H_

#include "wet1util.h"
#include "AVL.h"
#include "Team.h"
#include "Player.h"
#include <memory>
#include "DoublyLinkedList.h"
#include "TeamsByID.h"
#include "PlayersByID.h"
#include "PlayersByGoals.h"
using namespace std;

class world_cup_t {
private:
    AVL<shared_ptr<Player>, PlayersByID> avlPlayersByID;
    AVL<shared_ptr<Player>, PlayersByGoals> avlPlayersByGoals;
    AVL<shared_ptr<Team>, TeamsByID> teams;
    AVL<shared_ptr<Team>, TeamsByID> nonEmptyTeams;
    DoublyLinkedList<shared_ptr<Player>> playersByGoalsList;
    int totalPlayers;
    int totalTeams;
    shared_ptr<Player> bestPlayer;

    void deleteInnerTeams(AVL<shared_ptr<Team>, TeamsByID>*);
    void removeTeamPtrInPlayers(AVL<shared_ptr<Player>, PlayersByID>*);
    template <int teamPoints>
    void updatePlayerPointsAccordingToGroup(AVL<shared_ptr<Player>, PlayersByGoals>* players);

    void removeTeamPtrInPlayers(AVL<shared_ptr<Player>>*);
    AVL<shared_ptr<Player>> BetterTeamPlayer(AVL<shared_ptr<Player>> p1, AVL<shared_ptr<Player>> p2);

    void updateClosestPlayers(shared_ptr<Player> newPlayer);

public:
	// <DO-NOT-MODIFY> {
	
	world_cup_t();
	virtual ~world_cup_t();
	
	StatusType add_team(int teamId, int points);
	
	StatusType remove_team(int teamId);
	
	StatusType add_player(int playerId, int teamId, int gamesPlayed,
	                      int goals, int cards, bool goalKeeper);
	
	StatusType remove_player(int playerId);
	
	StatusType update_player_stats(int playerId, int gamesPlayed,
	                                int scoredGoals, int cardsReceived);
	
	StatusType play_match(int teamId1, int teamId2);
	
	output_t<int> get_num_played_games(int playerId);
	
	output_t<int> get_team_points(int teamId);
	
	StatusType unite_teams(int teamId1, int teamId2, int newTeamId);
	
	output_t<int> get_top_scorer(int teamId);
	
	output_t<int> get_all_players_count(int teamId);
	
	StatusType get_all_players(int teamId, int *const output);
	
	output_t<int> get_closest_player(int playerId, int teamId);
	
	output_t<int> knockout_winner(int minTeamId, int maxTeamId);
	
	// } </DO-NOT-MODIFY>
};


#endif // WORLDCUP23A1_H_

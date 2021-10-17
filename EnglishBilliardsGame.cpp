
#include "EnglishBilliardsGame.h"


/*
 * Default English Billiards Game constructor.
 */
EnglishBilliardsGame::EnglishBilliardsGame()
{
	player1 = new Player(true);
    player2 = new Player(false);
	frameTimer.start_timer();
	
}


/*
 * Default English Billiards Game destructor.
 */
EnglishBilliardsGame::~EnglishBilliardsGame()
{

}


/**
 * Returns the players scores in an array where the
 *  first integer is player 1 and the second is
 *  player 2
 */
void EnglishBilliardsGame::get_player_scores(int* scores)
{
    *scores = player1->get_score();
    *(scores + 1) = player2->get_score();
}


/**
 * Returns the players breaks in an array where the
 *  first integer is player 1 and the second is
 *  player 2
 */
void EnglishBilliardsGame::get_player_breaks(int* breaks)
{
    *breaks = player1->get_current_break();
    *(breaks + 1) = player2->get_current_break();
}


/**
 * Receives point input from the user and determines how to add the
 *  point value to a player if the input is valid for the state.
 */
void EnglishBilliardsGame::receive_point_input(int points)
{
	game_state_changed();
	Player* playerAtTable = player_at_table();
	playerAtTable->ball_potted(points);
}


/*
 * Indicates that the player at the table has fouled.
 */
void EnglishBilliardsGame::foul_occurred()
{
	game_state_changed();
	add_foul_points(2);
}


/*
 * Add foul points to the player not at the table and end the break
 *  of the player at the table.
 */
void EnglishBilliardsGame::add_foul_points(int points)
{
	Player* playerNotAtTable = player_not_at_table();
	
	playerNotAtTable->add_points(points);
	end_break();
}


/**
 * This function awards a frame to the player with the
 *  highest score and resets for the next frame
 */
void EnglishBilliardsGame::end_frame()
{
    int scores[2];
    get_player_scores(scores);
    
    game_state_changed();
    
    if(scores[0] > scores[1])
    {
        player1->won_frame();
        player2->lost_frame();
    }
    else
    {
        player2->won_frame();
        player1->lost_frame();
    }
    
	frameTimer.reset_timer();
	player1->set_at_table(true);
	player2->set_at_table(false);
}


/**
 * This function ends the break of the player at the
 *  table and begins the next players break
 */
void EnglishBilliardsGame::end_break()
{
	Player* playerAtTable = player_at_table();
	Player* playerNotAtTable = player_not_at_table();
	
	game_state_changed();
	
	playerAtTable->end_break();
	playerNotAtTable->begin_break();
}


/**
 * Gets the player at the table and returns a 1 for player
 *  1 and a 2 for player 2.
 */
int EnglishBilliardsGame::shooting_player()
{
    if(player1->get_at_table()){
        return 1;
    } else {
        return 2;
    }
}


/**
 * Private helper method to get player at table.
 */
Player* EnglishBilliardsGame::player_at_table()
{
    if(player1->get_at_table()){
		return player1;
    } else {
        return player2;
    }
}


/**
 * Private helper method to get player not at table.
 */
Player* EnglishBilliardsGame::player_not_at_table()
{
    if(player1->get_at_table()){
        return player2;
    } else {
        return player1;
    }
}


/**
 * Private helper method to create a snapshot of the current game state
 *  when a change is requested and add it to the snooker game state stack.
 */
void EnglishBilliardsGame::game_state_changed()
{
    GameState currentState;
    currentState.p1Points = player1->get_score();
    currentState.p2Points = player2->get_score();
    currentState.p1CurrentBreak = player1->get_current_break();
    currentState.p2CurrentBreak = player2->get_current_break();
    currentState.p1HighBreak = player1->get_high_break();
    currentState.p2HighBreak = player2->get_high_break();
    currentState.p1FramesWon = player1->get_frames_won();
    currentState.p2FramesWon = player2->get_frames_won();
    currentState.shootingPlayer = shooting_player();

    stateStack.add_game_state(currentState);
}


/**
 * Revert snooker game to last save state in stack.
 */
void EnglishBilliardsGame::revert_game_state()
{
    GameState* revertState = stateStack.previous_game_state();
    
    if(revertState != 0){
		player1->set_score(revertState->p1Points);
		player2->set_score(revertState->p2Points);
		player1->set_current_break(revertState->p1CurrentBreak);
		player2->set_current_break(revertState->p2CurrentBreak);
		player1->set_high_break(revertState->p1HighBreak);
		player2->set_high_break(revertState->p2HighBreak);
		player1->set_frames_won(revertState->p1FramesWon);
		player2->set_frames_won(revertState->p2FramesWon);
	
		if(revertState->shootingPlayer == 1){
			player1->set_at_table(true);
			player2->set_at_table(false);
		} else {
			player2->set_at_table(true);
			player1->set_at_table(false);
		}
    }
}


/*
 * Returns the current frame timer.
 */
void EnglishBilliardsGame::get_game_time(int *time)
{
	frameTimer.get_time(time);
}


/*
 * Stop the game and cleanup resources.
 */
void EnglishBilliardsGame::stop_game()
{
	frameTimer.stop_timer();
}

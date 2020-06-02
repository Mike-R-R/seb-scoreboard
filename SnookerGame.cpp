
#include "SnookerGame.h"


/**
 * Default constructor for a game of snooker
 */
SnookerGame::SnookerGame()
{
    player1 = new Player(true);
    player2 = new Player(false);
    reds = 15;
    pointsOnTable = 147;
    freeBall = false;
    foul = false;
}

/**
 * Constructor for a game of snooker where p1 and p2 are
 *  true if the player is breaking and false if not.
 */
SnookerGame::SnookerGame(bool p1, bool p2)
{
    player1 = new Player(p1);
    player2 = new Player(p2);
    reds = 15;
    pointsOnTable = 147;
    freeBall = false;
    foul = false;
}

/**
 * Default destructor
 */
SnookerGame::~SnookerGame()
{

}

/**
 * Copy assignment for a game of snooker
 */
SnookerGame& SnookerGame::operator= (const SnookerGame& g)
{
    this->player1 = g.player1;
    this->player2 = g.player2;
    this->reds = g.reds;
    this->freeBall = g.freeBall;
    return *this;
}


int SnookerGame::remaining_reds()
{
    return reds;
}


int SnookerGame::remaining_points()
{
    return pointsOnTable;
}

/**
 * Returns the players scores in an array where the
 *  first integer is player 1 and the second is
 *  player 2
 */
void SnookerGame::get_player_scores(int* scores)
{
    *scores = player1->get_score();
    *(scores + 1) = player2->get_score();
}


/**
 * Returns the players breaks in an array where the
 *  first integer is player 1 and the second is
 *  player 2
 */
void SnookerGame::get_player_breaks(int* breaks)
{
    *breaks = player1->get_current_break();
    *(breaks + 1) = player2->get_current_break();
}


/**
 * Returns the difference in points between the two
 *  players where a positive result indicates player
 *  1 is winning and a negative indicates player
 *  2 is in the lead.
 */
int SnookerGame::point_spread()
{
    int scores[2];
    get_player_scores(scores);
    
    return scores[0] - scores[1];
}


/**
 * Receives point input from the user and determines how to add the
 *  point value to a player if the input is valid for the state.
 */
void SnookerGame::receive_point_input(int points)
{
    Player* playerAtTable = player_at_table();
    bool color_shot_valid = false;
    
    if(freeBall){
	if(points > 1){
	    game_state_changed();
	    playerAtTable->ball_potted(points);
	    playerAtTable->set_on_red(true);
	    freeBall = false;
	}
    } else if(foul){
	game_state_changed();
	if(points < 4){
	    add_foul_points(4);
	} else {
	    add_foul_points(points);
	}
    } else {
	// Check if red ball potted
	if(points == 1){
	    if(reds > 0){
		game_state_changed();
		playerAtTable->ball_potted(points);
		
		// Adjust score and target ball when multiple reds potted together
		if(playerAtTable->get_on_red()){
		    pointsOnTable -= 7;
		    playerAtTable->set_on_red(false);
		}
		
		reds--;
		pointsOnTable -= 1;
	    }
	} else {
	    //Check if color ball potted
	    switch(points){
		    case 2:
			    if(pointsOnTable == 27){
				    color_shot_valid = true;
			    }
			    break;
		    case 3:
			    if(pointsOnTable == 25){
				    color_shot_valid = true;
			    }
			    break;
		    case 4:
			    if(pointsOnTable == 22){
				    color_shot_valid = true;
			    }
			    break;
		    case 5:
			    if(pointsOnTable == 18){
				    color_shot_valid = true;
			    }
			    break;
		    case 6:
			    if(pointsOnTable == 13){
				    color_shot_valid = true;
			    }
			    break;
		    case 7:
			    if(pointsOnTable == 7){
				    color_shot_valid = true;
			    }
			    break;
	    }
	    
	    // Player is shooting color after potting a red
	    if(!playerAtTable->get_on_red() && pointsOnTable > 27){
		color_shot_valid = true;
	    }
	    
	    if (color_shot_valid){
		game_state_changed();
		playerAtTable->ball_potted(points);
		
		// Set points on table and onRed value when only colors remain on the table.
		if(pointsOnTable <= 27){
		    playerAtTable->set_on_red(false);
		    pointsOnTable -= points;
		} else {
		    pointsOnTable -= 7;
		}
	    }
	}
    }
}


/*
 * Gets the foul status of the shooting player
 */
bool SnookerGame::player_fouled()
{
    return foul;
}


/*
 * Indicates that the player at the table has fouled.
 */
void SnookerGame::foul_occurred()
{
    if(pointsOnTable != 0){
	game_state_changed();
	foul = true;
    }
}


/*
 * Add foul points to the player not at the table and end the break
 *  of the player at the table.
 */
void SnookerGame::add_foul_points(int points)
{
	Player* playerNotAtTable = player_not_at_table();
	
	playerNotAtTable->add_points(points);
	end_break();
	foul = false;
}


/**
 * Shooting player made a free ball
 */
void SnookerGame::free_ball()
{
    Player* playerAtTable = player_at_table();

    if(!freeBall && pointsOnTable != 0){
	game_state_changed();
	playerAtTable->add_points(1);
	playerAtTable->set_on_red(false);
	freeBall = true;
    }
}


/**
 * This function awards a frame to the player with the
 *  highest score and resets for the next frame
 */
void SnookerGame::end_frame()
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
    
    reds = 15;
    pointsOnTable = 147;
}


/**
 * This function ends the break of the player at the
 *  table and begins the next players break
 */
void SnookerGame::end_break()
{
	Player* playerAtTable = player_at_table();
	Player* playerNotAtTable = player_not_at_table();
	
	if(!foul){
	    game_state_changed();
	}
	
	if(!player_shooting_red() && !freeBall && pointsOnTable > 27){
		pointsOnTable -= 7;
	}
	
	playerAtTable->end_break();
	playerNotAtTable->begin_break();
}


/**
 * This function accounts for a red lost during the
 *  course of play
 */
void SnookerGame::lost_red()
{
    if(reds != 0){
	game_state_changed();
	reds--;
	pointsOnTable -= 8;
    }
}


/**
 * Gets the player at the table and returns a 1 for player
 *  1 and a 2 for player 2.
 */
int SnookerGame::shooting_player()
{
    if(player1->get_at_table())
    {
        return 1;
    }
    else
    {
        return 2;
    }
}


bool SnookerGame::player_shooting_red()
{
    return player_at_table()->get_on_red();
}


/**
 * Private helper method to get player at table.
 */
Player* SnookerGame::player_at_table()
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
Player* SnookerGame::player_not_at_table()
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
void SnookerGame::game_state_changed()
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
    currentState.pointsOnTable = pointsOnTable;
    currentState.reds = reds;
    currentState.shootingPlayer = shooting_player();
    currentState.onRed = player_shooting_red();
    currentState.foul = foul;
    currentState.freeBall = freeBall;

    stateStack.add_game_state(currentState);
}


/**
 * Revert snooker game to last save state in stack.
 */
void SnookerGame::revert_game_state()
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
	pointsOnTable = revertState->pointsOnTable;
	reds = revertState->reds;
	
	if(revertState->shootingPlayer == 1){
	    player1->set_at_table(true);
	    player1->set_on_red(revertState->onRed);
	    player2->set_at_table(false);
	    player2->set_on_red(!revertState->onRed);
	} else {
	    player2->set_at_table(true);
	    player2->set_on_red(revertState->onRed);
	    player1->set_at_table(false);
	    player1->set_on_red(!revertState->onRed);
	}
	
	foul = revertState->foul;
	freeBall = revertState->freeBall;
    }
    
}



#include "Player.h"

/**
 * Default constructor for Player class
 */
Player::Player()
{
    score = 0;
    currentBreak = 0;
    highBreak = 0;
    framesWon = 0;
    onRed = true;
    atTable = false;
}


/**
 * Constructor for Player where breaking sets
 *  if the Player is currently at the table
 */
Player::Player(bool breaking)
{
    score = 0;
    currentBreak = 0;
    highBreak = 0;
    framesWon = 0;
    onRed = true;
    atTable = breaking;
}


/**
 * Default destructor for Player
 */
Player::~Player()
{

}


/**
 * Returns Player score
 */
int Player::get_score()
{
    return score;
}


/**
 * Sets Player score
 */
void Player::set_score(int score)
{
    this->score = score;
}


/**
 * Returns frames won by Player
 */
int Player::get_frames_won()
{
    return framesWon;
}


/**
 * Sets frames won by Player
 */
void Player::set_frames_won(int framesWon)
{
    this->framesWon = framesWon;
}


/**
 * Returns the players current break
 */
int Player::get_current_break()
{
    return currentBreak;
}


/**
 * Sets the players current break
 */
void Player::set_current_break(int currentBreak)
{
    this->currentBreak = currentBreak;
}


/*
 * Returns Players highest break
 */
int Player::get_high_break()
{
    return highBreak;
}


/*
 * Sets Players highest break
 */
void Player::set_high_break(int highBreak)
{
    this->highBreak = highBreak;
}


/**
 * Returns whether the player is shooting a red or color
 */
bool Player::get_on_red()
{
    return onRed;
}


/**
 * Set whether the player is shooting a red or color
 */
void Player::set_on_red(bool red)
{
    onRed = red;
}


/**
 * Returns boolean representing whether the Player
 *  is currently at the table
 */
bool Player::get_at_table()
{
    return atTable;
}


/**
 * Sets boolean representing whether the Player
 *  is currently at the table
 */
void Player::set_at_table(bool atTable)
{
    this->atTable = atTable;
}


/**
 * Player potted a ball.
 */
void Player::ball_potted(int points)
{
    add_points(points);
    onRed = !onRed;
}


/**
 * Ends the Players current break
 */
void Player::end_break()
{
    atTable = false;
    if(currentBreak > highBreak)
        highBreak = currentBreak;
    currentBreak = 0;
}


/**
 * Begins the Players break
 */
void Player::begin_break()
{
    atTable = true;
    onRed = true;
}


/**
 * This function adds a won frame to Player
 *  and resets Player for next frame
 */
void Player::won_frame()
{
    framesWon++;
    score = 0;
    currentBreak = 0;
    highBreak = 0;
    onRed = true;
}


/**
 * This function resets player for next frame
 */
void Player::lost_frame()
{
    score = 0;
    currentBreak = 0;
    highBreak = 0;
    onRed = true;
}


/**
 * Adds input integer points to players score
 */
void Player::add_points(int points)
{
    score += points;
    currentBreak += points;
}


#ifndef EB_GAME
#define EB_GAME

#include "Player.h"

class EnglighBilliardsGame {
	public:
		EnglighBilliardsGame();
		~EnglighBilliardsGame();
		void get_player_scores(int *);
		void get_player_breaks(int *);
		void receive_point_intput(int);
		bool player_fouled();
		void add_foul_points(int);
		void end_frame();
		int shooting_player();
		bool revert_game_state();
		
	private:
		Player* player1;
		Player* player2;
		bool foul;

}
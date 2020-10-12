
#ifndef EB_GAME
#define EB_GAME

#include "Player.h"
#include "SnookerStack.h"
#include "Timer.h"

class EnglishBilliardsGame {
	public:
		EnglishBilliardsGame();
		~EnglishBilliardsGame();
		void get_player_scores(int *);
		void get_player_breaks(int *);
		void receive_point_input(int);
		bool player_fouled();
		void foul_occurred();
		void add_foul_points(int);
		void end_frame();
		void end_break();
		int shooting_player();
		void revert_game_state();
		void get_game_time(int *);
		void stop_game();
		
	private:
		Player* player1;
		Player* player2;
		Timer frameTimer;
		SnookerStack stateStack;

		Player* player_at_table();
		Player* player_not_at_table();
		void game_state_changed();
};

#endif
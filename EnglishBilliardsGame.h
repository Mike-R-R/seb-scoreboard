
#ifndef EB_GAME
#define EB_GAME

#include "Player.h"
#include "SnookerStack.h"

struct Timer{
	int hours;
	int minutes;
	int seconds;
};

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
		
	private:
		Player* player1;
		Player* player2;
		bool foul;
		bool timerRunning;
		Timer frameTimer;
		SnookerStack stateStack;

		void game_state_changed();
};

#endif
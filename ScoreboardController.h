
#ifndef SCOREBOARD_CONTROLLER
#define SCOREBOARD_CONTROLLER

#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"
#include "pixel-mapper.h"
#include "graphics.h"
#include "SnookerGame.h"
#include "EnglishBilliardsGame.h"

#include <curses.h>

class ScoreboardController : public rgb_matrix::ThreadedCanvasManipulator{
	public:
		ScoreboardController(rgb_matrix::Canvas *m);
		~ScoreboardController();
		
		void Run();
		void stop_game();
		bool running();
	
	private:
		bool game_running;
		SnookerGame* snookerGame;
		EnglishBilliardsGame* englishBilliardsGame;
		
		/** Represents the current game state.
		  *  0 = Game selection
		  *  1 = Snooker
		  *  2 = English Billiards
		  */
		int gameState;
		
		void game_selection_input(int);
		void snooker_input(int);
		void english_billiards_input(int);
		void draw_game_selection_screen();
		void draw_snooker_scoreboard();
		void draw_english_billiards_scoreboard();
		void draw_number(int,int,int,int,int,int);
		void player_shooting(int, bool);
		void draw_shooting_indicator(int,bool);
		void draw_foul_indicator(int);
		void update_board();
		void clear_board();
		void populate_snooker_board();
		void populate_english_billiards_board();
		void draw_left_aligned(int,int,int,int,int,int);
		void draw_right_aligned(int,int,int,int,int,int);
		void draw_left_inverted(int);
		void draw_right_inverted(int);
		bool check_for_input(char *c);
	
};

#endif

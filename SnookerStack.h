
#ifndef SNOOKER_QUEUE
#define SNOOKER_QUEUE

#include <stack>

struct GameState{
	int p1Points;
	int p2Points;
	int p1CurrentBreak;
	int p2CurrentBreak;
	int p1HighBreak;
	int p2HighBreak;
	int p1FramesWon;
	int p2FramesWon;
	int pointsOnTable;
	int reds;
	int shootingPlayer;
	bool onRed;
	bool foul;
	bool freeBall;
};

class SnookerStack{
	public:
		SnookerStack();
		~SnookerStack();
		void add_game_state(GameState);
		void add_game_state(int,int,int,int,int,int,int,int,int,int,int,bool,bool,bool);
		GameState* previous_game_state();
	
	private:
		std::stack<GameState> gameStack;

};

#endif

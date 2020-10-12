
#ifndef TIMER
#define TIMER

#include <iostream>
#include <thread>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <atomic>

class Timer{
	public:
		Timer();
		~Timer();
		void start_timer();
		void stop_timer();
		void reset_timer();
		void get_time(int *);
		bool get_timer_running();

	private:
		volatile std::atomic<bool> timerRunning(false);
		int hours;
		int minutes;
		int seconds;
		
		void timer_loop();
};

#endif

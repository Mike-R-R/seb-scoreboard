
#include "Timer.h"


Timer::Timer()
{
	hours = 0;
	minutes = 0;
	seconds = 0;
}


Timer::~Timer()
{
	timer_running = false;
}


void Timer::start_timer()
{
	timer_running = true;
	std::thread timer(&Timer::timer_loop, this);
	timer.detach();
}


void Timer::stop_timer()
{
	timer_running = false;
}


void Timer::reset_timer()
{
	hours = 0;
	minutes = 0;
	seconds = 0;
}


void Timer::get_time(int *time)
{
	*time = hours;
	*(time + 1) = minutes;
	*(time + 2) = seconds;
}


bool Timer::get_timer_running()
{
	return timer_running;
}


void Timer::timer_loop(){
    while(timerRunning){

		if(seconds >= 60){
			seconds = 0;
			minutes = minutes + 1;
		}

		if(minutes >= 60){
			minutes = 0;
			hours = hours + 1;
		}
		
		if(hours > 9){
			hours = 0;
			minutes = 0;
			seconds = 0;
		}

		sleep(1);
		seconds += 1;
	}
}

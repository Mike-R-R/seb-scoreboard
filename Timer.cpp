
#include "Timer.h"


Timer::Timer()
{
	timer_running = false;
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
	//std::clock_t start = std::clock();
	
    while(timer_running){
		//std::cout << "Seconds: " << (std::clock() - start) << std::endl;
		//seconds = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

		if(seconds >= 60){
			seconds = 0;
			//start = std::clock();
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

		//std::cout << "Current thread time is " << hours << ":" << minutes << ":" << seconds << std::endl;
		//usleep(100000);
		sleep(1);
		seconds += 1;
	}

	std::cout << "Timer stopped! Exiting detached thread!" << std::endl;
}

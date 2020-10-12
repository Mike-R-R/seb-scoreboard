
#include "Timer.h"

/*
 * Default timer constructor.
 */
Timer::Timer()
{
	timerRunning = false;
	hours = 0;
	minutes = 0;
	seconds = 0;
}


/*
 * Default timer destructor.
 */
Timer::~Timer()
{
	timerRunning = false;
}


/*
 * Creates and detaches a new timer thread.
 */
void Timer::start_timer()
{
	timerRunning = true;
	std::thread timer(&Timer::timer_loop, this);
	timer.detach();
}


/*
 * Sets the atomic boolean variable to false to indicate
 *  to the detached thread that is should stop running.
 */
void Timer::stop_timer()
{
	timerRunning = false;
}


/*
 * Resets timer to default state.
 */
void Timer::reset_timer()
{
	hours = 0;
	minutes = 0;
	seconds = 0;
}


/*
 * Returns the current timer time in an array.
 */
void Timer::get_time(int *time)
{
	*time = hours;
	*(time + 1) = minutes;
	*(time + 2) = seconds;
}


/*
 * Return the current status of the atomic bool indicating
 *  if the detached thread is currently running.
 */
bool Timer::get_timer_running()
{
	return timerRunning;
}


/*
 * This function is run in a detached thread which continues
 *  counting until the atomic bool timerRunning is set to false.
 */
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

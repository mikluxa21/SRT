#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#define TOP  0
#define BOTTOM  1
#define THIS_FLOOR  2

#define UP  48
#define DOWN  49

int state = THIS_FLOOR;

void move(int newState)
{
	usleep(1000000);
}


void liftControl(int signo)
{
	std::cout <<signo << std::endl;
	switch(state){
		case (THIS_FLOOR):
			std::cout << THIS_FLOOR<< std::endl;
			break;
		case (TOP):
			std::cout << TOP << std::endl;
			break;
		case (BOTTOM):
			std::cout << BOTTOM << std::endl;
			break;
	}
} 

int main()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	struct sigaction act;
	act.sa_handler = &liftControl;
	act.sa_flags = 0;
	act.sa_mask = set;
	sigaction(SIGINT, &act, NULL);
	raise(BOTTOM);
	return 0;
}



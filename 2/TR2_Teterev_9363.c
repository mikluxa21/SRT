#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#define TOP
#define BOTTOM
#define THIS_FLOOR

#define UP
#define DOWN 

int state = THIS_FLOOR;

void move(int newState)
{
	usleep(1000000);
}


void liftControl(int signo, siginfo_t* info, void* nk)
{
	switch(state){
		case(THIS_FLOOR):
			if(signo == UP){
				
			}
			break;
		case(TOP):
			
			break;
		case(BOTTOM):
			
			break;
	}
} 

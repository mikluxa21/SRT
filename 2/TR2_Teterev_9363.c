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
	state = newState;
}


void liftControl(int signo, siginfo_t* info, void* context)
{
	int val = info->si_value.sival_int;
	switch(state){
		case (THIS_FLOOR):
			if(val = UP)
				move(TOP);
			if(val == DOWN)
				move(BOTTOM);
			break;
		case (TOP):
			if(val = UP)
				std::cout << "Error: state = TOP" << std::endl;
			if(val == DOWN)
				move(THIS_FLOOR);
			break;
		case (BOTTOM):
			if(val = UP)
				move(THIS_FLOOR);
			if(val == DOWN)
				std::cout << "Error: state = BOTTOM" << std::endl;
			break;
	}
}

void* push_buttom(void* args)
{
	char ch;
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = liftControl;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	union sigval val;
	while(ch != 'q')
	{
		std::cout << "Old state = " << state << std::endl;
		std::cin >> ch;
		switch(ch)
		{
			case 'u':
				val.sival_int = UP;
				sigqueue(getpid(), SIGUSR1, val);
				break;
			case 'd':
				val.sival_int = DOWN;
				sigqueue(getpid(), SIGUSR1, val);
				break;
			case 'q':
				break;
			default:
				std::cout << "u - up\nd - dowm\nq - end\n";
				break;
		}
		std::cout << "State after command = " << state << std::endl << std::endl;
	}
	return EXIT_SUCCESS;
	
}

int main()
{
	std::cout << "Start" <<  std::endl;
	pthread_t t;
	pthread_create(&t, NULL, &push_buttom, NULL);
	pthread_join(t, NULL);
	std::cout << "Finish" << std::endl;
	return 0;
}



#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>


void doControl()
{	
	srand(time(NULL));
	int x = 1;
	useconds_t t = 500000 + rand()%100000;
	std::cout << "####### " << t << std::endl;
	x = rand()%2;
	if(!x) while(1);
	usleep(t);
}

void deadlineHeandler()
{
	std::cout << "#### Deadline exceeded ####" << std::endl;
}


void alarmHeandler(int signal)
{
	std::cout << "##-- Restart requered --##" << std::endl;
	kill(getppid(), SIGUSR1);
	
}


int main()
{
	clock_t start, end;
	double time_used;
	while(1)
	{
		signal(SIGALRM, alarmHeandler);
		alarm(3);
		start = clock();
		doControl();
		end = clock();
		time_used = (double) (end - start)/CLOCKS_PER_SEC;
		std::cout << time_used*1000.0 << std::endl;
		if(time_used*1000.0 > 0.04) deadlineHeandler();
		alarm(0);
		usleep(3);
	}
	return 0;
}

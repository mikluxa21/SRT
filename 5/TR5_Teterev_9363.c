#include <pthread.h>
#include <unistd.h>
#include <iostream>

pthread_mutex_t mutex;
pthread_cond_t cond, cond2;

void* Cont(void* args)
{
	while(true)
	{
		std::cout << "container " << pthread_self() << " wait" << std::endl;
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		std::cout << "container " << pthread_self() << " unloads" << std::endl; 
		sleep(1);
		std::cout << "container " << pthread_self() << " unloaded" << std::endl; 
		//pthread_cond_signal(&cond2);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	};
	return EXIT_SUCCESS;
}

void* dispetcher(void* args)
{
	while(true)
	{
		//pthread_cond_wait(&cond2, &mutex);
		pthread_mutex_lock(&mutex);
		std::cout << "dispetcher in" << std::endl;
		sleep(1);
		std::cout << "dispetcher out" << std::endl;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(3);
	};
	return EXIT_SUCCESS;
}



int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_cond_init(&cond2, NULL);
	std::cout << "for stop this programm press any key" << std::endl;
	pthread_t thread_con[3], thread_disp;
	pthread_create(&thread_disp, NULL, &dispetcher, NULL);
	for(size_t i = 0; i < 3; i++)
		pthread_create(&thread_con[i], NULL, &Cont, NULL);
	
	getchar();
	pthread_cancel(thread_disp);
	for(auto i: thread_con)
		pthread_cancel(i);
	return EXIT_SUCCESS;
}

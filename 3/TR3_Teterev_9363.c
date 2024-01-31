#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>

int Buffer = 0;
const int maxBuf = 10;
sem_t sem;

void* Consumer(void* args)
{
	while(true)
	{
		sem_wait(&sem);
		if(Buffer > 0)
		{
			Buffer--;
			std::cout << "Cons: Buf = " << Buffer << std::endl;
		}
		else 
		{
			std::cout << "Cons: Buffer is empty" << std::endl;
		}
		sem_post(&sem);
		sleep(2);
	};
	return EXIT_SUCCESS;
}

void* Supplier(void* args)
{
	while(true)
	{
		sem_wait(&sem);
		if(Buffer < 10)
		{	
			Buffer++;
			std::cout << "Sup: Buf = " << Buffer << std::endl;
		}
		else 
		{
			std::cout << "Sup: Buffer is full" << std::endl;
		}
		sem_post(&sem);
		sleep(1);
	};
	return EXIT_SUCCESS;
}

int main()
{
	sem_init(&sem, 0, 1);
	pthread_t thread_Cons, thread_Sup;
	pthread_create(&thread_Cons, NULL, &Consumer, NULL);
	pthread_create(&thread_Sup, NULL, &Supplier, NULL);
	pthread_join(thread_Cons, NULL);
	pthread_join(thread_Sup, NULL);
	sem_destroy(&sem);
	return EXIT_SUCCESS;
}

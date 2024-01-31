#include <pthread.h>
#include <unistd.h>
#include <iostream>

int Buffer = 0;
const int maxBuf = 10;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* Consumer(void* args)
{
	while(true)
	{
		pthread_mutex_lock(&mutex);
		if(Buffer)
			pthread_cond_wait(&cond, &mutex);
		if(Buffer > 0)
		{
			Buffer--;
			std::cout << "Cons: Buf = " << Buffer << std::endl;
		}
		else 
		{
			std::cout << "Cons: Buffer is empty" << std::endl;
		}
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	};
	return EXIT_SUCCESS;
}

void* Supplier(void* args)
{
	while(true)
	{
		pthread_mutex_lock(&mutex);
		if(Buffer < 10)
		{	
			Buffer++;
			std::cout << "Sup: Buf = " << Buffer << std::endl;
		}
		else 
		{
			std::cout << "Sup: Buffer is full" << std::endl;
		}
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(1);
	};
	return EXIT_SUCCESS;
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_t thread_Cons, thread_Sup;
	pthread_create(&thread_Cons, NULL, &Consumer, NULL);
	pthread_create(&thread_Sup, NULL, &Supplier, NULL);
	pthread_join(thread_Cons, NULL);
	pthread_join(thread_Sup, NULL);
	return EXIT_SUCCESS;
}

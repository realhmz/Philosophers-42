#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int i = 0;
pthread_mutex_t mutex;


void* print_it()
{
	int j = 0;
	// pthread_mutex_lock(&mutex);
	while (j < 100000000)
	{
		j++;
		i++;
	}
	// pthread_mutex_unlock(&mutex);
	printf("%d\n",i);
}

int main()
{
	pthread_t t1; 
	pthread_t t2;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&t1,NULL,&print_it,NULL);
	pthread_create(&t2,NULL,&print_it,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

}
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// int i = 0;
// pthread_mutex_t mutex;

// static int j = 0;
// void* print_it()
// {
// 	int i  = 0;
// 	pthread_mutex_lock(&mutex);
// 	while (i < 50)
// 	{
// 		usleep(50000);
// 		printf("yam eatin  %d\n", j);
// 		i++;
// 	}
// 	j++;
// 	pthread_mutex_unlock(&mutex);
// 	printf("%d\n",i);
// }

// int main()
// {
// 	pthread_t t1; 
// 	pthread_t t2;
// 	pthread_mutex_init(&mutex,NULL);
// 	pthread_create(&t1,NULL,&print_it,NULL);
// 	pthread_create(&t2,NULL,&print_it,NULL);
// 	// while (1) ;
	
// 	// pthread_detach(t1);
// 	// pthread_detach(t2);
// 	// pthread_join(t1,NULL);
// 	// pthread_join(t2,NULL);

// }
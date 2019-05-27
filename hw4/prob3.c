#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

#define N 100
void* runner();
int inside, total, times = 10000000/N;
pthread_mutex_t mutex;

int main(){
  
	pthread_mutex_init(&mutex, NULL);
	pthread_t tid[N];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	for(int i = 0; i<N; i++){
		pthread_create(tid+i, &attr, runner, NULL);
	}
	for(int i = 0; i<N; i++){
		pthread_join(tid[i], NULL);
	}
	printf("pi = %f\n", (double)inside/total*4);
	return 0;
}

void* runner(){
	srand(time(NULL));
	for(int i = 0; i<times; i++){
		double x = (double) rand()/RAND_MAX;
		double y = (double) rand()/RAND_MAX;
		pthread_mutex_lock(&mutex);
		if (x*x+y*y <=1) inside++;
		total++;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

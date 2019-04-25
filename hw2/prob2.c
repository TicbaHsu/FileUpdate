#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

void* runner();
int inside, total, times = 100000000;

int main(){
  
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, NULL);
	pthread_join(tid, NULL);
	printf("pi = %f\n", (double)inside/total*4);
	return 0;
}

void* runner(){
	srand(time(NULL));
	for(int i = 0; i<times; i++){
		double x = (double) rand()/RAND_MAX;
		double y = (double) rand()/RAND_MAX;
		if (x*x+y*y <=1) inside++;
		total++;
	}
	pthread_exit(0);
}

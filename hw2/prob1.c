#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

float avg = 0.0;
int min = 0, max = 0;
void *worker1(void *param);
void *worker2(void *param);
void *worker3(void *param);

typedef struct Nums{
	int size;
	int *num;
}Nums;

int main(){
	int num[1000], i = 0;
	while(i < 1000 && scanf("%d", &num[i])>0) i++;
	Nums nums;
	nums.size = i;
	nums.num = num;
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, worker1, &nums);
	pthread_create(&tid2, &attr, worker2, &nums);
	pthread_create(&tid3, &attr, worker3, &nums);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

	printf("The average value is %f\n", avg);
	printf("The minimum value is %d\n", min);
	printf("The maximum value is %d\n", max);
	return 0;
}

void *worker1(void *param){
	Nums *nums = (Nums*)param;
	int *num = nums->num;
	int size = nums->size;
	for(int i = 0; i<size; i++){
		avg += num[i];
	}
	avg = avg/size;
	pthread_exit(0);
}
void *worker2(void *param){
	Nums *nums = (Nums*)param;
	int *num = nums->num;
	int size = nums->size;
	for(int i = 0; i<size; i++){
		if(i == 0) min = num[i];
		else{
			if(min > num[i]) min = num[i];
		}
	}
	pthread_exit(0);
}
void *worker3(void *param){
	Nums *nums = (Nums*)param;
	int *num = nums->num;
	int size = nums->size;
	for(int i = 0; i<size; i++){
		if(i == 0) max = num[i];
		else{
			if(max < num[i]) max = num[i];
		}
	}
	pthread_exit(0);
}

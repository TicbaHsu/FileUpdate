#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	if (argc > 2) exit(1);
	int num = atoi(argv[1]);
	if (num <= 0) fprintf(stderr, "input number is smaller than 1");

	pid_t pid;

	pid = fork();
	if(pid<0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if (pid == 0){
		printf("%d, ", num);
		while(num > 2){
			if(num%2== 0) num /= 2;
			else num = num*3+1;
			printf("%d, ", num);
		}
		printf("1\n");
	}
	else{
		wait(NULL);
	}
	return 0;
}

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>

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
		int shm_fd;
		char str[64];
		void *ptr;
		shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
		ftruncate(shm_fd, 4096);
		ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

		sprintf(str, "%d, ", num);
		sprintf(ptr, "%s", str);
		ptr += strlen(str);
		while(num > 2){
			if(num%2== 0) num /= 2;
			else num = num*3+1;
			sprintf(str, "%d, ", num);
			sprintf(ptr, "%s", str);
			ptr += strlen(str);
		}
		sprintf(str, "1\n");
		sprintf(ptr, "%s", str);
		ptr += strlen(str);
	}
	else{
		wait(NULL);
		int shm_fd;
		void *ptr;
		shm_fd = shm_open("OS", O_RDONLY, 0666);
		ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);
		printf("%s", (char*) ptr);
		shm_unlink("OS");
	}
	return 0;
}

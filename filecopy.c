#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[]){
	char p_buffer[100];
	char c_buffer[100];
	int fd[2], des, bytes, target;

	pipe(fd);

	pid_t pid = fork();
	if(pid > 0){
		close(fd[0]);

		des = open(argv[1], O_RDONLY);
		while((bytes = read(des, p_buffer, sizeof(p_buffer)))>0)
			write(fd[1], p_buffer, bytes);
	}
	else{
		close(fd[1]);
		target = open(argv[2], O_CREAT | O_WRONLY, 00666);

		while((bytes = read(fd[0], c_buffer, sizeof(c_buffer)))>0)
			write(target, c_buffer, bytes);
		close(fd[0]);
	}
	return 0;
}

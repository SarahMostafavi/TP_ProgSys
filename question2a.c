#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define WELCOME_MESSAGE_SIZE_MAX 80
#define READ_BUFFER_MAX_SIZE 200

int main (){
	// question 1
	char welcome_message[WELCOME_MESSAGE_SIZE_MAX] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseah %";
	write(STDOUT_FILENO,welcome_message,WELCOME_MESSAGE_SIZE_MAX);
	// question 2
		// 2.a
	char read_buffer[READ_BUFFER_MAX_SIZE];
	int n = read(STDIN_FILENO, read_buffer,READ_BUFFER_MAX_SIZE);
	
	
	return 0;
} 
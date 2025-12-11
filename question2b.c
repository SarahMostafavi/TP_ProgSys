#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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
	// 2.b
	read_buffer[n] = '\0';
		// If read_buffer has no argument
	if (n == 1){
		char no_argument_message[21] = "No arguments given!\n";
		write(STDOUT_FILENO,no_argument_message,strlen(no_argument_message));
	}
	else {
		execlp(read_buffer,read_buffer,(char *)NULL);
	}
	return 0;
} 	
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define WELCOME_MESSAGE_SIZE_MAX 80

int main (){
	// question 1
	char welcome_message[WELCOME_MESSAGE_SIZE_MAX] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseah %\n";
	write(STDOUT_FILENO,welcome_message,WELCOME_MESSAGE_SIZE_MAX);
	
	return 0;
} 
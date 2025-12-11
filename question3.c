#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define WELCOME_MESSAGE_SIZE_MAX 80
#define READ_BUFFER_MAX_SIZE 200

#define PROMPT "enseah % "
#define PROMPT_SIZE 8

int main (){
	// question 1
	char welcome_message[WELCOME_MESSAGE_SIZE_MAX] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseah %";
	write(STDOUT_FILENO,welcome_message,WELCOME_MESSAGE_SIZE_MAX);
	// question 2
		// 2.c
	while (1){
			//Lecture des commandes
		char read_buffer[READ_BUFFER_MAX_SIZE];
		int n = read(STDIN_FILENO, read_buffer,READ_BUFFER_MAX_SIZE);	
		
		read_buffer[n] = '\0';
		char *n1 = strchr(read_buffer, '\n');
		if (n1){
			*n1 = '\0';
		}
		
		// question 3
		if((n == 0)||(strcmp(read_buffer,"exit") == 0)){	// CTRL+D -> n==0 and exit
			exit(EXIT_SUCCESS);
		}
			// Création du nouveau processus
		else{
			int pid = fork();
			int status;

			if (pid == -1) {
				perror("Fork impossible");
				exit(EXIT_FAILURE) ;
			}
			else if (pid > 0){		//father code
				wait(&status);
			}
			else{					//child code
				
				if (n == 1){	// Gestion du cas où on fait entrée snas commande								
					char no_argument_message[21] = "No arguments given!\n";
					write(STDOUT_FILENO,no_argument_message,strlen(no_argument_message));
					exit(EXIT_SUCCESS);
				}
				
				else{
					execlp(read_buffer,read_buffer,(char *)NULL);
				}
			}
			write(STDOUT_FILENO,PROMPT,PROMPT_SIZE);
		}
	}
	
	return 0;
} 


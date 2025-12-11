#include <sys/wait.h>
#include <stdlib.h>

#define WELCOME_MESSAGE_SIZE_MAX 80
#define READ_BUFFER_MAX_SIZE 200
#define PROMPT "enseah % "
#define PROMPT_SIZE 8

int main (){
	// question 1
	char welcome_message[WELCOME_MESSAGE_SIZE_MAX] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseah % ";
	write(STDOUT_FILENO,welcome_message,WELCOME_MESSAGE_SIZE_MAX);
	// question 2
		// 2.c
	while (1){
			//Lecture des commandes
		char read_buffer[READ_BUFFER_MAX_SIZE];
		int n = read(STDIN_FILENO, read_buffer,READ_BUFFER_MAX_SIZE);	
		
		read_buffer[n] = '\0';

			// Création du nouveau processus
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
			
			if (n == 1){									// If read_buffer has no argument
				char no_argument_message[21] = "No arguments given!\n";
				write(STDOUT_FILENO,no_argument_message,strlen(no_argument_message));
			}
			
			else if (strcmp(read_buffer,"fortune") == 0){		// If buffer contains 'fortune'
				write(STDOUT_FILENO,"Today is what happened to yesterday.\n",40);
			}
			// question 3
			else if((n == 0)||(strcmp(read_buffer,"exit") == 0)){	// CTRL+D -> n==0 and exit
				execlp(read_buffer,read_buffer,(char *)NULL);
			}
			
			else{
				exit (EXIT_SUCCESS) ;
			}
		}
		write(STDOUT_FILENO,PROMPT,PROMPT_SIZE);
	}
	
	
	return 0;

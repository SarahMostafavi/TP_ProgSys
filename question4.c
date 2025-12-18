#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

// Macros for write
#define PROMPT_SIZE 50
#define WELCOME_MESSAGE_SIZE 69
#define EXIT_MESSAGE_SIZE 12
#define NO_ARGUMENT_MESSAGE_SIZE 21

// Macros for read
#define READ_BUFFER_MAX_SIZE 200



int main (){
	// question 1
	char welcome_message[WELCOME_MESSAGE_SIZE] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseah % ";
	write(STDOUT_FILENO,welcome_message,strlen(welcome_message));
	
    // Variables pour Q4
    int last_exit_code = -1;
    int last_signal = -1;
	
	// question 2
		// 2.c
	while (1){
		//Lecture des commandes
		char read_buffer[READ_BUFFER_MAX_SIZE];
		int n = read(STDIN_FILENO, read_buffer,READ_BUFFER_MAX_SIZE-1);	
		
        if (n < 0){ // erreur
            exit(EXIT_SUCCESS);
        }
		
		read_buffer[n-1] = '\0';
		char *n1 = strchr(read_buffer, '\n');
		if (n1){
			*n1 = '\0';
		}

		// question 3
		if((n == 0)||(strcmp(read_buffer,"exit") == 0)){	// (CTRL+D -> n==0) and exit
			char exit_message[EXIT_MESSAGE_SIZE] = "Bye bye...\n";
			write(STDOUT_FILENO,exit_message,strlen(exit_message));
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
				//question 4
	            char prompt[PROMPT_SIZE];
	            strncpy(prompt, "enseash ", sizeof(prompt) - 1);
	            prompt[sizeof(prompt) - 1] = '\0';
	            
	            if (WIFEXITED(status)){
	                int exit_code = WEXITSTATUS(status);
	                last_exit_code = exit_code;
	                last_signal = -1;
	                char exit_part[20];
	                sprintf(exit_part, "[exit:%d] ", exit_code);
	                strncat(prompt, exit_part, sizeof(prompt) - strlen(prompt) - 1);
	            }else if (WIFSIGNALED(status)){
	                int signal = WTERMSIG(status);
	                last_exit_code = -1;
	                last_signal = signal;
	                char sign_part[20];
	                sprintf(sign_part, "[sign:%d] ", signal);
	                strncat(prompt, sign_part, sizeof(prompt) - strlen(prompt) - 1);
	            }
	            
				strncat(prompt, "% ", sizeof(prompt) - strlen(prompt) - 1);
				write(STDOUT_FILENO,prompt,strlen(prompt));
			}
			else{					//child code
				
				if (n == 1){	// Gestion du cas où on fait entrée snas commande								
					char no_argument_message[NO_ARGUMENT_MESSAGE_SIZE] = "No arguments given!\n";
					write(STDOUT_FILENO,no_argument_message,strlen(no_argument_message));
					exit(EXIT_SUCCESS);
				}
				
				else{
					execlp(read_buffer,read_buffer,(char *)NULL);
				}
			}
		}
	}
	
	return 0;
} 


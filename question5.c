#define _POSIX_C_SOURCE 199309L
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>


// Macros for write
#define PROMPT_SIZE 50
#define WELCOME_MESSAGE_SIZE 69
#define EXIT_MESSAGE_SIZE 12
#define NO_ARGUMENT_MESSAGE_SIZE 21

// Macros for read
#define READ_BUFFER_MAX_SIZE 200



int main (int argc, char *argv[]){
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
		
			
		else{
			// question 5
			struct timespec start_time, end_time;
			clock_gettime(CLOCK_MONOTONIC, &start_time);
			// Création du nouveau processus
			int pid = fork();
			int status;

			if (pid == -1) {
				perror("Fork impossible");
				exit(EXIT_FAILURE) ;
			}
			else if (pid > 0){		//father code
				wait(&status);
	            // question 5 : end of the execution 
				clock_gettime(CLOCK_MONOTONIC, &end_time);
				long execution_time_ms;
				// calcul du temps d'execution en ms
				execution_time_ms =(end_time.tv_sec-start_time.tv_sec)*1000 +(end_time.tv_nsec-start_time.tv_nsec)/1000000;
				
				//question 4 et 5
	            char prompt[PROMPT_SIZE];
	            strncpy(prompt, "enseash ", sizeof(prompt) - 1);
	            prompt[sizeof(prompt) - 1] = '\0';
	           
	            
	            if (WIFEXITED(status)){
	                int exit_code = WEXITSTATUS(status);
	                last_exit_code = exit_code;
	                last_signal = -1;
	                char exit_part[30];
	                sprintf(exit_part, "[exit:%d|%ldms]", exit_code,execution_time_ms);
	                strncat(prompt, exit_part, sizeof(prompt) - strlen(prompt) - 1);
	            }else if (WIFSIGNALED(status)){
	                int signal = WTERMSIG(status);
	                last_exit_code = -1;
	                last_signal = signal;
	                char sign_part[30];
	                sprintf(sign_part, "[sign:%d|%ldms]", signal,execution_time_ms);
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
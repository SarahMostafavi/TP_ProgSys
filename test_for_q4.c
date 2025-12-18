#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (){
	
	char test_message[50];
    sprintf(test_message,"Le PID du programme est : %d\n", getpid());

	write(STDOUT_FILENO,test_message,strlen(test_message));
	while (1);
}
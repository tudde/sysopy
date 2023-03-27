#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


void isPending(void){
    sigset_t set;

    sigpending(&set);

    if(sigismember(&set, SIGUSR1))
        printf("Signal SIGUSR1 is pending\n");
    else
        printf("Signal SIGUSR1 is not pending\n");
}

int main(int argc, char *argv[]){

 

    printf("\nBegin exec\n");
   
    if( strcmp(argv[1], "pending") == 0){
        isPending();
    }
    else{
        raise(SIGUSR1);
    }

    return 0;
}
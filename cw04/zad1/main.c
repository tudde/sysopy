#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

typedef enum{
    IGNORE,
    HANDLER,
    MASK,
    PENDING
} option;

void isPending(void){
    sigset_t set;

    sigpending(&set);

    if(sigismember(&set, SIGUSR1))
        printf("Signal SIGUSR1 is pending\n");
    else
        printf("Signal SIGUSR1 is not pending\n");
}

void handle(int signo){
    printf("Signal handled\n");

}


int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "Wrong number of arguments");
        return -1;
    }
    


    option selectedOption;

    if(strcmp(argv[1],"ignore") == 0){
        selectedOption = IGNORE;
    }
    else if(strcmp(argv[1],"handler") == 0){
        selectedOption = HANDLER;
    }
    else if(strcmp(argv[1],"mask") == 0){
        selectedOption = MASK;
    }
    else if(strcmp(argv[1],"pending") == 0){
        selectedOption = PENDING;
    }
    else{
        fprintf(stderr, "Possible options: ignore|handler|mask|pending");
        return -1;
    }


    struct sigaction action;
    sigset_t mask;
    sigemptyset(&mask);

    switch (selectedOption){
    case IGNORE:
        action.sa_handler = SIG_IGN;
        sigaction(SIGUSR1, &action, NULL); 
        break;
    case HANDLER:
        action.sa_handler = handle;
        sigaction(SIGUSR1, &action, NULL); 
        break;
    case MASK:
        
        sigaddset(&mask,SIGUSR1);
        sigprocmask(SIG_BLOCK, &mask, NULL);
        break;
    case PENDING:
        sigaddset(&mask,SIGUSR1);
        sigprocmask(SIG_BLOCK, &mask, NULL);
        break;
    
    default:
        break;
    }

    printf("Begin parent\n");
    
    raise(SIGUSR1);
    
    if(selectedOption == PENDING){
        isPending();
    }

    // forking from this point
    
    int pid;
    pid = fork();
    if(pid == 0){
        printf("\nBegin fork\n");
        
        if(selectedOption == PENDING){
        isPending();
        }
        else{
            raise(SIGUSR1);
        }
        return 0;

    }

    wait(NULL);


    
    execl("./to_exec","to_exec", argv[1], NULL);
    perror("a");







    
    


    return 0;
}
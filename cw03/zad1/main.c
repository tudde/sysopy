#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){


    
    pid_t wpid;
    printf("Main pid: %d\n\n\n",getpid());

    for(int i=0;i<atoi(argv[1]);i++){
        int id = fork();
        if(id == 0){
            printf("process: %d; parent: %d\n\n", getpid(),getppid());
            exit(0);
        }
    }


    while ((wpid = wait(NULL)) > 0); 
    printf("\nProcesses created: %s\n\n", argv[1]);
    


    return 0;
}
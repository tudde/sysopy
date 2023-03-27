#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int call_depth = 0;

void siginfoTest(int signo, siginfo_t* siginfo, void* context){
    printf("\nHandling signal\n");
    printf("Signal number: %d\n", signo);
    printf("Sent from process: %d\n", siginfo->si_pid);
    printf("Sent from user: %d\n", siginfo->si_uid);
}
void siginfoTestValue(int signo, siginfo_t* siginfo, void* context){
    printf("\nHandling signal with custom value\n");
    printf("Signal number: %d\n", signo);
    printf("Sent from process: %d\n", siginfo->si_pid);
    printf("Value sent: %d\n", siginfo->si_value.sival_int);
}
void siginfoTestChild(int signo, siginfo_t* siginfo, void* context){
    printf("\nHandling signal from child process\n");
    printf("Signal number: %d\n", signo);
    printf("Sent from process (child): %d\n", siginfo->si_pid);
    printf("Child exit status: %d\n", siginfo->si_status);
  
}

void nodeferTest(int signo, siginfo_t* siginfo, void* context){

    call_depth++;
    printf("Current call depth: %d\n", call_depth);
    if (call_depth<5){
        raise(SIGUSR1);
    }
    call_depth--;
    
}

void resethandTest(int signo, siginfo_t* siginfo, void* context){
    printf("Signal handled!\n");
}


int main(int argc, char *argv[]){

    printf("---SIGINFO test---\n");
    struct sigaction act1;
    sigemptyset(&act1.sa_mask);
    act1.sa_flags = SA_SIGINFO;
    act1.sa_sigaction = siginfoTest;
    sigaction(SIGUSR1, &act1, NULL);

    struct sigaction act2;
    sigemptyset(&act2.sa_mask);
    act2.sa_flags = SA_SIGINFO;
    act2.sa_sigaction = siginfoTestValue;
    sigaction(SIGUSR2, &act2, NULL);

    struct sigaction act3;
    sigemptyset(&act3.sa_mask);
    act3.sa_flags = SA_SIGINFO;
    act3.sa_sigaction = siginfoTestChild;
    sigaction(SIGCHLD, &act3, NULL);



    raise(SIGUSR1);

    //receive signal with custom value
    sigval_t value = {2};
    sigqueue(getpid(), SIGUSR2, value);

    //receive signal from child
    int pid=fork();
    if(pid == 0){
        printf("\n in child \n");
        exit(1);
    }
    wait(NULL);


    printf("\n---NODEFER test---\n");
    struct sigaction act4;
    sigemptyset(&act4.sa_mask);
    act4.sa_flags = SA_NODEFER;
    act4.sa_sigaction = nodeferTest;
    sigaction(SIGUSR1, &act4, NULL);

    raise(SIGUSR1);


    printf("\n---RESETHAND test---\n");

    struct sigaction act5;
    sigemptyset(&act5.sa_mask);
    act5.sa_flags = SA_RESETHAND;
    act5.sa_sigaction = resethandTest;
    sigaction(SIGUSR1, &act5, NULL);

    raise(SIGUSR1);

    raise(SIGUSR1);

    return 0;
}
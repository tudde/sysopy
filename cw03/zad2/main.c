#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char *argv[]){

    if(argc<2){
        printf("\nToo few arguments\n");
        return -1;
    }

    printf("Main process name: %s\n\n", argv[0]);
    printf("\n%s\n", argv[1]);
    fflush(stdout);

    
    execl("/bin/ls", "ls", argv[1], (char *)NULL);

    return 0;
}
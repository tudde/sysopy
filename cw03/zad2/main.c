#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char *argv[]){

    if(argc<2){
        printf("\nToo few arguments\n");
        return -1;
    }

    printf("Main process name: %s\n\n", argv[0]);

    fflush(stdout);

    execl("/bin/ls",argv[1], (char *)NULL);



    




    return 0;
}
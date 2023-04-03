#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



double f(double x){
    return 4/(pow(x, 2) + 1);
}


int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr,"Wrong number of arguments");
        return 1;
    }

    double n = atof(argv[2]);
    double inter_len = 1/n;
    double sum = 0;
    double curr_start = 0;

    char * pipePath = "./fifo";
    mkfifo(pipePath, 0666);
    
    for(int i=0;i<n;i++){
        int pid=fork();
        if(pid==0){
        int len = snprintf(NULL, 0, "%f", curr_start);
        char a[len+1];
        snprintf(a, len+1, "%f", curr_start);
        len = snprintf(NULL, 0, "%f", curr_start + inter_len);
        char b[len+1];
        snprintf(b, len+1, "%f", curr_start + inter_len);
        execl("./integrate", "integrate", argv[1], a,b, NULL );
        }
        curr_start = curr_start + inter_len;
    }

    

   
    FILE * fp = fopen(pipePath, "r");
    

    int wpid;
    while ((wpid = wait(NULL)) > 0);
    
    sum=0;
    char buff[256];
    for(int i=0;i<n;i++){
        fgets(buff, 256,fp);
        sum = sum + atof(buff);
    }

    printf("Calculated integral value: %f\n" ,sum);
    remove(pipePath);

    return 0;
}
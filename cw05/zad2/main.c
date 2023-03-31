#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <sys/wait.h>



double f(double x){
    return 4/(pow(x, 2) + 1);
}


int main(int argc, char *argv[]){

    if (argc < 3){
        fprintf(stderr,"Wrong number of arguments");
        return 1;
    }


    double step = atof(argv[1]);
    double n = atof(argv[2]);
    double inter_len = 1/n;
    double sum = 0;
    double curr_x = 0;
    double curr_start = 0;

    int fd[2];
    pipe(fd);

    for(int i=0;i<n;i++){
        int pid = fork();
        if(pid == 0){
            close(fd[0]);
            sum = 0;
            curr_x = curr_start;
            while (curr_x < curr_start + inter_len){
            
            sum = sum + f(curr_x)*step;
            curr_x = curr_x + step;
             
            }
            write(fd[1],&sum,sizeof(double));
            exit(0);
        }
        
        curr_start = curr_start + inter_len;
    }

    close(fd[1]);
    int wpid;
    while ((wpid = wait(NULL)) > 0);
    
    sum=0;

    double buff;
    for(int i=0;i<n;i++){
        read(fd[0],&buff,sizeof(double));
        sum = sum + buff;
    }

    printf("Calculated integral value: %f\n" ,sum);



    return 0;
}
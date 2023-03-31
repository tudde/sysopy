#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>




int main(int argc, char *argv[]){


    if(argc == 1){
        FILE *fp;
        char buff[PIPE_BUF];
    
        fp = popen("fortune","r");
        fgets(buff,PIPE_BUF,fp);
        printf("%s", buff);
        pclose(fp);
        
    }
    if(argc == 2){
        FILE *fp;
        fp = popen("cowsay","w");
        fputs(argv[1],fp);
        pclose(fp);
    }






    return 0;
}
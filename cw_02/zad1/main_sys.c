#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, char *argv[]){
    if(argc!=5){
        printf("Incorrect number of arguments");
    }
    char to_replace = argv[1][0];
    char replace_with = argv[2][0];

    int in_handle = open(argv[3], O_RDONLY);
    int out_handle = open(argv[4], O_WRONLY | O_CREAT);

    char c;
    int state;
    state = read(in_handle,&c,sizeof(char));
        while(state!=0){
            if(c==to_replace){
                write(out_handle, &replace_with, sizeof(char));
            }
            else{
                write(out_handle, &c, sizeof(char));
            }
            state = read(in_handle,&c,sizeof(char));
        } 
    return 0;
}
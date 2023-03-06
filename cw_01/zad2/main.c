#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylibrary.h"

int main(){
    char command[255];
    char* arg;
    MemArray* mainArray;
    int init_flag = 0;

     while(1){
        fgets(command,255,stdin);
        strtok(command," ");
        arg=strtok(NULL," ");
        strtok(NULL," ");
        if (strcmp(command, "init") == 0) 
        {
            if(init_flag==0){
                mainArray=create_MemArray(atoi(arg));
                init_flag=1;
            }
            else{
                printf("Array already initialized\n");
            }
        } 
        else if (strcmp(command, "count") == 0)
        {
            if(init_flag==1){
                arg[strlen(arg)-1]=' ';
                run_wc(mainArray, arg);
            }
            else{
                printf("Array not initialized\n");
            }
        }
        else if (strcmp(command, "show") == 0)
        {
            
            if(init_flag==1){
                printf("%s",value_at(mainArray, atoi(arg)));
            }
            else{
                printf("Array not initialized\n");
            }

        }
        else if (strcmp(command, "delete") == 0)
        {
            if(init_flag==1){
            remove_at(mainArray, atoi(arg));
            }
            else{
                printf("Array not initialized\n");
            }

        }
        else if (strcmp(command, "destroy\n") == 0)
        {
            if(init_flag==1){
            free_array(mainArray);
            init_flag=0;
            }
            else{
                printf("Array not initialized\n");
            }
        }
        else
        {       
        }
        printf("%d\n",init_flag);

    }



    return 0;
}

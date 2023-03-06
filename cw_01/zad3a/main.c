#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/times.h>
#include <time.h>
#include <unistd.h>

#ifndef DYNAMIC
    #include "mylibrary.h"
#endif

#ifdef DYNAMIC
    #include <dlfcn.h>

    typedef struct{
        char** ptrArray;
        int size;
        int taken;
    } MemArray;
#endif


int main(){
    #ifdef DYNAMIC
        void *handle = dlopen("./libmylibrary.so", RTLD_LAZY);
        MemArray* (*create_MemArray)(int) = dlsym(handle, "create_MemArray");
        void (*run_wc)(MemArray*, char*) = dlsym(handle, "run_wc");
        char* (*value_at)(MemArray*, int) = dlsym(handle, "value_at");
        void (*remove_at)(MemArray*, int) = dlsym(handle, "remove_at");
        void (*free_array)(MemArray*) = dlsym(handle, "free_array");
    #endif

    char command[255];
    char* arg;
    MemArray* mainArray;
    int init_flag = 0;

     while(1){
        
        fgets(command,255,stdin);

        struct tms begin, end; 
        struct timespec begin_sys, end_sys, begin_real, end_real; 
        clock_gettime(CLOCK_REALTIME, &begin_real);
        times(&begin);
        strtok(command," ");

        arg=strtok(NULL," ");
        strtok(NULL," ");

        if (strcmp(command, "init") == 0) 
        {
            if(init_flag==0){
                printf("\n Initializing array\n");
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
                printf("\n Running wc\n");
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
                printf("\n Showing value\n");
                printf("%s",value_at(mainArray, atoi(arg)));
            }
            else{
                printf("Array not initialized\n");
            }

        }
        else if (strcmp(command, "delete") == 0)
        {
            if(init_flag==1){
                printf("\n Deleting value\n");
            remove_at(mainArray, atoi(arg));
            }
            else{
                printf("Array not initialized\n");
            }

        }
        else if (strcmp(command, "destroy\n") == 0)
        {
            printf("\n Destroying array\n");
            if(init_flag==1){
            free_array(mainArray);
            init_flag=0;
            }
            break;
        }
        else{       
        }

        times(&end);
        clock_gettime(CLOCK_REALTIME, &end_real);
        long seconds = end_real.tv_sec - begin_real.tv_sec;
        long nanoseconds = end_real.tv_nsec - begin_real.tv_nsec;
        double elapsed_real = seconds + nanoseconds*1e-9;
        
        printf("real time: %.10f\n", elapsed_real);
        printf("system time: %.10f\n", (double) (end.tms_stime - begin.tms_stime)/sysconf(_SC_CLK_TCK));
        printf("user time: %.10f\n", (double) (end.tms_utime - begin.tms_utime)/sysconf(_SC_CLK_TCK));
    }

    return 0;
}

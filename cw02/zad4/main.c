#include <stdio.h>
#include <ftw.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


long long size_sum;

int process_file(const char * path,const struct stat * stats, int flags){

    char pathcpy[strlen(path)];
    strcpy(pathcpy,path);
    char* prv_name;
    char* name;
    name =  strtok(pathcpy,"/");
    while(name!=NULL){
        prv_name=name;
        name=strtok(NULL,"/");
    } 
   
    printf("\nsize: %ld\nname: %s\n", stats->st_size, prv_name);
    
    if(!S_ISDIR(stats->st_mode)){
                size_sum = size_sum + stats->st_size;
            }
    return 0;
}





int main(int argc, char *argv[]){

    size_sum = 0;
    ftw(argv[1],process_file,100);
    printf("\n-------------\nTOTAL SUM: %lld\n", size_sum);
    return 0;
}

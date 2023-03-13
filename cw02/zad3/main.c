#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>



int main(){

    DIR* dir;
    struct dirent* entry;
    struct stat stats;
    char path[1024];
    long long size_sum = 0;

    if ((dir = opendir(".")) != NULL){
        while ((entry = readdir(dir)) != NULL) {

            printf("\nname: %s\nsize: %ld\n", entry->d_name, stats.st_size);
            strcpy(path, "./");
            strcat(path, entry->d_name);
            stat(path,&stats);
            if(!S_ISDIR(stats.st_mode)){
                size_sum = size_sum + stats.st_size;
                printf("\nname: %s\nsize: %ld\n", entry->d_name, stats.st_size);
            }
        }
        printf("%lld", size_sum);

    }

    closedir(dir);

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ftw.h>
#include <linux/limits.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>



int searchdir(char path[], char tofind[]){
    DIR* dir;
    struct dirent* entry;
    struct stat stats;
    char newpath[PATH_MAX];
    char resolvedpath[PATH_MAX];
    if ((dir = opendir(path)) != NULL){
            while ((entry = readdir(dir)) != NULL) {

                strcpy(newpath, path);
                if(newpath[strlen(newpath)-1]!='/'){
                    strcat(newpath, "/");
                }
                
                strcat(newpath, entry->d_name);
                if (realpath(newpath,resolvedpath)==NULL){
                    perror("error");
                    exit(-1);
                }

                if (stat(resolvedpath,&stats) == -1){
                    perror("error");
                    exit(-1);
                }

                if(S_ISDIR(stats.st_mode)){
                    if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                        
                        int id = fork();
                        if(id == 0){
                            searchdir(resolvedpath, tofind);
                            exit(0);
                        }

                    }
                }
                else{
                
                    FILE * file = fopen(resolvedpath,"r");
                    if(file == NULL){
                        perror("error");
                        exit(-1);
                    }
            
                    char buff[strlen(tofind)];
                    fread(buff, sizeof(char), strlen(tofind), file);
                    
                    fclose(file);
                    
                    if(strcmp(buff,tofind) == 0){
                        printf("\n%s\nprocess: %i\n",resolvedpath,getpid());
                    }
                    
                }
            }
            closedir(dir);
            return 0;
            
        }
        perror("error");
        return -1;
}




int main(int argc, char *argv[]){
    
    if(argc<3){
        fprintf(stderr,"\nToo few arguments\n");
        exit(-1);
    }

    if(strlen(argv[2])>255){
        fprintf(stderr,"\nInput string should be 255 characters at most\n");
        exit(-1);
    }

    searchdir(argv[1], argv[2]);

    return 0;
}
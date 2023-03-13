#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Incorrect number of arguments\n");
        return -1;
    }
    

    FILE* in_handle = fopen(argv[1], "r");
    FILE* out_handle = fopen(argv[2],"w");

    if(in_handle==NULL){
        printf("Input directory does not exist\n");
        return -1;
    }

    char c;
    int status=fseek(in_handle,-1,SEEK_END);
        while(status==0){
            c=fgetc(in_handle);
            fputc(c,out_handle);
            status=fseek(in_handle,-2,SEEK_CUR);    
        } 
    
    fclose(in_handle);
    fclose(out_handle);

    return 0;
}
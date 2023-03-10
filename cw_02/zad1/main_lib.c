#include <stdio.h>
#include <string.h>




int main(int argc, char *argv[]){
    if(argc!=5){
        printf("Incorrect number of arguments");
    }
    char to_replace = argv[1][0];
    char replace_with = argv[2][0];

    
    FILE* in_handle = fopen(argv[3], "r");
    FILE* out_handle = fopen(argv[4],"w");

    char c = fgetc(in_handle);
        while(c!=EOF){
            if(c==to_replace){
                fputc(replace_with, out_handle);
            }
            else{
                fputc(c, out_handle);
            }
            c=fgetc(in_handle);
        } 
    
    fclose(in_handle);
    fclose(out_handle);

    return 0;
}
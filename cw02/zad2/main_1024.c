#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Incorrect number of arguments\n");
        return -1;
    }
  
    int BLOCK_SIZE=1024;
    FILE* in_handle = fopen(argv[1], "r");
    FILE* out_handle = fopen(argv[2],"w");

    if(in_handle==NULL){
        printf("Input directory does not exist\n");
        return -1;
    }

    int bytes;
    for(bytes = 0; getc(in_handle) != EOF; ++bytes);
    

    char buff[1024];
    int status = fseek(in_handle, -BLOCK_SIZE, SEEK_END);
    // if status = zero then enough data for a full-sized block

    int chars_read;
        while(status==0){
            chars_read=fread(buff, sizeof(char),BLOCK_SIZE,in_handle);

            // reverse string
            for(int i=0;i<chars_read/2;i++){
                char tmp = buff[i];
                buff[i] = buff[chars_read-i-1];
                buff[chars_read-i-1] = tmp;
            }
            fwrite(buff,sizeof(char),chars_read,out_handle);
            status=fseek(in_handle,-(2*BLOCK_SIZE),SEEK_CUR);
        }
    //read and reverse remaining data
    fseek(in_handle,0,SEEK_SET);
    chars_read=fread(buff, sizeof(char),bytes%BLOCK_SIZE,in_handle);
    for(int i=0;i<chars_read/2;i++){
                char tmp = buff[i];
                buff[i] = buff[chars_read - i-1];
                buff[chars_read - i-1] = tmp;
            }
    fwrite(buff,sizeof(char),chars_read,out_handle);

    fclose(in_handle);
    fclose(out_handle);

    return 0;
} 
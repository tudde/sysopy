#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Incorrect number of arguments");
        return -1;
    }
  
    
    FILE* in_handle = fopen(argv[1], "r");
    FILE* out_handle = fopen(argv[2],"w");

    int bytes;
    for(bytes = 0; getc(in_handle) != EOF; ++bytes);
    printf("File size:                %d bytes%d\n",bytes, bytes%1024);

    char buff[1024];
    int status=fseek(in_handle,-1024,SEEK_END);
    int chars_read;
        while(status==0){
            chars_read=fread(buff, sizeof(char),1024,in_handle);
            for(int i=0;i<512;i++){
                char tmp = buff[i];
                buff[i] = buff[1024 - i];
                buff[1024 - i] = tmp;
            }
            fwrite(buff,sizeof(char),chars_read,out_handle);
            status=fseek(in_handle,-2048,SEEK_CUR);
            printf("%s",buff);
        }
    fseek(in_handle,0,SEEK_SET);
    chars_read=fread(buff, sizeof(char),bytes%1024,in_handle);
    for(int i=0;i<chars_read/2;i++){
                char tmp = buff[i];
                buff[i] = buff[chars_read - i-1];
                buff[chars_read - i-1] = tmp;
            }
    fwrite(buff,sizeof(char),chars_read,out_handle);
    printf("\nEND PART %s\n",buff);

    
    fclose(in_handle);
    fclose(out_handle);

    return 0;
} 
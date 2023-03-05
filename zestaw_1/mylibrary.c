#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MemArray{
    char** ptrArray;
    int size;
    int taken;
};
typedef struct MemArray MemArray;

MemArray create_MemArray(int size){
    MemArray res;
    res.size=size;
    res.ptrArray = calloc(size,sizeof(char*));
    res.taken=0;
    return res;
}

void run_wc(MemArray* mainArray, char* filename){
    char wcToTmp[255] = "wc ";
    char saveTo[] =" > ";
    char tmpPath[]="/tmp/costamXXXXXX";
    mkstemp(tmpPath);
    
    
    // char tmpPath[18]="/tmp/";
    // strcat(tmpPath,tmpName);

    

    strcat(wcToTmp, filename);
    strcat(wcToTmp, saveTo);
    strcat(wcToTmp, tmpPath);


    char rmTmp[20]="rm ";
    strcat(rmTmp,tmpPath);
    

    int err=system(wcToTmp);
    if(err!=-1){
        FILE* tmpPtr;
        char buff[255];

        tmpPtr = fopen(tmpPath,"r");
        fgets(buff,255,tmpPtr);

        fclose(tmpPtr);

        if(mainArray->taken < mainArray->size){
            mainArray->ptrArray[mainArray->taken]=(char*)calloc(strlen(buff),sizeof(char));   
            strcpy(mainArray->ptrArray[mainArray->taken],buff);
            mainArray->taken++;
        }
        else{
            printf("Unable to save more data\n");
        }

    system(rmTmp);
    }
}

char* valueAt(MemArray mainArray, int idx){
    if(idx>=mainArray.taken){
        return "No such index exists\n";
    }
    return mainArray.ptrArray[idx];
}
void removeAt(MemArray mainArray, int idx){
    if(idx>=mainArray.size){
        return;
    }
    free(mainArray.ptrArray[idx]);
}
void freeArray(MemArray mainArray){
    free(mainArray.ptrArray);
}

int main() {
    MemArray a = create_MemArray(2);
    
    run_wc(&a,"mylibrary.c");
    
    run_wc(&a,"bruh.c");
    printf("%s\n", valueAt(a,0));
    removeAt(a,0);
    printf("%s\n", valueAt(a,2));
   return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/msg.h>
#include <signal.h>

#include "util.h"
key_t c_key;
key_t s_key;
int c_queue;
int s_queue;
int c_id;

int init(){
    
    time_t timestamp = time(NULL);
    
    m_buffer *buff = malloc(sizeof(m_buffer));
    buff->mtype = INIT;
    buff->time = *localtime(&timestamp);
    buff-> c_queue = c_queue;

    msgsnd(s_queue, buff, MSG_BUFF_SIZE, 0);
    msgrcv(c_queue, buff, MSG_BUFF_SIZE,0 ,0);

    if (buff->c_id == -1){
        fprintf(stderr, "Server limit reached\n");
        exit(-1);
    }

    return buff->c_id;
}


void stop(){
    time_t timestamp = time(NULL);
    m_buffer *buff = malloc(sizeof(m_buffer));
    buff->mtype = STOP;
    buff->time = *localtime(&timestamp);
    buff-> c_id = c_id;

    msgsnd(s_queue, buff, MSG_BUFF_SIZE,0);
    msgctl(c_queue,IPC_RMID,NULL);

    exit(0);
}

void one(char* id, char* message){
    time_t timestamp = time(NULL);
    m_buffer *buff = malloc(sizeof(m_buffer));
    buff->mtype = ONE;
    buff->time = *localtime(&timestamp);
    buff-> c_id = c_id;
    buff->receiver_id = atoi(id);
    strcpy(buff->message,message);

    msgsnd(s_queue, buff, MSG_BUFF_SIZE,0);
}

void all(char* message){
    time_t timestamp = time(NULL);
    m_buffer *buff = malloc(sizeof(m_buffer));
    buff->mtype = ALL;
    buff->time = *localtime(&timestamp);
    buff-> c_id = c_id;
    strcpy(buff->message,message);

    msgsnd(s_queue, buff, MSG_BUFF_SIZE,0);
}
void list(){
    time_t timestamp = time(NULL);
    m_buffer *buff = malloc(sizeof(m_buffer));
    buff->mtype = LIST;
    buff->time = *localtime(&timestamp);
    buff-> c_id = c_id;

    msgsnd(s_queue, buff, MSG_BUFF_SIZE,0);
}


int main(int argc, char *argv[]){
    char input[255];
    char* arg1;
    char* arg2;
    m_buffer *rcv_buff = malloc(sizeof(m_buffer));


    srand(time(NULL));
    s_key = ftok(getenv("HOME"),1);
    c_key = ftok(getenv("HOME"), rand()%1000 +1);
    
    s_queue = msgget(s_key,0);
    c_queue = msgget(c_key, IPC_CREAT | 0666);

    signal(SIGINT, stop);                                         
        printf("--%d--%d--", c_queue,s_queue);
    c_id = init();
    printf("%d",c_id);


    while(1){

        

        fgets(input,255,stdin);
        strtok(input," ");
        char command[5];
        strncpy(command,input,4);
        command[4]='\0';

        arg1=strtok(NULL," ");
        arg2=strtok(NULL," ");
        strtok(NULL," ");
        
        

        if(strcmp(command,"LIST") == 0){
            list();
        }
        else if(strcmp(command,"2ALL") == 0){
            all(arg1);
        }
        else if(strcmp(command,"2ONE") == 0){
            one(arg1, arg2);
        }
        else if(strcmp(command,"STOP") == 0){
            stop();
        }
        else{
        }


        while(msgrcv(c_queue,rcv_buff,MSG_BUFF_SIZE,0,IPC_NOWAIT)>0){
            if(rcv_buff->mtype==STOP){
                exit(0);
            }
            printf("Message from id: %d\nTime: %d:%d;%d\n%s\n\n",
            rcv_buff->c_id,rcv_buff->time.tm_hour,rcv_buff->time.tm_min,rcv_buff->time.tm_sec,rcv_buff->message);
        }

        
    }

    return 0;
}

    
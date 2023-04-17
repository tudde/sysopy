#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <time.h>
#include <signal.h>

#include "util.h"

key_t client_list[MAX_CLIENTS];
int last_idx = 0;

int s_queue;



void init(m_buffer *buff){
    int set = 0;
    for(int i=0; i<MAX_CLIENTS;i++){
        if(client_list[i]==-1){
            client_list[i]=buff->c_queue;
            printf("Initiating client with id %d\n", i);
            buff->c_id = i;
            set = 1;
            break;
        }
    }

    if(set == 0){
        fprintf(stderr, "Client limit reached.");
        buff->c_id = -1;
    }
   
    msgsnd(buff->c_queue, buff,MSG_BUFF_SIZE,0);
    
}
void stop(m_buffer *buff){
    printf("Stopping client with id %d\n", buff->c_id);
    client_list[buff->c_id]=-1;
}

void one(m_buffer *buff){
    if(client_list[buff->receiver_id]!=-1){
         printf("Message sent to client with id %d\n", buff->receiver_id);
        msgsnd(client_list[buff->receiver_id],buff,MSG_BUFF_SIZE,0);
    }
    
}

void all(m_buffer *buff){
    for(int i=0; i<MAX_CLIENTS;i++){
        if(client_list[i]!=-1){
            printf("Message sent to client with id %d\n", i);
            msgsnd(client_list[i],buff,MSG_BUFF_SIZE,0);
        }
    }
}

void list(m_buffer *buff){
    printf("Active clients: ");
    for(int i=0; i<MAX_CLIENTS;i++){
        if(client_list[i]!=-1){
            printf("%d, ", i);
        }
    }
    printf("\n");

}
void server_stop(){
    m_buffer *buff = malloc(sizeof(m_buffer));
    buff->mtype=STOP;
    for(int i=0; i<MAX_CLIENTS;i++){
        if(client_list[i]!=-1){
            printf("Stopping client with id %d\n", i);
            msgsnd(client_list[i],buff,MSG_BUFF_SIZE,0);
        }
    }
    msgctl(s_queue,IPC_RMID,NULL);

    exit(0);

}

void log_message(m_buffer *buff){
    FILE * log = fopen("log.txt","a");
    fprintf(log,"Message from id: %d\nTime: %d:%d;%d\n%sType: ",
            buff->c_id,buff->time.tm_hour,buff->time.tm_min,buff->time.tm_sec,buff->message);
        
    switch (buff->mtype)
    {
    case INIT:
        fprintf(log,"INIT\n\n");
        break;
    case LIST:
        fprintf(log,"LIST\n\n");
        break;
    case ONE:
        fprintf(log,"2ONE\n\n");
        break;
    case ALL:
        fprintf(log,"2ALL\n\n");
        break;
    case STOP:
        fprintf(log,"STOP\n\n");
        break;
    }
    fclose(log);

}


int main(int argc, char *argv[]){

    m_buffer* buff = malloc(sizeof(m_buffer));
    key_t s_key = ftok(getenv("HOME"),1);
    s_queue = msgget(s_key, IPC_CREAT | 0666);
    signal(SIGINT, server_stop);

    for(int i=0; i<MAX_CLIENTS;i++){
        client_list[i]=-1;
    }

    while(1){
        msgrcv(s_queue, buff, MSG_BUFF_SIZE, -6, 0);
        switch(buff->mtype){
            case INIT:
                init(buff);
                log_message(buff);
                break;
            case LIST:
                list(buff);
                log_message(buff);
                break;
            case ALL:
                all(buff);
                log_message(buff);
            break;
            case ONE:
                one(buff);
                log_message(buff);
                break;
            case STOP:
                stop(buff);
                log_message(buff);
                break;
        }
    }

    
    return 0;
}

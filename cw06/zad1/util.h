#ifndef __UTIL_H__
#define UTIL_H__
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <time.h>

#define MSG_BUFF_SIZE 4096
#define MAX_CLIENTS 10

typedef struct m_buffer{
    long mtype;
    int c_queue;
    int c_id;
    int receiver_id;
    char message[MSG_BUFF_SIZE];
    struct tm time;
} m_buffer;

typedef enum m_type{
    INIT = 1,
    LIST = 2,
    ALL = 3,
    ONE = 4,
    STOP = 5
} m_type;


#endif
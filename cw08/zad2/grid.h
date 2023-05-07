#pragma once
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>

struct thread_args{
    char *src;
    char *dst;
    int a;
    int b;
};
typedef struct thread_args thread_args;


char *create_grid();
void destroy_grid(char *grid);
void draw_grid(char *grid);
void init_grid(char *grid);
bool is_alive(int row, int col, char *grid);
void update_grid(char *src, char *dst);
void threads_init(pthread_t threads[], thread_args** arg_structs, int n, int block_size, char* src, char* dst);
void update_grid_2(pthread_t threads[], int n);
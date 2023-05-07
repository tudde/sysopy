#include "grid.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

const int grid_width = 30;
const int grid_height = 30;
typedef struct thread_args thread_args;


char *create_grid()
{
    return malloc(sizeof(char) * grid_width * grid_height);
}

void destroy_grid(char *grid)
{
    free(grid);
}

void draw_grid(char *grid)
{
    for (int i = 0; i < grid_height; ++i)
    {
        // Two characters for more uniform spaces (vertical vs horizontal)
        for (int j = 0; j < grid_width; ++j)
        {
            if (grid[i * grid_width + j])
            {
                mvprintw(i, j * 2, "■");
                mvprintw(i, j * 2 + 1, " ");
            }
            else
            {
                mvprintw(i, j * 2, " ");
                mvprintw(i, j * 2 + 1, " ");
            }
        }
    }

    refresh();
}

void init_grid(char *grid)
{
    for (int i = 0; i < grid_width * grid_height; ++i)
        grid[i] = rand() % 2 == 0;
}

bool is_alive(int row, int col, char *grid)
{

    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int r = row + i;
            int c = col + j;
            if (r < 0 || r >= grid_height || c < 0 || c >= grid_width)
            {
                continue;
            }
            if (grid[grid_width * r + c])
            {
                count++;
            }
        }
    }

    if (grid[row * grid_width + col])
    {
        if (count == 2 || count == 3)
            return true;
        else
            return false;
    }
    else
    {
        if (count == 3)
            return true;
        else
            return false;
    }
}

void update_grid(char *src, char *dst)
{
    for (int i = 0; i < grid_height; ++i)
    {
        for (int j = 0; j < grid_width; ++j)
        {
            dst[i * grid_width + j] = is_alive(i, j, src);
        }
    }
}

void* thread_routine(void* args){
	thread_args* arg = (thread_args*)args;

    while(1){

        for(int i=arg->a;i<arg->b;i++){
            arg->dst[i] = is_alive(i/grid_width, i%grid_width, arg->src);
        }
        char* tmp;
        tmp = arg->src;
        arg->src = arg->dst;
        arg->dst = tmp;
        pause();
    }
	return NULL;
}
void threads_init(pthread_t threads[], thread_args** arg_structs, int n, int block_size ,char* src, char* dst){
    arg_structs = malloc(n*sizeof(thread_args*));
    int a = 0;
    int b = block_size;

	for(int i = 0; i < n; i++){
		arg_structs[i] = malloc(sizeof(thread_args));
		arg_structs[i]->src=src;
		arg_structs[i]->dst=dst;
		arg_structs[i]->a=a;
        arg_structs[i]->b=b;
		pthread_create(&threads[i],NULL,&thread_routine,(void*)arg_structs[i]);
        a=b;
        if(a+2*block_size<=grid_height*grid_width){
            b=a+block_size;
        }
        else{
            b=grid_height*grid_width;
        }
        
	}
}


void update_grid_2(pthread_t threads[], int n){
    for(int i = 0; i<n; i++){
        pthread_kill(threads[i], SIGUSR1);
    }
}
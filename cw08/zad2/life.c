#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>


typedef struct thread_args thread_args;
void pass(){};


int main(int argc, char *argv[])
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "");
	initscr(); // Start curses mode

	signal(SIGUSR1, pass);

	char *foreground = create_grid();
	char *background = create_grid();
	char *tmp;

	int n = 30*30;

	int nthreads = atoi(argv[1]);
	int block_size = n/nthreads;

	pthread_t threads[nthreads];
	thread_args ** arg_structs = malloc(nthreads*sizeof(thread_args*));
	
	init_grid(foreground);
	// for(int i = 0; i<n;i++){
	// 	printf("%d/n", )
	// };
	threads_init(threads,arg_structs,nthreads,block_size,foreground,background);

	while (true)
	{
		draw_grid(background);
		usleep(500 * 1000);

		// Step simulation
		update_grid_2(threads,nthreads);
		tmp = foreground;
		foreground = background;
		background = tmp;
	}

	endwin(); // End curses mode
	destroy_grid(foreground);
	destroy_grid(background);

	for(int i; i<n; i++){
		free(arg_structs[i]);
	}
	free(arg_structs);

	return 0;
}

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


int main()
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "");
	initscr(); // Start curses mode

	signal(SIGUSR1, pass);

	char *foreground = create_grid();
	char *background = create_grid();
	char *tmp;

	const int n = 30*30;

	pthread_t threads[n];
	thread_args ** arg_structs = malloc(n*sizeof(thread_args*));
	
	init_grid(foreground);
	threads_init(threads,arg_structs,n,foreground,background);

	while (true)
	{
		draw_grid(foreground);
		usleep(500 * 1000);

		// Step simulation
		update_grid_2(threads,n);
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

CC=gcc
CFLAGS =-Wall


all: main

main:
	$(CC) $(CFLAGS) -c to_exec.c 

	$(CC) $(CFLAGS) -c main.c 
	$(CC) to_exec.o -o to_exec
	$(CC) main.o -o main
	
	
	
clean:
	rm *.o main to_exec
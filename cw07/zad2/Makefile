CFLAGS =-Wall
CC=gcc

all: main

main:
	$(CC) $(CFLAGS) -c main.c 
	$(CC) main.o -o main -l pthread -l rt
	
clean:
	rm *.o main 

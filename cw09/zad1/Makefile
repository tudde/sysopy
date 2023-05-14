CFLAGS =-Wall
CC=gcc

all: main

main:
	$(CC) $(CFLAGS) -c main.c 
	$(CC) main.o -o main -lpthread
	
clean:
	rm *.o main

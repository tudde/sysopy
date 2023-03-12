CC=gcc
CFLAGS =-Wall


all: main_1024

main:
	$(CC) $(CFLAGS) -c main.c 
	$(CC) main.o -o main

main_1024:
	$(CC) $(CFLAGS) -c main_1024.c 
	$(CC) main_1024.o -o main_1024

clean:
	rm main main_1024 *.o
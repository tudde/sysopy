CC=gcc
CFLAGS =-Wall


all: lib sys

lib:
	$(CC) $(CFLAGS) -c main_lib.c 
	$(CC) main_lib.o -o main_lib
sys:
	$(CC) $(CFLAGS) -c main_sys.c 
	$(CC) main_sys.o -o main_sys


clean:
	rm main_sys main_lib *.o
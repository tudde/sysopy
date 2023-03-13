CC=gcc
CFLAGS =-Wall


all: lib sys

lib:
	$(CC) $(CFLAGS) -c main_lib.c 
	$(CC) main_lib.o -o main_lib
sys:
	$(CC) $(CFLAGS) -c main_sys.c 
	$(CC) main_sys.o -o main_sys

test: lib sys
	echo POMIAR FUNKCJE BIBLIOTECZNE > pomiar_zad_1.txt
	(time ./main_lib c 4 ../test.txt result.txt) >> pomiar_zad_1.txt 2>&1
	echo POMIAR FUNKCJE SYSTEMOWE >> pomiar_zad_1.txt
	(time ./main_sys c 4 ../test.txt result.txt) >> pomiar_zad_1.txt 2>&1



clean:
	rm main_sys main_lib *.o result.txt
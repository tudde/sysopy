CC=gcc
CFLAGS =-Wall


all: main main_1024

main:
	$(CC) $(CFLAGS) -c main.c 
	$(CC) main.o -o main

main_1024:
	$(CC) $(CFLAGS) -c main_1024.c 
	$(CC) main_1024.o -o main_1024


test: main main_1024
	echo POMIAR POJEDYNCZE ZNAKI > pomiar_zad_2.txt
	(time ./main ../test.txt result.txt) >> pomiar_zad_2.txt 2>&1
	echo POMIAR BLOKI 1024 >> pomiar_zad_2.txt
	(time ./main_1024 ../test.txt result.txt) >> pomiar_zad_2.txt 2>&1

clean:
	rm main main_1024 *.o result.txt
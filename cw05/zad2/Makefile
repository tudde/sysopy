CC=gcc
CFLAGS =-Wall


all: main

main:
	$(CC) $(CFLAGS) -c main.c 
	$(CC) main.o -o main -lm

test: main 
	echo step: 0.000000005 n=1> pomiar_zad_2.txt
	(time ./main 0.000000005 1) >> pomiar_zad_2.txt 2>&1
	echo step: 0.000000005 n=5>> pomiar_zad_2.txt
	(time ./main 0.000000005 5) >> pomiar_zad_2.txt 2>&1
	echo step: 0.000000005 n=15>> pomiar_zad_2.txt
	(time ./main 0.000000005 15) >> pomiar_zad_2.txt 2>&1
	
	
	
clean:
	rm *.o main 
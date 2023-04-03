CC=gcc
CFLAGS =-Wall


all: main

main:
	$(CC) $(CFLAGS) -c main.c 
	$(CC) main.o -o main -lm

test: main 
	echo step: 0.00000005 n=1> pomiar_zad_2.txt
	(time ./main 0.00000005 1) >> pomiar_zad_2.txt 2>&1
	echo step: 0.00000005 n=3>> pomiar_zad_2.txt
	(time ./main 0.00000005 3) >> pomiar_zad_2.txt 2>&1
	echo step: 0.00000005 n=10>> pomiar_zad_2.txt
	(time ./main 0.00000005 10) >> pomiar_zad_2.txt 2>&1
	echo step: 0.00000005 n=100>> pomiar_zad_2.txt
	(time ./main 0.00000005 100) >> pomiar_zad_2.txt 2>&1
	
	echo -------------- >> pomiar_zad_2.txt


	echo step: 0.000000005 n=1>> pomiar_zad_2.txt
	(time ./main 0.000000005 1) >> pomiar_zad_2.txt 2>&1
	echo step: 0.000000005 n=3>> pomiar_zad_2.txt
	(time ./main 0.000000005 3) >> pomiar_zad_2.txt 2>&1
	echo step: 0.000000005 n=10>> pomiar_zad_2.txt
	(time ./main 0.000000005 10) >> pomiar_zad_2.txt 2>&1
	echo step: 0.000000005 n=100>> pomiar_zad_2.txt
	(time ./main 0.000000005 100) >> pomiar_zad_2.txt 2>&1
	
	
	
	
clean:
	rm *.o main 
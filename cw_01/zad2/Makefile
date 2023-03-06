CC=gcc
CFLAGS = -Wall

all: static

static: static-lib
		$(CC) -c main.c
		$(CC) main.o libmylibrary.a -o main



static-lib: 
		$(CC) $(CFLAGS) -c mylibrary.c
		ar crs libmylibrary.a mylibrary.o

dynamic-lib:
		$(CC) $(CFLAGS) -shared -fPIC mylibrary.c -o libmylibrary.so
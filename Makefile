CC=gcc
CFLAGS = -Wall

all: static dynamic
static: 
		$(CC) -c mylibrary.c
		ar crs libmylibrary.a mylibrary.o
dynamic:
		$(CC) $(CFLAGS) -shared -fPIC mylibrary.c -o libmylibrary.so
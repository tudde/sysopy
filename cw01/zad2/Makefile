CC=gcc
CFLAGS = -Wall

all: static

static: static-lib
		$(CC) $(CFLAGS) -c main.c
		$(CC) main.o libmylibrary.a -o main

shared: shared-lib 
		$(CC) $(CFLAGS) -c main.c
		$(CC) main.c -L. -lmylibrary -o main -Wl,-rpath=.
dynamic: shared-lib 
		$(CC) -c main.c
		$(CC) main.c -L. -lmylibrary -o main -ldl -D DYNAMIC


static-lib: 
		$(CC) $(CFLAGS) -c mylibrary.c
		ar crs libmylibrary.a mylibrary.o

shared-lib:
		$(CC) $(CFLAGS) -shared -fPIC mylibrary.c -o libmylibrary.so

clean:
		rm *.o *.a *.so main mylibrary test
CC=gcc
CFLAGS = -Wall

all: static

static: static-lib
		$(CC) $(CFLAGS) -c main.c
		$(CC) main.o libmylibrary.a -o main

shared: shared-lib 
		$(CC) $(CFLAGS)  -c main.c
		$(CC) main.c -L. -lmylibrary -o main -Wl,-rpath=.
dynamic: shared-lib 
		$(CC) $(CFLAGS) -c main.c
		$(CC) main.c -L. -lmylibrary -o main -ldl -D DYNAMIC


static-lib: 
		$(CC) $(CFLAGS) -c mylibrary.c
		ar crs libmylibrary.a mylibrary.o

shared-lib:
		$(CC) $(CFLAGS) -shared -fPIC mylibrary.c -o libmylibrary.so

test-static:  static
	./main < test_commands.txt > results_static.txt 


test-shared:  shared
	./main < test_commands.txt > results_shared.txt 

test-dynamic:  static
	./main < test_commands.txt > results_dynamic.txt 


clean:
		rm *.o *.so *.a results* main mylibrary test
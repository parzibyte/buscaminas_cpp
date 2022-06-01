CC=g++
CFLAGS=-Wall
main: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main 
	./main
TARGET1 = quicksort
CC = gcc
CFLAGS = -g -Wall -m32 -std=c99

.PHONY: clean all

default: all

all:
	make $(TARGET1)

$(TARGET1): quicksort.o simulator.o
	$(CC) $(CFLAGS) -o $(TARGET1) quicksort.o simulator.o

quicksort.o: quicksort.c simulator.h
	$(CC) $(CFLAGS) -c quicksort.c
	
simulator.o: simulator.c simulator.h
	$(CC) $(CFLAGS) -c simulator.c

clean:
	rm $(TARGET1) $(TARGET2) $(TARGET3) *.o *~

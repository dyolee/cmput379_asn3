TARGET1 = quicksort
TARGET2 = heapsort
CC = gcc
CFLAGS = -g -Wall -std=c99

.PHONY: clean all

default: all

all:
	make $(TARGET1)
	make $(TARGET2)

$(TARGET2): heapsort.o simulator.o
	$(CC) $(CFLAGS) -o $(TARGET2) heapsort.o simulator.o

$(TARGET1): quicksort.o simulator.o
	$(CC) $(CFLAGS) -o $(TARGET1) quicksort.o simulator.o

heapsort.o: quicksort.c simulator.h
	$(CC) $(CFLAGS) -c heapsort.c

quicksort.o: quicksort.c simulator.h
	$(CC) $(CFLAGS) -c quicksort.c
	
simulator.o: simulator.c simulator.h
	$(CC) $(CFLAGS) -c simulator.c

clean:
	rm $(TARGET1) $(TARGET2) *.o *~ *.txt

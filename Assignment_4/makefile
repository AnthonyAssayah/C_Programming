CC=gcc
FLAGS = -Wall -g

all: graph 

graph: main.o graph.h 
	$(CC) $(FLAGS) -o graph main.o 

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

Queue.o: Queue.c graph.h
	$(CC) $(FLAGS) -c Queue.c


.PHONY: clean all

clean:
	rm -f *.o *.a graph

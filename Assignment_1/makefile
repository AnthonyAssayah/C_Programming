CC=gcc
AR=ar
FLAGS= -Wall -g

all: loops loopd recursives recursived mains maindloop maindrec

loops: libclassloops.a

recursives: libclassrec.a

recursived: libclassrec.so

loopd: libclassloops.so


libclassloops.a: basicClassification.o advancedClassificationLoop.o
	$(AR) -rcs libclassloops.a  basicClassification.o advancedClassificationLoop.o

libclassrec.a: basicClassification.o advancedClassificationRecursion.o
	$(AR) -rcs libclassrec.a basicClassification.o advancedClassificationRecursion.o

libclassloops.so: basicClassification.o advancedClassificationLoop.o
	$(CC) -shared -o libclassloops.so  basicClassification.o advancedClassificationLoop.o

libclassrec.so: basicClassification.o advancedClassificationRecursion.o
	$(CC) -shared -o libclassrec.so  basicClassification.o advancedClassificationRecursion.o



basicClassification.o: basicClassification.c NumClass.h
	$(CC) $(FLAGS) -c basicClassification.c -lm

advancedClassificationLoop.o: advancedClassificationLoop.c NumClass.h
	$(CC) $(FLAGS) -c advancedClassificationLoop.c -lm

advancedClassificationRecursion.o: advancedClassificationRecursion.c NumClass.h
	$(CC) $(FLAGS) -c advancedClassificationRecursion.c -lm

main.o: main.c NumClass.h
	$(CC) $(FLAGS) -c main.c -lm


mains: main.o libclassrec.a
	$(CC) $(FLAGS) -o mains main.o libclassrec.a -lm

maindloop: main.o libclassloops.so 
	$(CC) $(FLAGS) -o maindloop main.o ./libclassloops.so -lm

maindrec: main.o libclassrec.so 
	$(CC) $(FLAGS) -o maindrec main.o ./libclassrec.so -lm


.PHONY: clean all

clean:
	rm *.o *.a *.so mains maindloop maindrec

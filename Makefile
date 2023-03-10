# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define sets of source files and object files
SRC = main.c rbtree.c integer.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)
 
# Define the executable name(s)
EXE = main

all: main

# The first target:
main: main.o rbtree.o integer.o
	gcc $(CFLAGS) -o main main.o rbtree.o integer.o
	
# Other targets specify how to get the .o files
main.o: main.c 
	gcc -c main.c  

rbtree.o: rbtree.c rbtree.h
	gcc -c rbtree.c 

integer.o: integer.c integer.h
	gcc -c integer.c

clean: 
	rm -f *.o main

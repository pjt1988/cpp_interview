OBJS=main.o
CC=g++
DEBG=-g  
CFLAG=-c $(DEBUG)
LFLAGS=-Wall -O3 $(DEBUG)
PFLAGS=-fopenmp -lpthread $(DEBUG)

all: $(OBJS)
	$(CC) -o "mc_test" $(LFLAGS) $(OBJS) $(PFLAGS)

main.o: main.cpp
	$(CC) -c $(DEGB) main.cpp $(PFLAGS)


clean: 
	\rm -f *.o mc_test

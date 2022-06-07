OBJDIR=obj
OBJS = $(OBJDIR)/rootfinder.o $(OBJDIR)/main.o $(OBJDIR)/eos.o 
			 
CC = g++

DEBUG = -g -D_GLIBCXX_CONCEPT_CHECKS -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
STANDARD= -std=c++11
WARNINGS= -w -Wall -Wextra -pedantic -Wno-conversion -Wcast-align -Wunused \
          -Wshadow -Wpointer-arith -Weffc++
OPTIMIZATION= -O2

SRC=$(realpath src)
INCLUDE=$(realpath include)

GSLPATH=/projects/jnorhos/local/include
GSLLIBPATH=/projects/jnorhos/local/lib
CFLAGS = $(WARNINGS) $(OPTIMIZATION) -c -I$(GSLPATH) $(DEBUG) $(STANDARD) -fopenmp
LDFLAGS = -lm -lgsl -lgslcblas -lstdc++ -L$(GSLLIBPATH) $(DEBUG) $(STANDARD) 

.PHONY:	all clean mkobjdir main

all:	mkobjdir main
	
mkobjdir:
	-@mkdir -p $(OBJDIR)

main: mkobjdir $(OBJS)
	$(CC) -g $(OBJS) -o persephone $(LDFLAGS)

$(OBJDIR)/main.o: $(INCLUDE)/eos.h $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $@

$(OBJDIR)/eos.o: $(INCLUDE)/eos.h $(SRC)/eos.cpp 
	$(CC) $(CFLAGS) $(SRC)/eos.cpp -o $@

$(OBJDIR)/rootfinder.o: $(INCLUDE)/rootfinder.h $(SRC)/rootfinder.cpp
	$(CC) $(CFLAGS) $(SRC)/rootfinder.cpp -o $@


clean:
	-rm $(OBJDIR)/*.o main

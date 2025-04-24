# Compiler and flags
CC = g++
FLAGS = -g -c -Wall -O3
LFLAGS = 

# Source files and object files
OBJS = State.o aStar.o main.o
SOURCE = State.cpp aStar.cpp main.cpp
HEADER = State.hpp aStar.hpp
OUT = puzzleSolver

# Libraries
LDLIBS = 

# Default target
all: $(OUT)

# Linking rules
$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDLIBS)

# Compilation rules
%.o: %.cpp $(HEADER)
	$(CC) $(FLAGS) -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(OUT)

# Compiler and flags
CC = g++
FLAGS = -g -c -Wall
LFLAGS = 

# Source files and object files
OBJS = Pseudohalogen
SOURCE = Pseudohalogen
HEADER = Pseudohalogen
OUT = PseudoHalogen

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

CC = gcc
CFLAGS = -Wall -Wextra -g  # Enable warnings & debugging
LIBS = -lm  # Link against the math library

Object files
OBJ = main.o data_structures.o

Compile .c files into .o files
%.o: %.c
    $(CC) -c -o $@ $< $(CFLAGS)

Build the final executable
stock_analysis: $(OBJ)
    $(CC) -o $@ $(OBJ) $(CFLAGS) $(LIBS)

Clean compiled files
.PHONY: clean
clean:
    rm -f *.o stock_analysis